#include <stdlib.h>
#include "cm0pikmcu.h"

#include "main.h"
#include "led_drv.h"
#include "common_drv.h"

void led_control_constant(struct led_data *led)
{
	led_constant_state_t state = led->constant_state;
	uint8_t led_type = led->type;

	led->mode = LED_CONSTANT;

	//DB_L("state %d type %d \r\n", state, led->type);
	switch (state) {
	case LED_CONS_STATE_READY:
		led_drv_set_ontime(led_type, 0x0F);
		led_drv_set_offtime(led_type, 0);

		led_drv_set_onoff_sequence(0);

		led_drv_set_rampup_time(led_type, 0x01);
		led_drv_set_rampdn_time(led_type, 0x01);

		led_drv_set_mode_en(led_type, LED_BLINK_MODE);
		led->sys_time = sys_get_tick();
		//led->constant_state = LED_CONS_STATE_RAMPUP;
		break;
	case LED_CONS_STATE_RAMPUP:
		if (check_timer(led->sys_time, 300))
		{
			led_drv_set_mode_en(led_type, LED_CONSTANT_MODE);
			if (led->sys_timer)
				led->sys_time = sys_get_tick();
			//led->constant_state = LED_CONS_STATE_ON;
		}
		break;
	case LED_CONS_STATE_ON:
		if (led->sys_timer)
		{
			if (check_timer(led->sys_time, led->sys_timer))
				led->constant_state = LED_CONS_STATE_PRE_RAMPDN;
		}
		break;
	case LED_CONS_STATE_PRE_RAMPDN:
		led_drv_set_rampup_time(led_type, 0);
		led_drv_set_ontime(led_type, 0x00);
		led_drv_set_offtime(led_type, 0x0F);
		led_drv_set_mode_en(led_type, LED_BLINK_MODE);
		led->sys_time = sys_get_tick();
		led->constant_state = LED_CONS_STATE_RAMPDN;

		DB_L("LED_CONS_STATE_PRE_RAMPDN\r\n");
		break;
	case LED_CONS_STATE_RAMPDN:
		if (check_timer(led->sys_time, 300))
		{
			led_drv_set_mode_en(led_type, LED_CONSTANT_MODE);
			led->constant_state = LED_CONS_STATE_OFF;
			DB_L("LED_CONS_STATE_RAMPDN\r\n");
		}
		break;
	case LED_CONS_STATE_OFF:
		led_drv_set_mode_en(led_type, LED_OFF_MODE);
		led->event = LED_NONE;
		DB_L("LED_CONS_STATE_OFF\r\n");
		break;
	default:
		break;
	}
}	

void led_control_blink(struct led_data *led, uint8_t ontime, uint8_t offtime)
{
	uint8_t led_type = led->type;
	led_blink_state_t state = led->blink_state;

	switch (state) {
	case LED_BLINK_STATE_READY:
		led->mode = LED_BLINK;

		led_drv_set_ontime(led_type, ontime);
		led_drv_set_offtime(led_type, offtime);

		led_drv_set_onoff_sequence(0);

		led_drv_set_rampup_time(led_type, 0x00);
		led_drv_set_rampdn_time(led_type, 0x00);

		led_drv_set_mode_en(led_type, LED_BLINK_MODE);
		led->sys_time = sys_get_tick();
		led->blink_state = LED_BLINK_STATE_ON;
		break;
	case LED_BLINK_STATE_ON:
		if (led->sys_timer)
		{
			if (check_timer(led->sys_time, led->sys_timer))
				led->blink_state = LED_BLINK_STATE_OFF;
			DB_L("led_control_blink(LED_BLINK_STATE_ON)\r\n");
		}
		break;
	case LED_BLINK_STATE_OFF:
		led_drv_set_mode_en(led_type, LED_OFF_MODE);
		DB_L("led_control_blink(LED_BLINK_STATE_OFF)\r\n");
		led->event = LED_NONE;
		break;
	default:
		break;
	}
}

