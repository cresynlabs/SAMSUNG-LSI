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

uint16_t detach_cnt_r, detach_cnt_l;
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

void POGO_Process(uint8_t dir)
{
	uint16_t vout, iout;

	if (plc_get_plc_mode(dir) == PLC_MODE_OFF)
	{
		vout = pm_drv_get_vpogo(dir);
		if (vout < 100)
		{
			/* Enable LDO */
			plc_set_plc_mode(dir, PLC_MODE_LDO);

			/* If CHG_MODE is BUCK, you must turn on the Booster */
			if (sc_drv_get_reg_mode() == BUCK_MODE)
				sc_drv_set_reg_mode(BST_MODE);

			/* For PLC, VOUT need a difference between Vout and Booster more than 100mV  */
			sc_drv_set_bst_voltage(PLC_LDO_BST_4_7V);
			plc_set_plc_output(dir, PLC_LDO_4_6V);

			if (dir == LEFT)
			{
				printf("Left attached\r\n");
				led_drv_set_mode_en(LED2_RED, LED_CONSTANT_MODE);
			}
			else
			{
				printf("Right attached\r\n");
				led_drv_set_mode_en(LED5_RED, LED_CONSTANT_MODE);
			}
		}
	}
	else
	{
		iout = pm_drv_get_ipogo(dir);
		if (dir == LEFT)
		{
			/* If the Current is less than 3mA during 1sec (10ms X 100count), turn off LDO.
			   And Resetart detection.
			 */
			if (iout < 3)
				detach_cnt_l++;
			else
				detach_cnt_l = 0;

			if (detach_cnt_l > 100)
			{
				printf("Left detached\r\n");
				led_drv_set_mode_en(LED2_RED, LED_OFF_MODE);
				sysreg_drv_seten_det_reset_pogo(dir);
				sysdelay_us(50);
				sysreg_drv_seten_det_pogo(dir, ON);
				plc_set_plc_mode(dir, PLC_MODE_OFF);
			}
		}
		else
		{
			if (iout < 3)
				detach_cnt_r++;
			else
				detach_cnt_r = 0;

			if (detach_cnt_r > 100)
			{
				printf("Right detached\r\n");
				led_drv_set_mode_en(LED5_RED, LED_OFF_MODE);
				sysreg_drv_seten_det_reset_pogo(dir);
				sysdelay_us(50);
				sysreg_drv_seten_det_pogo(dir, ON);
				plc_set_plc_mode(dir, PLC_MODE_OFF);
			}

		}
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

	/* Turn off the output for POGO_DET */
	plc_set_plc_mode(LEFT, PLC_MODE_OFF);
	plc_set_plc_mode(RIGHT, PLC_MODE_OFF);

	/* Enable ADC of POGO */
	pm_drv_set_vpogo_co(ON);
	pm_drv_set_ipogo_co(ON);

	/* Detection must be set in the order below */
	sysreg_drv_seten_det_reset_pogo(LEFT);
	sysreg_drv_seten_det_reset_pogo(RIGHT);

	sysreg_drv_seten_det_pogo(LEFT, ON);
	sysreg_drv_seten_det_pogo(RIGHT, ON);

	detach_cnt_r = 0;
	detach_cnt_l = 0;

	systime = sys_get_tick();

	while (1)
	{
		if (sys_get_tick() - systime > 10)
		{
			systime = sys_get_tick();

			POGO_Process(RIGHT);
			POGO_Process(LEFT);
		}
	}
}

#pragma arm section code


