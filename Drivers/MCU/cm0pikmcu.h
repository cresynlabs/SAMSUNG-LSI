/*
 *-----------------------------------------------------------------------------
 * The confidential and proprietary information contained in this file may
 * only be used by a person authorised under and to the extent permitted
 * by a subsisting licensing agreement from ARM Limited.
 *
 *            (C) COPYRIGHT 2011-2012 ARM Limited.
 *                ALL RIGHTS RESERVED
 *
 * This entire notice must be reproduced on all copies of this file
 * and copies of this file may only be made by a person if such person is
 * permitted to do so under the terms of a subsisting license agreement
 * from ARM Limited.
 *
 *      SVN Information
 *
 *      Checked In          : $Date: 2012-12-11 21:30:49 +0000 (Tue, 11 Dec 2012) $
 *
 *      Revision            : $Revision: 231305 $
 *
 *      Release Information : Cortex-M0+ AT590-r0p1-00rel0
 *-----------------------------------------------------------------------------
 */

#ifndef __CM0PIKMCU_H__
#define __CM0PIKMCU_H__

#include <stdio.h>
#include <rt_misc.h>
#include <stdint.h>

/*
 * ==========================================================================
 * ---------- Interrupt Number Definition -----------------------------------
 * ==========================================================================
 */

typedef enum IRQn
{
/******  Cortex M0+ Processor Exceptions Numbers **************************************************/
    NonMaskableInt_IRQn        = -14,    /*!< 2 Non Maskable Interrupt                              */
    HardFault_IRQn	           = -13,    /*!< 3 Cortex M0+ Hard Fault Interrupt                     */
    SVCall_IRQn                = -5,     /*!< 11 Cortex M0+ SV Call Interrupt                       */
    PendSV_IRQn                = -2,     /*!< 14 Cortex M0+ Pend SV Interrupt                       */
    SysTick_IRQn               = -1,     /*!< 15 Cortex M0+ System Tick Interrupt                   */

    IRQ00_NOR                   = 0,     /*!< GPIO Interrupt                                        */
                                         /* if GPIO Interrupt is changed from default of 0,         */
                                         /* ensure that all GPIOINT feeds in to new GPIO_IRQn.      */
                                         /* Also change vector table in boot_cm0pikmcu.c so that    */
                                         /* GPIO_IRQHandler is correctly set for new GPIO_IRQn.     */
                                         /*                                                         */
                                         /*!< maximum of 32 Interrupts are possible                 */
	IRQ01_PI2C                  = 1,
	IRQ02_MI2C                  = 2,
	IRQ03_FG                    = 3,
	IRQ04_FG2                   = 4,
	IRQ05_UART_TXD              = 5,
	IRQ06_PLC                   = 6,
	IRQ07_WDT                   = 7,
	IRQ08_TIMER0                = 8,
	IRQ09_TIMER1                = 9,
	IRQ10_TIMER2                = 10,
	IRQ11_TIMER3                = 11,
	IRQ12_WPT_COM               = 12,
	IRQ13_WPT_ADC               = 13,
	IRQ14_WPT_EXT_REG           = 14,
	IRQ15_SEL_GPIO_IN0          = 15,
	IRQ16_SEL_GPIO_IN1          = 16,
	IRQ17_RESERVED              = 17,
	IRQ18_GPIO_EDGE_TRIG        = 18,
	IRQ19_R_SC                  = 19,
	IRQ20_PM                    = 20,
	IRQ21_DET_POGO              = 21,
	IRQ22_DET_HALL              = 22,
	IRQ23_RESERVED              = 23,
	IRQ24_PI2C_AHB_ERR          = 24,
	IRQ25_MON_OUT1_NO_CLK       = 25,
	IRQ26_MON_OUT2_NO_CLK       = 26,
	IRQ27_A2D_WPT_NRST          = 27,
	IRQ28_PLC_R                 = 28,
	IRQ29_PLC_L                 = 29,
	IRQ30_RESERVED              = 30,
	IRQ31_RESERVED              = 31
} IRQn_Type;

