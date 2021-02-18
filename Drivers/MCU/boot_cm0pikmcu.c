/*
******************************************************************************
* @file    boot_cm0pikmcu.c
* @author  Power Device Team
* @version V1.0.0
* @date    15-March-2016
* @brief   Inital vector table and Handler
******************************************************************************
*/


#include <stdio.h>
#include <rt_misc.h>
#include <stdint.h>
#include "cm0pikmcu.h"
#include "wpc.h"

//
// Dummy Interrupt Handlers
//
// The following functions are defined weakly to allow the user
// to override them at link time simply by declaring their own
// function of the same name.
//
// If no user function is provided, the weak function is used.
//

//
// Reset Handler
//

#pragma arm section code = "region_boot_config_func"

// ============ Exception & IRQ Handler register Function ===========
EXP_REG_FN register_exception_handler(uint32_t EXP_ID, exception_fn_t EXP_Handler)
{
    EXP_REG_FN Old_Handler;

    Old_Handler = EXCEPTION_TBL.exp_EXCEPTION_HANDLER[EXP_ID];
    EXCEPTION_TBL.exp_EXCEPTION_HANDLER[EXP_ID] = (EXP_REG_FN)EXP_Handler;

    return Old_Handler;
}

IRQ_REG_FN register_irq_handler(uint32_t IRQ_ID, IRQ_fn_t IRQ_Handler)
{
    IRQ_REG_FN Old_Handler;

    Old_Handler = IRQ_TBL.irq_INTERRUPT_HANDLER[IRQ_ID];
    IRQ_TBL.irq_INTERRUPT_HANDLER[IRQ_ID] = (IRQ_REG_FN)IRQ_Handler;

    return Old_Handler;
}

__weak void boot_nmi_handler(void)
{
    //__Flash_Vectors[Vect_NMI]();
    return;
}

__weak void boot_hardfault_handler(void)
{
    //DATA_SRAM.FLASH_MODE_STATUS = FLASH_FUNCTION_STATE;
    //__Flash_Vectors[Vect_HARDFAULT]();
    SYSREG.Soft_Rst.DATA |= bCORE;
    return;
}

__weak void boot_svc_handler(void)
{
    //__Flash_Vectors[Vect_SVC]();
    return;
}

__weak void boot_pend_sv_handler(void)
{
    //__Flash_Vectors[Vect_PENDSV]();
	SCB->ICSR = SCB_ICSR_PENDSVCLR_Msk; // remove pend state from PendSV

    return;
}

__weak void boot_systick_handler(void)
{
    //__Flash_Vectors[Vect_SYSTICK]();
	SCB->ICSR = SCB_ICSR_PENDSTCLR_Msk; // remove pend state from SysTick

    return;
}


__weak void boot_Default_IRQHandler(void)
{
    while(1);
}


//
// Reset Handler
//

void reset_handler(void)
{

	BOOTCON.EXT_RST_SEL.BITS.EXT_RST_SEL = 0;

	main();

    return;
}

__weak void boot_nor_irqhandler(void)
{
    return;
}

__weak void boot_pi2c1_irqhandler(void)
{
	NVIC_ClearPendingIRQ(IRQ01_PI2C);

    return;
}

__weak void boot_mi2c1_irqhandler(void)
{
    NVIC_ClearPendingIRQ(IRQ02_MI2C);

    return;
}

__weak void boot_fg_irqhandler(void)
{
    NVIC_ClearPendingIRQ(IRQ03_FG);
    return;
}

__weak void boot_fg2_irqhandler(void)
{
	NVIC_ClearPendingIRQ(IRQ04_FG2);

    return;
}

__weak void boot_uart_txd_irqhandler(void)
{
	NVIC_ClearPendingIRQ(IRQ05_UART_TXD);
    return;
}

__weak void boot_plc_irq_handler(void)
{
    NVIC_ClearPendingIRQ(IRQ06_PLC);

    return;
}

__weak void boot_wdt_irqhandler(void)
{
	NVIC_ClearPendingIRQ(IRQ07_WDT);
    return;
}

__weak void boot_timer0_irqhandler(void)
{
    NVIC_ClearPendingIRQ(IRQ08_TIMER0);
    return;
}

__weak void boot_timer1_irqhandler(void)
{
    NVIC_ClearPendingIRQ(IRQ09_TIMER1);
    return;
}

__weak void boot_Timer2_irqhandler(void)
{
    NVIC_ClearPendingIRQ(IRQ10_TIMER2);

    return;
}

__weak void boot_timer3_irqhandler(void)
{
    NVIC_ClearPendingIRQ(IRQ11_TIMER3);

    return;
}

#if 0
__weak void boot_wpt_com_irqhandler(void)
{
    NVIC_ClearPendingIRQ(IRQ12_WPT_COM);
    return;
}

__weak void boot_wpt_adc_irqhandler(void)
{
	NVIC_ClearPendingIRQ(IRQ13_WPT_ADC);
    return;
}

__weak void boot_wpt_ext_reg_irqhandler(void)
{
    NVIC_ClearPendingIRQ(IRQ14_WPT_EXT_REG);
    return;
}
#endif

__weak void boot_gpio_in0_irqhandler(void)
{
	NVIC_ClearPendingIRQ(IRQ15_SEL_GPIO_IN0);
    return;
}

__weak void boot_gpio_in1_irqhandler(void)
{
    NVIC_ClearPendingIRQ(IRQ16_SEL_GPIO_IN1);
    return;
}

__weak void boot_gpio_irqhandler(void)
{
    NVIC_ClearPendingIRQ(IRQ18_GPIO_EDGE_TRIG);
    return;
}

