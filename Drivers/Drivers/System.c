/*
******************************************************************************
* @file    System.c
* @author  Power Device Team
* @version V1.0.0
* @date    15-March-2016
* @brief
******************************************************************************
*/

#include "System.h"
#include "wpc.h"

volatile uint32_t sys_tick_time = 0;
volatile uint32_t sys_tick_time_125uSec = 0;

void boot_systick_handler(void)
{
	sys_tick_time++;
	wpc_set_tick(sys_tick_time);

    SCB->ICSR = SCB_ICSR_PENDSTCLR_Msk; // remove pend state from systick

    return;
}

uint32_t sys_get_tick(void)
{
	return sys_tick_time;
}

/* Ref Clk - 16MHz
 * Systick Clock - 5.3Mhz  ==> (Ref.Clk / 3)
 * Count 5333 = 1ms
 * CTRL : b0 - ENABLE	b1 - TICKINT	b2 - ClkSource	b16 - CountFlg
 * SysTick->LOAD   = (0xFFFFFF & ((1 << 24)-1))-1; */
void systimer_initialize(void)
{
    SysTick->CTRL = 0x0;  /* Systick Disable */
    SysTick->LOAD = TICK_UNIT;
    SysTick->VAL = 0x0;
    SysTick->CTRL = 0x3;  /* Systick Enable */
    return;
}

void systimer_stop(void)
{
    SysTick->CTRL   = 0x0;  /* Systick Disable */
    SysTick->LOAD   = 0x0;
    SysTick->VAL    = 0x0;
    return;
}

void sysdelay_ms(uint32_t delay_ms)
{
	uint32_t ul_temp;

	ul_temp = sys_tick_time;

	while(1)
	{
		if ((sys_tick_time - ul_temp) > delay_ms)
			break;
	}
}

void sysdelay_us(uint32_t delay_us)
{
	uint32_t tdata;

	if (delay_us == 0)
		return;

	TIMER.TMOD.BITS.TE0 = 0; /* timer 0 disable */
	TIMER.TCNT0.DATA = 0xFFFFFFFF;

	tdata = delay_us * 0x10;
	tdata = 0xFFFFFFFF -  tdata;
	TIMER.TMOD.BITS.TE0 = 1; /* timer 0 enable */

	while (TIMER.TCNT0.DATA > tdata);

	TIMER.TMOD.BITS.TE0 = 0; /* timer 0 disable */
}

