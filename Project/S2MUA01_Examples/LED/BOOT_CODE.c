/*
******************************************************************************
* @file    boot_code.c
* @author  Power Device Team
* @version V1.0.0
* @date    15-March-2016
* @brief   Boot System Function
******************************************************************************
*/

#include "cm0pikmcu.h"
#include "System.h"
#include "common_drv.h"
#include "PLC.h"
#include "sc_drv.h"
#include "timer_drv.h"
#include "i2c_drv.h"
#include "fg_drv.h"
#include "led_drv.h"

#pragma arm section code = "region_main_func"

void variable_area_clear(void)
{
	uint32_t *ClrAdr, ulCnt;

	ClrAdr = (uint32_t *)(DATA_AREA_BASE);
	for (ulCnt = 0; ulCnt < (FLASH_DUMP_SIZE / 4); ulCnt++)
		ClrAdr[ulCnt] = 0;

	ClrAdr = (uint32_t *)(EXT_SRAM_BASE + 0x10);
	for (ulCnt = 0; ulCnt < 16; ulCnt++)
		ClrAdr[ulCnt] = 0xFFFFFFFF;
}

void delay_for_stablization(void)
{
	uint32_t cnt;
	for (cnt = 0; cnt < 10000; cnt++)
	{
		__NOP();
	}
}

uint8_t charging_event(void)
{
	uint8_t stats;

	// occur VBUS(CHGIN) interrupt
	stats = sc_drv_get_chgin_status();
	if (stats == CHGIN_UNDER_UVLO || stats == CHGIN_VOLTAGE_LOW || stats == CHGIN_IN_SWITCH_IS_OFF)
	{
		if (plc_get_plc_mode(RIGHT) == PLC_MODE_LDO || plc_get_plc_mode(LEFT) == PLC_MODE_LDO)
			sc_drv_set_reg_mode(BST_MODE);
		else
			sc_drv_set_reg_mode(BUCK_MODE);

		return 0;
	}
	if (stats == CHGIN_OVER_OVLO || stats == CHGIN_IN_CURRENT_IS_LIMITED_REGUL || stats == CHGIN_IS_VALID)
	{
		sc_drv_set_reg_mode(CHG_MODE);

		return 1;
	}

	return 0;
}

int main(void)
{
	uint32_t systime = 0;
	uint8_t prev_chg_status = 0;
	uint8_t current_chg_status = 0;
	

	NVIC->ICER[0] = (uint32_t)0xFFFFFFFF;       /* Disable All IRQ */
	NVIC->ICPR[0] = (uint32_t)0xFFFFFFFF;       /* Interrupt Pending Clear */

	/* OM LOW Debounce time */
	SYSREG.OM_DBNC_PDLY.BITS.OM_DBNC_PDLY = 0x8000; /* 0x8000 =2 ms */
	SYSREG.DMA_Flash.BITS.PI2C_TO_FLASH_AUTO_PGM = 0;
	PM.REG_4C.BITS.VBAT1CO = 1;

	systimer_initialize();
	NVIC_EnableIRQ(IRQ00_NOR);
	variable_area_clear();
	gpio_drv_set_to_uart();
	uart_drv_init();

	delay_for_stablization();

	printf("START S2MUA01 : %s\r\n", BuildTime);

	sc_drv_set_1st_topoff(TOPOFF_40MA);
	sc_drv_set_2nd_topoff(TOPOFF_30MA);

	sc_drv_set_charger_off_by_2nd_topoff(0x08);

	sc_drv_set_reg_mode(BUCK_MODE);
	sc_drv_set_switch_freq(SWITCH_FREQ_1M);

	/* S2MUA01 has 5 LEDs, the current should be defined to adjust led light */
	led_drv_set_current(LED1_BLUE, 0x6);
	led_drv_set_current(LED2_RED | LED3_GREEN | LED4_GREEN | LED5_RED, 0x6);

	/* All LED can be set to BLINK Mode */
	led_drv_set_mode_en(LED1_BLUE, LED_BLINK_MODE);

	sysdelay_ms(2000);

	/* turn off LED */
	led_drv_set_mode_en(LED1_BLUE, LED_OFF_MODE);

	sysdelay_ms(1000);

	/* All LED can be set to CONSTANT Mode */
	led_drv_set_mode_en(LED1_BLUE, LED_CONSTANT_MODE);

	sysdelay_ms(2000);

	/* turn off LED */
	led_drv_set_mode_en(LED1_BLUE, LED_OFF_MODE);

	while (1)
	{
		if ((sys_get_tick() - systime) > 1000)
		{
			systime = sys_get_tick();

			/* Example Code is that
			turn on/off RED LED according to Charging Status */
			current_chg_status = charging_event();

			if (prev_chg_status != current_chg_status)
			{
				if (current_chg_status)
				{
					/* set BLINK Mode On/off time */
					led_drv_set_ontime(LED2_RED, 0x0F);
					led_drv_set_offtime(LED2_RED, 0);

					/* start BLINK mode low to high */
					led_drv_set_onoff_sequence(0);

					/* set BLINK mode ramp delay */
					led_drv_set_rampup_time(LED2_RED, 0x01);
					led_drv_set_rampdn_time(LED2_RED, 0x01);

					/* Combine tow modes to slowly turn the LED on */
					led_drv_set_mode_en(LED2_RED, LED_BLINK_MODE);
				
					sysdelay_ms(300);

					led_drv_set_mode_en(LED2_RED, LED_CONSTANT_MODE);
				}
				else
				{
					led_drv_set_ontime(LED2_RED, 0x0);
					led_drv_set_offtime(LED2_RED, 0x0F);
					led_drv_set_rampup_time(LED2_RED, 0x00);
					led_drv_set_rampdn_time(LED2_RED, 0x01);

					/* Combine tow modes to slowly turn the LED off */
					led_drv_set_mode_en(LED2_RED, LED_BLINK_MODE);
				
					sysdelay_ms(300);

					led_drv_set_mode_en(LED2_RED, LED_OFF_MODE);
				}
				prev_chg_status = current_chg_status;
			}
		}
	}
}

#pragma arm section code