typedef enum
{
    Vect_STACK                  = 0,
    Vect_RESET                  = 1,
    Vect_NMI                    = 2,
    Vect_HARDFAULT              = 3,
    Reserved_04                 = 4,
    Reserved_05                 = 5,
    Reserved_06                 = 6,
    Reserved_07                 = 7,
    Reserved_08                 = 8,
    Reserved_09                 = 9,
    Reserved_10                 = 10,
    Vect_SVC                    = 11,
    Reserved_12                 = 12,
    Reserved_13                 = 13,
    Vect_PENDSV                 = 14,
    Vect_SYSTICK                = 15,

    Vect_NOR                    = 16,

    // 1-3
    Vect_PI2C                   = 17,
    Vect_MI2C                   = 18,
    Vect_FG                     = 19,

    //4-7
    Vect_FG2                    = 20,
    Vect_UART_TXD               = 21,
    Vect_PLC                    = 22,
    Vect_WDT                    = 23,

    //8-11
    Vect_TIMER0                 = 24,
    Vect_TIMER1                 = 25,
    Vect_TIMER2                 = 26,
    Vect_TIMER3                 = 27,

    //12-15
    Vect_WPT_COM                = 28,
    Vect_WPT_ADC                = 29,
    Vect_WPT_EXT_REG            = 30,
    Vect_SEL_GPIO_IN0           = 31,

    //16-19
    Vect_SEL_GPIO_IN1           = 32,
    Reserved_33                 = 33,
    Vect_GPIO_EDGE_TRIG			= 34,
    Reverse_INT_SC		        = 35,

    //20-23
    INT_PM                   	= 36,
    Vect_DET_POGO              	= 37,
    Vect_DET_HALL              	= 38,
    Reserved_39           		= 39,

    //24-27
    Vect_I2C_AHB_ERR      		= 40,
    Vect_MON_OUT1_NO_CLK       	= 41,
    Vect_MON_OUT2_NO_CLK       	= 42,
    Vect_A2D_WPT_NRST          	= 43,

    //28-31
    Reserved_44               	= 44,
    Reserved_45                 = 45,
    Reserved_46                 = 46,
    Reserved_47                 = 47

} Num_Vect_Type;

typedef enum
{
	RET_OK	= 0,
	RET_FAIL = 1,
} ret_t;

#define ON  (1)
#define OFF (0)

#define TRUE  (1)
#define FALSE (0)

#define NACK 0
#define ACK 1

#define OR 0
#define AND 1

/*
 * ==========================================================================
 * ----------- Processor and Core Peripheral Section ------------------------
 * ==========================================================================
 */

/* Configuration of the Cortex M0+ Processor and Core Peripherals */
#define __MPU_PRESENT           1       /*!< cm0pikmcu can support an MPU                         */
#define __NVIC_PRIO_BITS        2       /*!< cm0pikmcu Supports 2 Bits for the Priority Levels    */
#define __VTOR_PRESENT          1       /*!< cm0pikmcu can support the VTOR                       */
#define __Vendor_SysTickConfig  0       /*!< Set to 1 if different SysTick Config is used         */


#include "core_cm0plus.h"               /* Cortex M0+ processor and core peripherals              */

#include "stack.h"

#include "EXT_SRAM.h"

#include "peri_boot_con.h"
#include "peri_flash_con.h"
#include "peri_timer.h"
#include "peri_i2c.h"
#include "peri_uart.h"
#include "system_reg.h"
#include "peri_fg.h"
#include "peri_plc.h"
#include "peri_pm.h"
#include "peri_rgb.h"
#include "peri_sc.h"

#include "timer_drv.h"
#include "uart_drv.h"

#include "System.h"

#define b0  0x00000001
#define b1  0x00000002
#define b2  0x00000004
#define b3  0x00000008

#define b4  0x00000010
#define b5  0x00000020
#define b6  0x00000040
#define b7  0x00000080

#define b8  0x00000100
#define b9  0x00000200
#define b10 0x00000400
#define b11 0x00000800

