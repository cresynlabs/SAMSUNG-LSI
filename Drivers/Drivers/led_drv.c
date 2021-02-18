#include "led_drv.h"

void led_drv_set_mode_en(uint8_t channel, uint8_t mode)
{
	RGB_REG_40 reg_40;

	reg_40.DATA = RGB.REG_40.DATA;

	if (channel & LED1_BLUE)
		reg_40.BITS.LED1_EN = mode;
	if (channel & LED2_RED)
		reg_40.BITS.LED2_EN = mode;
	if (channel & LED3_GREEN)
		reg_40.BITS.LED3_EN = mode;
	if (channel & LED4_GREEN)
		reg_40.BITS.LED4_EN = mode;
	if (channel & LED5_RED)
		reg_40.BITS.LED5_EN = mode;

	RGB.REG_40.DATA = reg_40.DATA;
}

uint8_t led_drv_get_mode(uint8_t channel)
{
	RGB_REG_40 reg_40;

	reg_40.DATA = RGB.REG_40.DATA;

	switch(channel)
	{
	case LED1_BLUE:
		return reg_40.BITS.LED1_EN;
	case LED2_RED:
		return reg_40.BITS.LED2_EN;
	case LED3_GREEN:
		return reg_40.BITS.LED3_EN;
	case LED4_GREEN:
		return reg_40.BITS.LED4_EN;
	case LED5_RED:
		return reg_40.BITS.LED5_EN;
	}

	return 0;
}

/* 0~0.8s : 100ms-step, 0.8s~2.2s : 200ms-step */
void led_drv_set_rampup_time(uint8_t channel, uint8_t time)
{
	if (channel & LED1_BLUE)
		RGB.REG_44.BITS.LED1_RAMP_UP = time;
	if (channel & LED2_RED)
		RGB.REG_48.BITS.LED2_RAMP_UP = time;
	if (channel & LED3_GREEN)
		RGB.REG_48.BITS.LED3_RAMP_UP = time;
	if (channel & LED4_GREEN)
		RGB.REG_4C.BITS.LED4_RAMP_UP = time;
	if (channel & LED5_RED)
		RGB.REG_4C.BITS.LED5_RAMP_UP = time;
}

/* 0~0.8s : 100ms-step, 0.8s~2.2s : 200ms-step */
void led_drv_set_rampdn_time(uint8_t channel, uint8_t time)
{
	if (channel & LED1_BLUE)
		RGB.REG_44.BITS.LED1_RAMP_DN = time;
	if (channel & LED2_RED)
		RGB.REG_48.BITS.LED2_RAMP_DN = time;
	if (channel & LED3_GREEN)
		RGB.REG_48.BITS.LED3_RAMP_DN = time;
	if (channel & LED4_GREEN)
		RGB.REG_4C.BITS.LED4_RAMP_DN = time;
	if (channel & LED5_RED)
		RGB.REG_4C.BITS.LED5_RAMP_DN = time;
}

/* 0.1mA-step
 * 0x01 : 0.1mA, 0x0F : 1.5mA, 0xFF : 25.5mA
 * to use 25.5mA, STEP_CTRLx be set to 1 (LED_100UASTEP_25P5MA_OUTPUT) */
void led_drv_set_current(uint8_t channel, uint8_t current) // 각 LED 전류 설정 
{
	if (channel & LED1_BLUE)
		RGB.REG_40.BITS.LED1_CURR_SET = current;
	if (channel & LED2_RED)
		RGB.REG_40.BITS.LED2_CURR_SET = current;
	if (channel & LED3_GREEN)
		RGB.REG_44.BITS.LED3_CURR_SET = current;
	if (channel & LED4_GREEN)
		RGB.REG_44.BITS.LED4_CURR_SET = current;
	if (channel & LED5_RED)
		RGB.REG_44.BITS.LED5_CURR_SET = current;
}

/* 0.1s~0.5s : 100ms-step, 0.5S3.25s : 250ms-step
 * LED_DURATION_100MS      0x00
 * LED_DURATION_200MS      0x01
 * LED_DURATION_300MS      0x02
 * LED_DURATION_400MS      0x03
 * LED_DURATION_500MS      0x04
 * LED_DURATION_750MS      0x05
 * LED_DURATION_1000MS     0x06
 * LED_DURATION_1250MS     0x07
 * LED_DURATION_1500MS     0x08
 * LED_DURATION_1750MS     0x09
 * LED_DURATION_2000MS     0x0A
 * LED_DURATION_2250MS     0x0B
 * LED_DURATION_2500MS     0x0C
 * LED_DURATION_2750MS     0x0D
 * LED_DURATION_3000MS     0x0E
 * LED_DURATION_3250MS     0x0F */
void led_drv_set_ontime(uint8_t channel, uint8_t time)
{
	if (channel & LED1_BLUE)
		RGB.REG_48.BITS.LED1_ON_DUR = time;
	if (channel & LED2_RED)
		RGB.REG_48.BITS.LED2_ON_DUR = time;
	if (channel & LED3_GREEN)
		RGB.REG_4C.BITS.LED3_ON_DUR = time;
	if (channel & LED4_GREEN)
		RGB.REG_4C.BITS.LED4_ON_DUR = time;
	if (channel & LED5_RED)
		RGB.REG_50.BITS.LED5_ON_DUR = time;
}

void led_drv_set_offtime(uint8_t channel, uint8_t time)
{
	if (channel & LED1_BLUE)
		RGB.REG_48.BITS.LED1_OFF_DUR = time;
	if (channel & LED2_RED)
		RGB.REG_48.BITS.LED2_OFF_DUR = time;
	if (channel & LED3_GREEN)
		RGB.REG_4C.BITS.LED3_OFF_DUR = time;
	if (channel & LED4_GREEN)
		RGB.REG_4C.BITS.LED4_OFF_DUR = time;
	if (channel & LED5_RED)
		RGB.REG_50.BITS.LED5_OFF_DUR = time;
}

void led_drv_set_led4_onoff_timedur(uint8_t data)
{
	RGB.REG_50.BITS.ON_OFF_TIME_DUR4 = data;
}

/* LED ON/OFF sequencce selction, ONLY correspond to "BLINK MODE"
 * LED_BLINK_ON_TO_OFF            0
 * LED_BLINK_OFF_TO_ON_TO_OFF     1 */
void led_drv_set_onoff_sequence(uint8_t mode)
{
	RGB.REG_50.BITS.LED_ON_SEQ_SEL = mode;
}
