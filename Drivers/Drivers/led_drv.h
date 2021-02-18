#include "cm0pikmcu.h"

#ifndef __LED_DRV_H
#define __LED_DRV_H

enum {
	LED_OFF_MODE,
	LED_CONSTANT_MODE,
	LED_BLINK_MODE ,
};

enum {
	LED_DURATION_100MS,
	LED_DURATION_200MS,
	LED_DURATION_300MS,
	LED_DURATION_400MS,
	LED_DURATION_500MS,
	LED_DURATION_750MS,
	LED_DURATION_1000MS,
	LED_DURATION_1250MS,
	LED_DURATION_1500MS,
	LED_DURATION_1750MS,
	LED_DURATION_2000MS,
	LED_DURATION_2250MS,
	LED_DURATION_2500MS,
	LED_DURATION_2750MS,
	LED_DURATION_3000MS,
	LED_DURATION_3250MS,
};

enum {
	LED_RAMP_UP_0MS,
	LED_RAMP_UP_100MS,
	LED_RAMP_UP_200MS,
	LED_RAMP_UP_300MS,
	LED_RAMP_UP_400MS,
	LED_RAMP_UP_500MS,
	LED_RAMP_UP_600MS,
	LED_RAMP_UP_700MS,
	LED_RAMP_UP_800MS,
	LED_RAMP_UP_1000MS,
	LED_RAMP_UP_1200MS,
	LED_RAMP_UP_1400MS,
	LED_RAMP_UP_1600MS,
	LED_RAMP_UP_1800MS,
	LED_RAMP_UP_2000MS,
	LED_RAMP_UP_2200MS,
};
/* LED_CTRL1 */
#define LED_50UASTEP_12MA_OUTPUT       0
#define LED_100UASTEP_25P5MA_OUTPUT    1

/* LED_CTRL2
 LED ON/OFF sequencce selction, ONLY correspond to "BLINK MODE" */
#define LED_BLINK_ON_TO_OFF            0
#define LED_BLINK_OFF_TO_ON_TO_OFF     1

typedef enum {
	LED1_BLUE = 1,
	LED2_RED = 1 << 1,
	LED3_GREEN = 1 << 2,
	LED4_GREEN = 1 << 3,
	LED5_RED = 1 << 4,
	LED2_3_YELLOW = 1 << 5,
	LED_UNKNOWN = 1 << 6,
} led_channel_t;

void led_drv_set_mode_en(uint8_t channel, uint8_t drivemode);
uint8_t led_drv_get_mode(uint8_t channel);
void led_drv_set_rampup_time(uint8_t channel, uint8_t time);
void led_drv_set_rampdn_time(uint8_t channel, uint8_t time);
void led_drv_set_current(uint8_t channel, uint8_t current);
void led_drv_set_ontime(uint8_t channel, uint8_t time);
void led_drv_set_offtime(uint8_t channel, uint8_t time);
void led_drv_set_led4_onoff_timedur(uint8_t data);
void led_drv_set_onoff_sequence(uint8_t onoffmode);
#endif /* __LED_DRV_H */
