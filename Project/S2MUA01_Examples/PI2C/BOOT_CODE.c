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
	uint8_t gpio_status=0;
	uint32_t systime=0;

	NVIC->ICER[0] = (uint32_t)0xFFFFFFFF;       /* Disable All IRQ */
	NVIC->ICPR[0] = (uint32_t)0xFFFFFFFF;       /* Interrupt Pending Clear */

	/* OM LOW Debounce time */
	SYSREG.OM_DBNC_PDLY.BITS.OM_DBNC_PDLY = 0x8000; /* 0x8000 =2 ms */
	SYSREG.DMA_Flash.BITS.PI2C_TO_FLASH_AUTO_PGM = 0;
	PM.REG_4C.BITS.VBAT1CO = 1;

	systimer_initialize();
	NVIC_EnableIRQ(IRQ00_NOR);
	NVIC_EnableIRQ(IRQ01_PI2C);
	
	variable_area_clear();
	gpio_drv_set_to_uart();
	uart_drv_init();

	delay_for_stablization();

	i2c_slave_init();

	gpio_drv_set_enable(GPIO_PORT1, GPIO_PORT_MODE_CMOS);

	systime = sys_get_tick();

	while (1)
	{
		if ((sys_get_tick() - systime) > 500)
		{
			systime = sys_get_tick();
			gpio_drv_set_output_data(GPIO_PORT2, !gpio_drv_get_output_data(GPIO_PORT2));
		}

		if (gpio_drv_get_input_data(GPIO_PORT1) != gpio_status)
		{
			if (gpio_status == TRUE)
			{
				gpio_status = FALSE;
				printf("GPIO1 is Low\r\n");
			}
			else
			{
				gpio_status = TRUE;
				printf("GPIO1 is High\r\n");
			}
		}
	}	
}

#pragma arm section code