void led_control_process(struct led_data *led, led_event_t led_event)
{
	switch (led_event) {
	case LED_BATTERY_CHECK_0_25:
		led->type = LED1_BLUE;
		led->sys_timer = 3000;
		led_control_constant(led);
		break;
	case LED_BATTERY_CHECK_25_50:
		led->type = LED1_BLUE | LED2_RED;
		led->sys_timer = 3000;
		led_control_constant(led);
		break;
	case LED_BATTERY_CHECK_50_75:
		led->type = LED1_BLUE | LED2_RED | LED3_GREEN;
		led->sys_timer = 3000;
		led_control_constant(led);
		break;
	case LED_BATTERY_CHECK_75_100:
		led->type = LED1_BLUE | LED2_RED | LED3_GREEN | LED4_GREEN;
		led->sys_timer = 3000;
		led_control_constant(led);
		break;

	case LED_TURN_ON_CHARGING_0_25:
		led->type = LED1_BLUE;
		led->sys_timer = 0;
		led_control_blink(led, 0x04, 0x01);
		break;
	case LED_TURN_ON_CHARGING_25_50:
		led->type = LED1_BLUE;
		led->sys_timer = 0;
		led_control_constant(led);

		led->type = LED2_RED;
		led_control_blink(led, 0x04, 0x01);
		break;
	case LED_TURN_ON_CHARGING_50_75:
		led->type = LED1_BLUE | LED2_RED;
		led->sys_timer = 0;
		led_control_constant(led);

		led->type = LED3_GREEN;
		led_control_blink(led, 0x04, 0x01);
		break;
	case LED_TURN_ON_CHARGING_75_99:
		led->type = LED1_BLUE | LED2_RED | LED3_GREEN;
		led->sys_timer = 0;
		led_control_constant(led);

		led->type = LED4_GREEN;
		led_control_blink(led, 0x04, 0x01);
		break;
	case LED_TURN_ON_FULL_CHARGING:
		led->type = LED1_BLUE | LED2_RED | LED3_GREEN | LED4_GREEN;
		led->sys_timer = 0;
		led_control_constant(led);
		break;

	case LED_TURN_OFF_CHARGING:
		led->type = LED1_BLUE | LED2_RED | LED3_GREEN | LED4_GREEN;
		led->sys_timer = 0;
		led_control_constant(led);
		break;
	case LED_TURN_ON_ERROR:
		led->type = LED2_RED;
		led->sys_timer = 0;
		led_control_blink(led, 0x04, 0x01);
		break;
	case LED_TURN_OFF_ERROR:
		led->blink_state = LED_BLINK_STATE_OFF;
		led_control_blink(led, 0x00, 0x00);
		break;
	case LED_TURN_ON_COUPLING:
		led->type = LED3_GREEN;
		led->sys_timer = 7000; /* 7s */
		led_control_blink(led, 0x04, 0x01);
		break;
	case LED_ALL_OFF:
		led->event = LED_NONE;
		break;
	default:
		break;
	}
}

void led_queue_event(struct led_data *led, led_event_t led_event)
{
	led->rq = (led->rq + 1) % LED_QUEUE_MAX;
	led->led_queue[led->rq] = led_event;
}

led_event_t led_queue_pop(struct led_data *led)
{
	led->fq = (led->fq + 1) % LED_QUEUE_MAX;
	return led->led_queue[led->fq];
}

void led_queue_task(struct led_data *led)
{
	led_event_t led_event = (led_event_t)0;

	/* if queue is not empty, execuate pop */
	if (led->fq != led->rq)
		led_event = led_queue_pop(led);

   //현재 LED동작 보다 우선순위가 높을대 
	if (led_event > led->event)
	{
		/* if turn off event occured, do not init the current led state */
		if (led_event == LED_TURN_OFF_CHARGING)
		{
			led->constant_state = LED_CONS_STATE_PRE_RAMPDN;
			DB_L("constant_state %d\r\n", led->constant_state);
		}
		else
		{
			/* close previos led process */
			led_drv_set_mode_en(LED1_BLUE | LED2_RED | LED3_GREEN | LED4_GREEN, LED_OFF_MODE);

			led->constant_state = LED_CONS_STATE_READY; 
			led->blink_state = LED_BLINK_STATE_READY; 
		}
		led->event = led_event;
	}

	led_control_process(led, led->event);

	return;
}

void led_print_out(struct led_data *led)
{
	printf("event : %x, cons state : %x, blink state : %x\r\n\n",
			led->event, led->constant_state, led->blink_state);
}

struct led_data *led_init(void)
{
	struct led_data *led;

	led = malloc(sizeof(struct led_data));
	if (!led)
	{
		printf("%s, failed to allocate LED driver data\r\n", __func__);
		return led;
	}

	led->led_queue = malloc(sizeof(led_event_t) * LED_QUEUE_MAX);
	led->fq = 0;
	led->rq = 0;
	led->event = LED_NONE;
	led_drv_set_current(LED1_BLUE | LED2_RED | LED3_GREEN | LED4_GREEN | LED5_RED, 0x06);

	return led;
}