__weak void boot_r_int_sc_irqhandler(void)
{
	NVIC_ClearPendingIRQ(IRQ19_R_SC);
    return;
}

__weak void boot_int_pm_irqhandler(void)
{
    NVIC_ClearPendingIRQ(IRQ20_PM);
    return;
}

__weak void boot_det_pogo_irqhandler(void)
{
    NVIC_ClearPendingIRQ(IRQ21_DET_POGO);
    return;
}

__weak void boot_det_hall_irqhandler(void)
{
	NVIC_ClearPendingIRQ(IRQ22_DET_HALL);
    return;
}

__weak void boot_pi2c_ahb_err_irqhandler(void)
{
    NVIC_ClearPendingIRQ(IRQ24_PI2C_AHB_ERR);
    return;
}

__weak void boot_monout1_no_clk_irqhandler(void)
{
    NVIC_ClearPendingIRQ(IRQ25_MON_OUT1_NO_CLK);
    return;
}

__weak void boot_monout2_no_clk_irqhandler(void)
{
    NVIC_ClearPendingIRQ(IRQ26_MON_OUT2_NO_CLK);
    return;
}

__weak void boot_a2d_wpt_nreset_irqhandler(void)
{
    NVIC_ClearPendingIRQ(IRQ27_A2D_WPT_NRST);
    return;
}

__weak void boot_plc_r_irq_handler(void)
{

    NVIC_ClearPendingIRQ(IRQ28_PLC_R);

    return;
}

__weak void boot_plc_l_irq_handler(void)
{

    NVIC_ClearPendingIRQ(IRQ29_PLC_L);

    return;
}


#pragma arm section code


#if 1
//
// Set up Vector Table
//

Boot_vect_t __Vectors[]
__attribute__ ((section("boot_vectors"))) =
{
  (Boot_vect_t)(STACK_BASE),             	// Top of Stack             // 0x00
  (Boot_vect_t)reset_handler,            	// Reset Handler            // 0x04
  (Boot_vect_t)boot_nmi_handler,            // NMI Handler              // 0x08
  (Boot_vect_t)boot_hardfault_handler,      // Hard Fault Handler       // 0x0C
  0,                                		// Reserved                 // 0x10
  0,                                		// Reserved                 // 0x14
  0,                                		// Reserved                 // 0x18
  0,                                		// Reserved                 // 0x1C
  0,                                		// Reserved                 // 0x20
  0,                                		// Reserved                 // 0x24
  0,                                		// Reserved                 // 0x28
  (Boot_vect_t)boot_svc_handler,            // SVCall Handler           // 0x2C
  0,                                		// Reserved                 // 0x30
  0,                                		// Reserved                 // 0x34
  (Boot_vect_t)boot_pend_sv_handler,         // PendSV Handler           // 0x38
  (Boot_vect_t)boot_systick_handler,        // SysTick Handler          // 0x3C

  // External Interrupts
  (Boot_vect_t)boot_nor_irqhandler,         //(Boot_vect_t)GPIO_IRQHandler,  // 0x40

  // External Interrupts 1 - 32
  // These are essentially unused, so will all
  // take the same default handler if invoked.

  // 1-3
  (Boot_vect_t)boot_pi2c1_irqhandler,       // 0x44
  (Boot_vect_t)boot_mi2c1_irqhandler,		// 0x48
  (Boot_vect_t)boot_fg_irqhandler,          // 0x4C

  //4-7
  (Boot_vect_t)boot_fg2_irqhandler,         // 0x50
  (Boot_vect_t)boot_uart_txd_irqhandler,    // 0x54
  (Boot_vect_t)boot_plc_irq_handler,         // 0x58
  (Boot_vect_t)boot_wdt_irqhandler,         // 0x5C

  //8-11
  (Boot_vect_t)boot_timer0_irqhandler,      // 0x60
  (Boot_vect_t)boot_timer1_irqhandler,      // 0x64
  (Boot_vect_t)boot_Timer2_irqhandler,      // 0x68
  (Boot_vect_t)boot_timer3_irqhandler,      // 0x6C

  //12-15
  (Boot_vect_t)boot_wpt_com_irqhandler,     // 0x7C
  (Boot_vect_t)boot_wpt_adc_irqhandler,     // 0x74
  (Boot_vect_t)boot_wpt_ext_reg_irqhandler, // 0x78
  (Boot_vect_t)boot_gpio_in0_irqhandler,    // 0x7C

  //16-19
  (Boot_vect_t)boot_gpio_in1_irqhandler,    // 0x80
  0,                                       	// 0x84
  (Boot_vect_t)boot_gpio_irqhandler,        // 0x88
  (Boot_vect_t)boot_r_int_sc_irqhandler,    // 0x8C

  //20-23
  (Boot_vect_t)boot_int_pm_irqhandler,      // 0x90
  (Boot_vect_t)boot_det_pogo_irqhandler,    // 0x94
  (Boot_vect_t)boot_det_hall_irqhandler,    // 0x98
  0,                              			// 0x9C

  //24-27
  (Boot_vect_t)boot_pi2c_ahb_err_irqhandler,// 0xA0
  (Boot_vect_t)boot_monout1_no_clk_irqhandler,// 0xA4
  (Boot_vect_t)boot_monout2_no_clk_irqhandler,// 0xA8
  (Boot_vect_t)boot_a2d_wpt_nreset_irqhandler,// 0xAC

  //28-31
  (Boot_vect_t)boot_plc_r_irq_handler,    	// 0xB0
  (Boot_vect_t)boot_plc_l_irq_handler,       // 0xB4
  0,					                    // 0xB8
  0											// 0xBC
};
#endif

