/*
******************************************************************************
* @file    system.h
* @author  Power Device Team
* @version V1.0.0
* @date    15-March-2016
* @brief
******************************************************************************
*/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __SYSTEM_H
#define __SYSTEM_H

#include "cm0pikmcu.h"

#define FW_MAJOR_VERSION	0x1302
#define FW_MINOR_VERSION	0x1004
#define VERSION 			"1004"

#define BuildDate	"Feb 18 2021 "
#define BuildTime	"12:55:27"

#define TICK_UNIT   (5333)  // 1ms

void systimer_initialize(void);
void sys_timer_stop(void);
void boot_systick_handler(void);
uint32_t sys_get_tick(void);

void sysdelay_ms(uint32_t delay_ms);
void sysdelay_us(uint32_t delay_us);

#endif /* __SYSTEM_H */


