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
	for (cnt = 0; cnt < 10000;cnt++)
	{
		__NOP();
	}
}

int main(void)
{
	uint32_t systime=0;

	uint16_t vout;

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

	while (1)
	{
		if ((sys_get_tick() - systime) > 200)
		{
			systime = sys_get_tick();
			vout = pm_drv_get_vpogo(LEFT);

			if (vout < 100)  /* 100mV */
			{
				printf("LEFT detected\r\n");
				/* Restart detecion */
				sysreg_drv_seten_det_reset_pogo(LEFT);
				sysreg_drv_seten_det_pogo(LEFT, ON);
				plc_set_plc_mode(LEFT, PLC_MODE_OFF);
			}
			vout = pm_drv_get_vpogo(RIGHT);
			if (vout < 100)
			{
				printf("RIGHT detected\r\n");
				sysreg_drv_seten_det_reset_pogo(RIGHT);
				sysreg_drv_seten_det_pogo(RIGHT, ON);
				plc_set_plc_mode(RIGHT, PLC_MODE_OFF);

			}
		}
	}
}

#pragma arm section code