#define b12 0x00001000
#define b13 0x00002000
#define b14 0x00004000
#define b15 0x00008000

#define b16 0x00010000
#define b17 0x00020000

#define SEC    1000
#define MINUTE 60*SEC

/**
 * Initialize the system clock
 *
 * @param  none
 * @return none
 *
 * @brief  Setup the microcontroller system
 *         Initialize the PLL and update the SystemFrequency variable
 */

typedef void (*const Boot_vect_t)(void);
typedef void (*const vect_t)(void);

typedef uint32_t EXP_REG_FN;
typedef uint32_t IRQ_REG_FN;
typedef void (*exception_fn_t)(void);
typedef void (*IRQ_fn_t)(void);


typedef struct
{
    // ======= exp_EXCEPTION_HANDLER[0] = STACK_BASE Address =======
    //  exception_function_t    exp_RESET_HANDLER;          //  1
    //  exception_function_t    exp_NMI_HANDLER;            //  2
    //  exception_function_t    exp_HARD_FAULT_HANDLER;     //  3
    //  exception_function_t    exp_RSVD04_HANDLER;
    //  exception_function_t    exp_BUS_FAULT_HANDLER;      //  5
    //  exception_function_t    exp_USAGE_FAULT_HANDLER;    //  6
    //  exception_function_t    exp_RSVD07_HANDLER;
    //  exception_function_t    exp_RSVD08_HANDLER;
    //  exception_function_t    exp_RSVD09_HANDLER;
    //  exception_function_t    exp_RSVD10_HANDLER;
    //  exception_function_t    exp_SVCALL_HANDLER;         //  11
    //  exception_function_t    exp_RSVD12_HANDLER;
    //  exception_function_t    exp_RSVD13_HANDLER;
    //  exception_function_t    exp_PENDSV_HANDLER;         //  14
    //  exception_function_t    exp_SYSTICK_HANDLER;        //  15
    EXP_REG_FN    exp_EXCEPTION_HANDLER[16];
} Exception_Entry_Type;


typedef struct
{
    IRQ_REG_FN                irq_INTERRUPT_HANDLER[32];
} IRQ_Entry_Type;


extern void reset_handler(void);
extern int main(void);

extern void SystemInit (void);

extern EXP_REG_FN register_exception_handler(uint32_t EXP_ID, exception_fn_t EXP_Handler);
extern IRQ_REG_FN register_irq_handler(uint32_t IRQ_ID, IRQ_fn_t IRQ_Handler);


// Exception Function Definition
#define EXCEPTION_TABLE_BASE        0x00000000
#define EXCEPTION_TBL               (*( Exception_Entry_Type *)    EXCEPTION_TABLE_BASE)

//  IRQ Function Definition
#define IRQ_TABLE_BASE              0x00000040
#define IRQ_TBL                     (*( IRQ_Entry_Type *)           IRQ_TABLE_BASE)


/******************************************************************************/
/*                         Peripheral memory map                              */
/******************************************************************************/
/* Peripheral and SRAM base address */
#define SRAM_BASE                   0x20000000
#define DATA_SRAM_BASE              0x20001000
#define EXT_SRAM_BASE               0x20002F00

#define FLASH_AREA_BASE             0x00000000
#define FLASH_CODE_BASE				0x00001000

#define FLASH_TRIM_FG_BASE			(FLASH_AREA_BASE + 0xBF00)


/* Peripheral memory map */
#define EXT_SRAM        (*(volatile EXT_SRAM_Type *) EXT_SRAM_BASE)

// Peripherals Definition
//
#define PERIPH_BASE         0xF0000000

