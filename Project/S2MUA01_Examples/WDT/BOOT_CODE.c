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
	for (cnt = 0; cnt < 10000; cnt++)
	{
		__NOP();
	}
}

int main(void)
{
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

	/* Initalize WDT, Timeout timer is 2330ms. You can change timer value. */
	sysreg_drv_set_wdt();

	while (1)
	{
		/*
		   Reset WDT Timer
		   If you don't reset the timer, the MCU is reset by IRQ handler.(boot_WDT_IRQHandler)
		 */
		sysreg_drv_set_wdt_reset();
	}
}

#pragma arm section code


