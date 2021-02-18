/*
******************************************************************************
* @file    fg_drv.h
* @author  Power Device Team
* @version V1.0.0
* @brief   Header for StartUp
******************************************************************************
*/
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __FG_DRV_H
#define __FG_DRV_H

#define SOC_RESOLUTION		0.39f

#define MODE_CHANGE_CURR_MIN_CURR  -0.076f /* 0.048*-1.6  (48mA * -1.6) */
#define MODE_CHANGE_CURR_MAX_CURR  -0.01f
#define MODE_CHANGE_CHAR_VOLT_GAIN  4.3251f /* 4.35*0.996-0.0075 */

void fg2_irq_enable(void);
void boot_fg2_irqhandler(void);
void fg_drv_set_if_en(char data);
void fg_drv_set_batcap_ocv_en(char data);
void fg_drv_set_batcap_ocv(uint16_t data);
void fg_drv_set_batcap(uint16_t data);
void fg_drv_set_start(void);
void fg_drv_set_restart(void);
void fg_drv_set_soc_i2c(float data);
float fg_drv_get_soc_r(void);
void fg_drv_set_soc_flag(uint8_t data);
float fg_drv_show_soc(uint8_t chin, float soc);
void fg_drv_set_design_cap(uint16_t data);

float fg_drv_get_cur_cc(void);
float fg_drv_get_cur_cc_avg(void);
float fg_drv_get_temp(void);
float fg_drv_get_vbat_avg(void);
void fg_drv_set_ocv_soc_rs_lut(void);
float fg_drv_get_vbat(void);
uint8_t fg_drv_get_fg_surge(void);
void fg_drv_set_init_done(void);
void fg_drv_set_voltage_mode(uint8_t enable);
void fg_drv_set_inc_ok_en(uint8_t enable);
void fg_drv_set_edv(uint8_t data);

#endif /* __FG_DRV_H */
