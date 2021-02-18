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

void fg_init(void)
{
	/* Read BATCAP, BATCAP_OCV, Design_CAP etc.  from FACTORY_SECTION(to be) */

	fg_drv_set_if_en(3);				/* IF_EN (0x03) enable to 0b11 */

	fg_drv_set_ocv_soc_rs_lut();		/* OCV, SOC, RS Table(0x92~0xFF) write */

	fg_drv_set_batcap_ocv(0x078C);		/* BATCAP_OCV (0x04/60) set */
	sysdelay_us(10);
	fg_drv_set_batcap_ocv_en(1);		/* BATCAP_OCV_EN (0x0C) enable */
	fg_drv_set_batcap(0x0121);			/* BATCAP write (0x11/10) */
	fg_drv_set_design_cap(0x0460);		/* Design CAP write (0x87/86) */
	fg_drv_set_init_done();
	fg_drv_set_start();				/* dumpdone, FG start (0x1E to 0x03) */
	/* FG ADC is default disable State.
	You have to enable to calculate SOC, Voltage, Current */

	fg_drv_set_if_en(3);			/* Fuelgauge I2C Enable */

	/* Set Battery Parameter,
	this will be guilded by SAMSUNG */
	fg_drv_set_ocv_soc_rs_lut();

	fg_drv_set_batcap_ocv(0x03D4);	/* set BATCAP_OCV */
	fg_drv_set_batcap(0x0093);		/* set BAT CAP */

	fg_drv_set_batcap_ocv_en(1);	/* BATCAP OCV enable */

	fg_drv_set_edv(0x67);			/* Set EDV Voltage : 2.8V */

	fg_drv_set_init_done();			/* mark FG Init Done */

	fg_drv_set_start();			/* FG start */

	sysdelay_ms(100);			/* must wait for operating FG */

	fg_drv_set_if_en(0);			/* Fuelgauge I2C Disable */
}

void set_fg_soc(float soc)
{
	fg_drv_set_if_en(3);			/* Fuelgauge I2C Disable */

	fg_drv_set_soc_i2c(soc * 100.0f);

	fg_drv_set_restart();			/* must restart FG to set soc by user */

	fg_drv_set_if_en(0);			/* Fuelgauge I2C Disable */
}

int main(void)
{
	uint32_t systime = 0;
	float temp, soc, VBAT, Current;

	NVIC->ICER[0] = (uint32_t)0xFFFFFFFF;       /* Disable All IRQ */
	NVIC->ICPR[0] = (uint32_t)0xFFFFFFFF;       /* Interrupt Pending Clear */

	/* OM LOW Debouncgrepe time */
	SYSREG.OM_DBNC_PDLY.BITS.OM_DBNC_PDLY = 0x8000;    /* 0x8000 =2 ms */
	SYSREG.DMA_Flash.BITS.PI2C_TO_FLASH_AUTO_PGM = 0;
	PM.REG_4C.BITS.VBAT1CO = 1;

	systimer_initialize();
	NVIC_EnableIRQ(IRQ00_NOR);
	variable_area_clear();
	gpio_drv_set_to_uart();
	uart_drv_init();

	delay_for_stablization();

	printf("START S2MUA01 : %s\r\n", BuildTime);

	fg_init();

	/* example code, set soc 50 by user */
	set_fg_soc(0.5f);

	fg_drv_set_voltage_mode(FALSE);	/* Set FG CC Mode */

	/* INC OK EN Disable,
	 * INC OK EN Mean that allow increasing SOC during discharging
	 * It is usually used after charge done */
	fg_drv_set_inc_ok_en(FALSE);

	while (1)
	{
		if ((sys_get_tick() - systime) > 1000)
		{
			systime = sys_get_tick();

			temp = fg_drv_get_temp();
			Current = fg_drv_get_cur_cc();
			VBAT = fg_drv_get_vbat();
			soc = fg_drv_get_soc_r();

			printf("temp : %4.1f, Current : %6.3fA, VBAT : %1.3fV, soc : %1.3f\r\n",
													temp, Current, VBAT, soc);
		}
	}
}

#pragma arm section code


