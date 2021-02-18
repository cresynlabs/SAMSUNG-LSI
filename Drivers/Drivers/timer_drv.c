#include "cm0pikmcu.h"
#include "timer_drv.h"
#include "common_drv.h"

uint32_t timer0_val;

void boot_timer0_irqhandler(void)
{
	timer0_val = 1;

	TIMER.TINTSTAT.BITS._32bit_Timer0_Interrupt_clear = 1;
    NVIC_ClearPendingIRQ(IRQ08_TIMER0);
}

uint32_t get_timer0_val(void)
{
	return timer0_val;
}

void timer0_irq_initialize(uint32_t usec)
{
	timer0_val = 0;

	TIMER.TMOD.BITS.TE0 = 0;
	TIMER.TDATA0.DATA = 16 * usec;

	NVIC_EnableIRQ(IRQ08_TIMER0);
}

void timer0_irq_start(void)
{
	TIMER.TMOD.BITS.TE0 = 1;
}

void timer0_irq_stop(void)
{
	TIMER.TMOD.BITS.TE0 = 0;
}

void boot_timer1_irqhandler(void)
{
	timer0_val = 1;
	TIMER.TINTSTAT.BITS._32bit_Timer1_Interrupt_clear = 1;
    NVIC_ClearPendingIRQ(IRQ09_TIMER1);

	timer1_irq_stop();
}

void timer1_irq_initialize(uint32_t msec)
{
	timer0_val = 0;

	TIMER.TMOD.BITS.TE1 = 0;
	TIMER.TDATA1.DATA = (16000 * msec);

	NVIC_EnableIRQ(IRQ09_TIMER1);
}

void timer1_irq_start(void)
{
	if (TIMER.TMOD.BITS.TE1 == 1)
		return;
	TIMER.TMOD.BITS.TE1 = 1;
}

void timer1_irq_stop(void)
{
	TIMER.TMOD.BITS.TE1 = 0;
}