// Modified by minsix in 2016.04.05
#define FLASHCON_BASE       (PERIPH_BASE + 0x0000)
#define SYSREG_BASE         (PERIPH_BASE + 0x1000)
#define BOOTCON_BASE		(PERIPH_BASE + 0x2000)
#define FG_BASE             (PERIPH_BASE + 0x3000)
#define RGB_BASE            (PERIPH_BASE + 0x6000)
#define PM_BASE             (PERIPH_BASE + 0x7000)
#define SC_BASE             (PERIPH_BASE + 0x8000)
#define MI2C_BASE           (PERIPH_BASE + 0x9000)
#define PI2C_BASE           (PERIPH_BASE + 0xA000)
#define UART_BASE           (PERIPH_BASE + 0xB000)
#define TIMER_BASE          (PERIPH_BASE + 0xD000)
#define PLC_BASE            (PERIPH_BASE + 0xE000)

#define WPT_TRIM_BASE       (PERIPH_BASE + 0x5130)

#define FLASHCON (*(volatile FLASHCON_BLOCK_Type *)FLASHCON_BASE)
#define SYSREG   (*(volatile SYSREG_BLOCK_Type *)SYSREG_BASE)
#define BOOTCON  (*(volatile BOOTCON_BLOCK_Type *)BOOTCON_BASE)
#define FG       (*(volatile FG_BLOCK_Type *)FG_BASE)
#define RGB      (*(volatile RGB_BLOCK_Type *)RGB_BASE)
#define PM       (*(volatile PM_BLOCK_Type *)PM_BASE)
#define SC       (*(volatile SC_BLOCK_Type *)SC_BASE)
#define PI2C     (*(volatile PI2C_BLOCK_Type *)PI2C_BASE)
#define MI2C     (*(volatile MI2C_BLOCK_Type *)MI2C_BASE)
#define UART     (*(volatile UART_BLOCK_Type *)UART_BASE)
#define TIMER    (*(volatile TIMER_BLOCK_Type *)TIMER_BASE)
#define PLC      (*(volatile PLC_BLOCK_Type *)PLC_BASE)

#define I2C_HOST_CMD_MODE       (*(volatile uint8_t *)(EXT_SRAM_BASE + 0x10))
#define I2C_HOST_CMD_SEL        (*(volatile uint8_t *)(EXT_SRAM_BASE + 0x11))
#define I2C_HOST_WR_DATA8       (*(volatile uint8_t *)(EXT_SRAM_BASE + 0x12))
#define I2C_HOST_WR_DATA16      (*(volatile uint16_t *)(EXT_SRAM_BASE + 0x12))
#define I2C_HOST_WR_DATA16_L    (*(volatile uint8_t *)(EXT_SRAM_BASE + 0x12))
#define I2C_HOST_WR_DATA16_H    (*(volatile uint8_t *)(EXT_SRAM_BASE + 0x13))
#define I2C_HOST_CMD_AREA       (*(volatile uint32_t *)(EXT_SRAM_BASE + 0x10))

#define I2C_SLV_DATA8           (*(volatile uint8_t *)(EXT_SRAM_BASE + 0x14))
#define I2C_SLV_DATA16          (*(volatile uint16_t *)(EXT_SRAM_BASE + 0x14))
#define I2C_SLV_DATA32          (*(volatile uint32_t *)(EXT_SRAM_BASE + 0x14))

// Definition Mode Select
#define MODE_BLANK					0x00
#define MODE_INT_CLEAR				0x01
#define MODE_REGISTER				0x02
#define MODE_INTERFACE				0x03
#define MODE_SELECT_SLEEP			0x0F
#define MODE_FLASH_UPDATE			0x10
#define MODE_FLASH_EXIT 			0x20
#define MODE_FLASH_CMD_ON			0x40
#define MODE_FLASH_ACCESS			0x42
#define MODE_FLASH_FULL_ERASE		0x44
#define MODE_FLASH_TRIM_UPDATE		0x4F

#define MODE_SRAM_READ				0xAA
#define MODE_TEST_FUNC				0xF0

// Definition Register Access Select
#define SEL_REG_BLANK				0x00
#define SEL_WRITE_BYTE				0x01
#define SEL_WRITE_WORD				0x02
#define SEL_WRITE_LONG				0x04
#define SEL_READ_BYTE				0x10
#define SEL_READ_WORD				0x20
#define SEL_READ_LONG				0x40

extern void sendchar(char ch);


#endif
