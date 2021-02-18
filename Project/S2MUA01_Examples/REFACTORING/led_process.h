#include "led_drv.h"

#ifndef __LED_PROCESS_H
#define __LED_PROCESS_H

#define LED_QUEUE_MAX	20

typedef enum {
	LED_NONE,

	//배터리만 연결되어 있을때 배터리 레벨 체크 LED
	LED_BATTERY_CHECK_0_25,
	LED_BATTERY_CHECK_25_50,
	LED_BATTERY_CHECK_50_75,
	LED_BATTERY_CHECK_75_100,

	//CHGIN OR WCIN으로 연결되어 배터리 충전 중일때 배터리 레벨 체크 LED
	LED_TURN_ON_CHARGING_0_25,
	LED_TURN_ON_CHARGING_25_50,
	LED_TURN_ON_CHARGING_50_75,
	LED_TURN_ON_CHARGING_75_99,

    //CHGIN OR WCIN으로 충전 중이며 충전이 완료되었을때 LED
	LED_TURN_ON_FULL_CHARGING,

	//charger_attach 상태가 바뀌고 CHGIN OR WCIN 을 안했을때 (배터리로만 동작상태 )
	LED_TURN_OFF_CHARGING,

	LED_TURN_ON_ERROR,
	LED_TURN_OFF_ERROR,
	LED_TURN_ON_COUPLING,
	LED_ALL_OFF,
} led_event_t;

typedef enum {
	LED_CONS_STATE_READY,
	LED_CONS_STATE_RAMPUP,
	LED_CONS_STATE_ON,
	LED_CONS_STATE_PRE_RAMPDN,
	LED_CONS_STATE_RAMPDN,
	LED_CONS_STATE_OFF,
} led_constant_state_t;

typedef enum {
	LED_BLINK_STATE_READY,
	LED_BLINK_STATE_ON,
	LED_BLINK_STATE_OFF,
} led_blink_state_t;

typedef enum {
	LED_BLINK,
	LED_CONSTANT,
} led_op_mode_t;

struct led_data {
	led_event_t				event;
	uint32_t				sys_time;
	uint32_t				sys_timer;
	uint8_t					type;

	led_constant_state_t	constant_state;
	led_blink_state_t		blink_state;
	led_op_mode_t			mode;
	uint8_t					rq;
	uint8_t					fq;

	led_event_t				*led_queue;
};

void led_print_out(struct led_data *led);
void led_queue_task(struct led_data *led);
void led_queue_event(struct led_data *led, led_event_t led_event);
struct led_data *led_init(void);

#endif /* __LED_PROCESS_H */
