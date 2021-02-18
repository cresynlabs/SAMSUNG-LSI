/*
******************************************************************************
* @file    peri_timer.h
* @author  Power Device Team
* @version V1.0.0
* @date    2015.01.27
* @brief   Header for Timer Block
******************************************************************************
*/
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef _PERI_TIMER_H_
#define _PERI_TIMER_H_

typedef union
{
    uint32_t DATA;
    struct {
        uint32_t   TE0:1,
                   TMD0:1,
                   TCLR0:1,
                   Reserved1:1,
                   TE1:1,
                   TMD1:1,
                   TCLR1:1,
                   Reserved2:25;
  } BITS;
} TMOD_Type;

typedef union
{
    uint32_t DATA;
    struct {
        uint32_t   TDATA0:32;
  } BITS;
} TDATA0_Type;

typedef union
{
    uint32_t DATA;
    struct {
        uint32_t   TCNT0 :32;
  } BITS;
} TCNT0_Type;

typedef union
{
    uint32_t DATA;
    struct {
        uint32_t   TDATA1:32;
  } BITS;
} TDATA1_Type;

typedef union
{
    uint32_t DATA;
    struct {
        uint32_t   TCNT1 :32;
  } BITS;
} TCNT1_Type;

typedef union
{
    uint32_t DATA;
    struct {
        uint32_t   _32bit_Timer0_Interrupt_clear:1,
                   _32bit_Timer1_Interrupt_clear:1,
                   Reserved1:2,
                   Watchdog_Timer_Interrupt_clear:1,
                   Reserved2:27;
  } BITS;
} TINTSTAT_Type;

typedef union
{
    uint32_t DATA;
    struct {
        uint32_t   WDTVAL:18,
                   Reserved:11,
                   RST:1,
                   MODE:1,
                   EN:1;
  } BITS;
} WDTCON_Type;

typedef union
{
    uint32_t DATA;
    struct {
        uint32_t  WTCNT:32;
  } BITS;
} WTCNT_Type;

typedef struct
{
    TMOD_Type       	TMOD;			// 0x00
    TDATA0_Type     	TDATA0;			// 0x04
    TCNT0_Type      	TCNT0;			// 0x08
    TDATA1_Type     	TDATA1;			// 0x0C
    TCNT1_Type      	TCNT1;			// 0x10
    Reserved_Type     	RSVD_14;		// 0x14
    Reserved_Type      	RSVD_18;		// 0x18
    Reserved_Type     	RSVD_1C;		// 0x1C
    Reserved_Type      	RSVD_20;		// 0x20
    TINTSTAT_Type   	TINTSTAT;		// 0x24
    Reserved_Type   	RSVD_28;		// 0x28
    Reserved_Type   	RSVD_2C;		// 0x2C
    WDTCON_Type     	WDTCON;			// 0x30
    Reserved_Type   	RSVD_34;        // 0x34
    WTCNT_Type      	WTCNT;          // 0x38
} TIMER_BLOCK_Type;

#endif /* __TIMER_BLOCK_H */

