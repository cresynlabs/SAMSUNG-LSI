
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

void charging_event(void)
{
	uint8_t stats;

	/* occur VBUS(CHGIN) interrupt */
	stats = sc_drv_get_chgin_status();
	if (stats == CHGIN_UNDER_UVLO || stats == CHGIN_VOLTAGE_LOW || stats == CHGIN_IN_SWITCH_IS_OFF)
	{
		if (plc_get_plc_mode(RIGHT) == PLC_MODE_LDO || plc_get_plc_mode(LEFT) == PLC_MODE_LDO)
			sc_drv_set_reg_mode(BST_MODE);
		else
			sc_drv_set_reg_mode(BUCK_MODE);

		led_drv_set_mode_en(LED2_RED, LED_OFF_MODE);
	}
	if (stats == CHGIN_OVER_OVLO || stats == CHGIN_IN_CURRENT_IS_LIMITED_REGUL || stats == CHGIN_IS_VALID)
	{
		sc_drv_set_reg_mode(CHG_MODE);
		led_drv_set_mode_en(LED2_RED, LED_CONSTANT_MODE);
	}

}


int main(void)
{

	uint32_t systime=0;

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
	sc_drv_set_fast_charge_current(0x04); /* set charging current 125mA */

	systime = sys_get_tick();

	while (1)
	{
		if ((sys_get_tick() - systime) > 10)
		{
			systime = sys_get_tick();
			charging_event();
		}
	}

}

#pragma arm section code


