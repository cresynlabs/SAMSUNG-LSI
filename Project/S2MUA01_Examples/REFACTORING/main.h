/*
******************************************************************************
* @file    main.h
* @author  Power Device Team
* @version V1.0.0
* @date    15-March-2016
* @brief   Main System StartUp
******************************************************************************
*/

#include "cm0pikmcu.h"

//#include "PLC.h"
#include "chg_process.h"
#include "led_process.h"
#include "fg_process.h"
#include "pogo_process.h"
#include "wpt_process.h"
//#include "pm_process.h"

#ifndef __MAIN_H
#define __MAIN_H


#define DEBUG
#if defined (DEBUG)
#define DB(...) printf(__VA_ARGS__)
#else
#define DB(...)
#endif

//#define DEBUG_CURRENT
#if defined (DEBUG_CURRENT)
#define DB_C(...) printf(__VA_ARGS__)
#else
#define DB_C(...)
#endif

#define DEBUG_LED
#if defined (DEBUG_LED)
#define DB_L(...) printf(__VA_ARGS__)
#else
#define DB_L(...)
#endif

#define FG_DEBOUNCE_TIME_120S 7680


#define FG_ERROR_DELTA   0.50f


#define LED1_ON_TIME_HALL_CLOSE   3000	  //ms

#define CRADLE_READY_TIME 100

#define JUDGE_LEVEL_ABNORMAL_TEMP 5

#ifdef S2MUA01_WPC_IOP_BELKIN_WA
#define WPT_HIGH_TEMP_BELKIN_IN_VALUE       47
#endif
#ifdef S2MUA01_WPC_D2D_TEMP_CONTROL
#define WPT_D2D_HIGH_TEMP_CONTROL_IN_VALUE  43
#define WPT_D2D_HIGH_TEMP_CONTROL_OUT_VALUE 41
#endif

#define DELAYTIME_FOR_POGO                  60000 // 1min

#define WPT_VERY_LOW_TEMP_CHAR_CURR        0x01 // 50mA
#define WPT_LOW_TEMP_CHAR_CURR             0x03 // 100mA
#define WPT_NORMAL_TEMP_CHAR_CURR          0x0A // 275mA // cradle only or buds full
#define WPT_NORMAL_TEMP_CHAR_W_BUDS_CURR   0x03 // 100mA // with buds

#define WPT_VERY_LOW_TEMP_TMR               650  //min
#define WPT_LOW_TEMP_TMR                    650
#define WPT_NORMAL_TEMP_TMR                 240

#define WPT_TXID_SEND_CNT                   5
#define WPT_CS100_SEND_CNT                  5
#define WPT_TXID_SEND_TIME                  3000 // 1Sec
#define WPT_CS100_SEND_TIME                 3000 // 1Sec
#define WPT_CHG_ON_TIME                     150  // 150mSec

#define ENTER_LPM_MODE_TIME_ALONE           60000  // 1min
#define EVENT_DELAY_LOOP_NORMAL             10
#define EVENT_DELAY_LOOP_LPM                2

#define EVENT_DELAY_LOOP_SUB_NORMAL         1000
#define EVENT_DELAY_LOOP_SUB_LPM            60

enum {
	CHGIN_ON_EVENT						= 1 << 0,
	CHGIN_OFF_EVENT						= 1 << 1,
	CHG_DONE_EVENT						= 1 << 2,
	WCIN_ON_EVENT						= 1 << 3,
	WCIN_OFF_EVENT						= 1 << 4,
	VBUS_ON_EVENT						= 1 << 5,
	VBUS_OFF_EVENT						= 1 << 6,
	POGOR_ATTACH_WAIT_EVENT				= 1 << 7,
	POGOL_ATTACH_WAIT_EVENT				= 1 << 8,
	LPM_TIMER_RESET_EVENT				= 1 << 9,
	CHARGING_CURRENT_CHANGED_EVENT		= 1 << 10,
	HALL_OPEN_EVENT						= 1 << 11,
	HALL_CLOSE_EVENT					= 1 << 12,
};

typedef enum {
	POWER_STATE_READY,
	POWER_STATE_BUD,
	POWER_STATE_CHARGING,
	POWER_STATE_CHARGING_WITH_BUD,
	POWER_STATE_LPM,
} power_state_t;

typedef enum {
	LOW_TEMP_ERROR,
    LOW_TEMP_WARN,
    HIGH_TEMP_WARN,
    HIGH_TEMP_ERROR,
    NORMAL_TEMP
} temp_status_t;

typedef enum {
	LOW_TEMP_ERROR_IN,
	LOW_TEMP_ERROR_OUT,
    LOW_TEMP_WARN_IN,
    LOW_TEMP_WARN_OUT,
    HIGH_TEMP_WARN_IN,
    HIGH_TEMP_WARN_OUT,
    HIGH_TEMP_ERROR_IN,
    HIGH_TEMP_ERROR_OUT,
} temp_ctrl_status_t;

typedef enum {
	HALL_CLOSE,
	HALL_OPEN,
} hall_status_t;

enum {
	LPM_MODE,
	NORMAL_MODE,
};

struct s2mua01_data {
	power_state_t		power_state;
	uint32_t			event_flag;
	uint32_t			shutdown_enter_timer[2];
	uint32_t			lpm_enter_timer[2];
	uint8_t				pogo_attach;
	uint16_t			charging_current;
	uint8_t				chgin_attach;
	uint8_t				wcin_attach;
	uint8_t				charger_attach; /* chgin_attach || wcin_attach */
	uint8_t				chg_done;
	uint32_t			sys_time;
	uint32_t			loop_delay_pm;

	float				VBAT;
	struct pogo_data	*pogo;
	struct charger_data	*charger;
	struct led_data		*led;
	struct wpt_data		*wpt;
	struct fg_data		*fg;
	hall_status_t		hall_status;
	temp_status_t		temp_status;
	float				temp;
	uint8_t				op_mode;
};

typedef power_state_t(*pm_fp) (struct s2mua01_data *);

power_state_t power_state_lpm(struct s2mua01_data *main_data);
power_state_t power_state_ready(struct s2mua01_data *main_data);
power_state_t power_state_charging(struct s2mua01_data *main_data);
power_state_t power_state_bud(struct s2mua01_data *main_data);
power_state_t power_state_charging_with_bud(struct s2mua01_data *main_data);

void S2MUA01_Process(void);
#endif /* __MAIN_H */
