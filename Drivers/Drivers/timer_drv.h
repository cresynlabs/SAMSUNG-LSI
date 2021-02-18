/*
******************************************************************************
* @file    timer_drv.h
* @author  Power Device Team
* @version V1.0.0
* @date    09-June-2016
* @brief
******************************************************************************
*/
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __TIMER_DRV_H
#define __TIMER_DRV_H

void timer0_irq_initialize(uint32_t usec);
void timer0_irq_start(void);
void timer0_irq_stop(void);
void timer1_irq_initialize(uint32_t sec);
void timer1_irq_start(void);
void timer1_irq_stop(void);

uint32_t get_timer0_val(void); /* for test */

#endif /* __TIMER_DRV_H */

