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
	uint32_t systime = 0;

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

	/* Enable SysTick_IRQ */
	NVIC_EnableIRQ(SysTick_IRQn);

	/* Get Current System Time */
	systime = sys_get_tick();

	printf("%s, sys time : %d\r\n", __func__, systime);

	/* Init Timer0
	S2MUA01 has 2 Timers for USER
	Both Timers has 16Mhz Tick Clock and are accessible in the same way */
	timer0_irq_initialize(1000000); /* 1000000usec */
	timer0_irq_start();

	/*Timer IRQ Handler is called after 1000000usec
	and it set timer0_val = 1
	it is defined at Drivers/Drivers/TimerDrv.c */
	while (get_timer0_val() == 0);

	/* Get Current System Time */
	systime = sys_get_tick();

	printf("%s, sys time : %d\r\n", __func__, systime);

	timer0_irq_stop();

	timer1_irq_initialize(100); /* 100msec */
	timer1_irq_start();
	/*Timer IRQ Handler is called after 100msec
	and it set timer0_val = 1
	it is defined at Drivers/Drivers/TimerDrv.c */
	while (get_timer0_val() == 0);

	/* Get Current System Time */
	systime = sys_get_tick();

	printf("%s, sys time : %d\r\n", __func__, systime);

	while (1)
	{
		/* Timer is used for delay */
		sysdelay_ms(1000); /* delay 1000ms */
		systime = sys_get_tick();
		printf("%s, systime : %d\r\n", __func__, systime);
	}
}

#pragma arm section code


