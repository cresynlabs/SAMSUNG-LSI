#include <stdlib.h>
#include "cm0pikmcu.h"

#include "main.h"
#include "PLC.h"
#include "uart_cmd.h"
#include "common_drv.h"
#include <string.h>
#include "uart_drv.h"
#include "fg_drv.h"
#include "sc_drv.h"
#include "wpc.h"
#include "wpc_common.h"

#pragma arm section code = "region_main_func"

const pm_fp power_state_machine[] = {
	power_state_ready,
	power_state_bud,
	power_state_charging,
	power_state_charging_with_bud,
	power_state_lpm,
};

/* reference value
LOW_TEMP_ERROR_IN,	LOW_TEMP_ERROR_OUT,	LOW_TEMP_WARN_IN,	LOW_TEMP_WARN_OUT,
HIGH_TEMP_WARN_IN,	HIGH_TEMP_WARN_OUT, HIGH_TEMP_ERROR_IN,	HIGH_TEMP_ERROR_OUT*/
const int temp_table[3][8] = {
#if 0//MCD
	{0, 2, 5, 7, 41, 39, 50, 48}, /* CHGIN */
	{0, 2, 5, 7, 43, 41, 45, 43}, /* WCIN */
	{0, 2, 5, 7, 43, 41, 50, 48}, /* BATT */
#else //CRESYN
	{0, 2, 5, 7, 40, 38, 45, 43}, /* CHGIN */
	{0, 2, 5, 7, 43, 41, 45, 43}, /* WCIN */
	{0, 2, 5, 7, 43, 41, 50, 48}, /* BATT */
#endif
};

/* charging current
LOW_TEMP_ERROR, LOW_TEMP_WARN, HIGH_TEMP_WARN, HIGH_TEMP_ERROR, NORMAL_TEMP */
const int current_table[3][5] = {
	{0x0, 0x7, 0x7, 0x0, 0xB}, /* CHGIN  0, 200, 200, 0, 300 */
	{0x0, 0x7, 0x7, 0x0, 0xB}, /* WCIN  0, 200, 200, 0, 300 */
	{0x0, 0x7, 0x7, 0x0, 0xB}, /* BAT  0, 200, 200, 0, 300 */	
};

uint32_t loopDelay1=0, loopDelay2=0;

uint8_t get_event(struct s2mua01_data *main_data, uint32_t event)
{  
// 해당 event가 참이면 해당비트 event비트를 main_data->event_flag를 0으로 초기화
	if (main_data->event_flag & event)
	{
		main_data->event_flag &= ~event;
		return TRUE;
	}

	return FALSE;
}

void hall_detect(struct s2mua01_data *main_data)
{
	hall_status_t prev_hall_status = main_data->hall_status;

    // hall 감지 레지스터 읽어오기
	main_data->hall_status = (hall_status_t)hall_drv_get_hall_status();

	if (prev_hall_status != main_data->hall_status)
	{
		main_data->event_flag |= LPM_TIMER_RESET_EVENT;
		if (main_data->hall_status)
			main_data->event_flag |= HALL_OPEN_EVENT;
		else
			main_data->event_flag |= HALL_CLOSE_EVENT;
	}
}

void charging_temp_table_process(struct s2mua01_data *main_data)
{
	chg_status_t temp_chg_status;
	float temp = fg_drv_get_temp();
	uint16_t prev_charging_current = main_data->charging_current;
	temp_status_t temp_status = NORMAL_TEMP;
	temp_status_t prev_temp_status = main_data->temp_status;

	main_data->temp = temp;
	//어떤 방식으로 충전이 되고 충전 방식판단하여 temp_chg_status 상태 설정  온도 체크를 위함  (판단 우선순위 CHGIN > WCIN > BATT)
	if (main_data->chgin_attach)
		temp_chg_status = CHGIN;
	else if (main_data->wcin_attach)
		temp_chg_status = WCIN;
	else
		temp_chg_status = BATT;

	if(temp_chg_status != BATT)
		main_data->charger_attach = TRUE;     //temp_chg_status가 BATT가 아닐때 
	else
		main_data->charger_attach = FALSE;
	
	switch(main_data->temp_status) //temp_table설정 값에 따라 temp_status 설정
	{
		case LOW_TEMP_ERROR 	:
			if (temp > temp_table[temp_chg_status][LOW_TEMP_ERROR_OUT])
				temp_status = LOW_TEMP_WARN;
			else
				temp_status = LOW_TEMP_ERROR;
			break;
		case LOW_TEMP_WARN 		:
			if (temp < temp_table[temp_chg_status][LOW_TEMP_ERROR_IN])
				temp_status = LOW_TEMP_ERROR;
			else if (temp > temp_table[temp_chg_status][LOW_TEMP_WARN_OUT])
				temp_status = NORMAL_TEMP;
			else
				temp_status = LOW_TEMP_WARN;			
			break;
		case HIGH_TEMP_WARN 	:
			if (temp < temp_table[temp_chg_status][HIGH_TEMP_WARN_OUT])
				temp_status = NORMAL_TEMP;
			else if (temp > temp_table[temp_chg_status][HIGH_TEMP_ERROR_IN])
				temp_status = HIGH_TEMP_ERROR;
			else
				temp_status = HIGH_TEMP_WARN;			
			break;
		case HIGH_TEMP_ERROR 	:
			if (temp < temp_table[temp_chg_status][HIGH_TEMP_ERROR_OUT])
				temp_status = HIGH_TEMP_WARN;
			else
				temp_status = HIGH_TEMP_ERROR;			
			break;
		case NORMAL_TEMP 	:
			if (temp > temp_table[temp_chg_status][HIGH_TEMP_WARN_IN])
				temp_status = HIGH_TEMP_WARN;
			else if (temp < temp_table[temp_chg_status][LOW_TEMP_WARN_IN])
				temp_status = LOW_TEMP_WARN;
			else
				temp_status = NORMAL_TEMP;			
			break;
		default :
			break;
	}
	//if(temp_status != NORMAL_TEMP)
	//	DB("!NORMAL_TEMP, main_data->temp_status %d temp %f \r\n", temp_status, temp);

	if(main_data->charger_attach)  //CHGIN OR WCIN일때만 충전전류 설정 
		main_data->charging_current = current_table[temp_chg_status][temp_status];

	if (prev_charging_current != main_data->charging_current)
		main_data->event_flag |= CHARGING_CURRENT_CHANGED_EVENT;  //이전 충전 전류와 현재 충전 전류가 다르면 main_data->event_flag는 CHARGING_CURRENT_CHANGED_EVENT 설정

	if (prev_temp_status != temp_status)
	{
		//DB("charging_temp_table_process - temp_status %d attach %d\r\n", temp_status, main_data->charger_attach);
		if (temp_status == LOW_TEMP_ERROR || temp_status == HIGH_TEMP_ERROR)
			led_queue_event(main_data->led, LED_TURN_ON_ERROR);
		else if (prev_temp_status == LOW_TEMP_ERROR || prev_temp_status == HIGH_TEMP_ERROR)
			led_queue_event(main_data->led, LED_TURN_OFF_ERROR);
	}

   // LOW,HIGH TEMP ERROR일때  ㅡmain_data->charger_attach를 FALSE 로 바꿔줌 
	if (temp_status == LOW_TEMP_ERROR || temp_status == HIGH_TEMP_ERROR)
	{
		main_data->charger_attach = FALSE;
	}

	main_data->temp_status = temp_status;    //설정된 temp_status 값을 main_data 구조체에 넣어줌
}

void monitor_work(struct s2mua01_data *main_data)
{
	uint8_t prev_charger_attach = main_data->charger_attach;

	/* check pogo status */
	//get_event : 각 event의  event_flag가 참이면 각 main_data 구조체 항목을 설정 
	if (get_event(main_data, POGOR_ATTACH_WAIT_EVENT))
		main_data->pogo_attach |= RIGHT;

	//DB("main_data->pogo_attach(R) %x \r\n", main_data->pogo_attach);

	if (get_event(main_data, POGOL_ATTACH_WAIT_EVENT))
		main_data->pogo_attach |= LEFT;

	//DB("main_data->pogo_attach(L) %x \r\n", main_data->pogo_attach);

	/* check vbus status */
	if (get_event(main_data, CHGIN_ON_EVENT))
		main_data->chgin_attach = TRUE;

	if (get_event(main_data, CHGIN_OFF_EVENT))
		main_data->chgin_attach = FALSE;

	if (get_event(main_data, WCIN_ON_EVENT))
		main_data->wcin_attach = TRUE;

	if (get_event(main_data, WCIN_OFF_EVENT))
		main_data->wcin_attach = FALSE;

	if (get_event(main_data, CHG_DONE_EVENT))
		main_data->chg_done = TRUE;

	charging_temp_table_process(main_data);

	hall_detect(main_data);

	if (get_event(main_data, HALL_OPEN_EVENT) && (!main_data->charger_attach))
	{
	// hall : open, 배터리만 연결되어 있을때 진입 
		if (main_data->fg->soc < 0.25)
			led_queue_event(main_data->led, LED_BATTERY_CHECK_0_25);
		else if (main_data->fg->soc < 0.5)
			led_queue_event(main_data->led, LED_BATTERY_CHECK_25_50);
		else if (main_data->fg->soc < 0.75)
			led_queue_event(main_data->led, LED_BATTERY_CHECK_50_75);
		else
			led_queue_event(main_data->led, LED_BATTERY_CHECK_75_100);
	}

	/* VBUS Check */
	if (prev_charger_attach != main_data->charger_attach)
	{
		if (main_data->charger_attach)
		{
			if (main_data->chg_done)
				led_queue_event(main_data->led, LED_TURN_ON_FULL_CHARGING);
			else
			{
				if (main_data->fg->soc < 0.25)
					led_queue_event(main_data->led, LED_TURN_ON_CHARGING_0_25);
				else if (main_data->fg->soc < 0.5)
					led_queue_event(main_data->led, LED_TURN_ON_CHARGING_25_50);
				else if (main_data->fg->soc < 0.75)
					led_queue_event(main_data->led, LED_TURN_ON_CHARGING_50_75);
				else
					led_queue_event(main_data->led, LED_TURN_ON_CHARGING_75_99);
			}
		}
		else
		{
			DB_L("monitor_work(LED_TURN_OFF_CHARGING)\r\n");
			led_queue_event(main_data->led, LED_TURN_OFF_CHARGING);
		}
	}
}

power_state_t power_state_lpm(struct s2mua01_data *main_data)
{
	/* if there is any event, exit the lpm mode */
	if (main_data->event_flag || main_data->charger_attach)
	{
		main_data->op_mode = NORMAL_MODE;
		sysreg_drv_set_lpm(0);
		DB("power_state_lpm(wakeup) \r\n");
		return POWER_STATE_READY;
	}

	if (check_timer(main_data->sys_time,
				main_data->shutdown_enter_timer[main_data->hall_status]))
	{
		sysreg_drv_set_lpm(0);
		printf("SHUTDOWN --- S2MUA01\r\n");
		bootcon_drv_set_shutdown_mode(ON);
		return POWER_STATE_LPM;
	}

	return main_data->power_state;
}

power_state_t power_state_ready(struct s2mua01_data *main_data)
{
	if (main_data->charger_attach)
	{
		sc_drv_set_fast_charge_current(main_data->charging_current);
		sc_drv_set_reg_mode(CHG_MODE);
		DB("power_state_ready(main_data->charger_attach(%d))-CHG_MODE \r\n", main_data->charger_attach);
		return POWER_STATE_CHARGING;
	}

	if (main_data->pogo_attach)
	{
		sc_drv_set_reg_mode(BST_MODE);
		DB("power_state_ready(main_data->pogo_attach)-BST_MODE \r\n");
		return POWER_STATE_BUD;
	}

   //초기 main_data_int에 아래 플래그가 설정되어 sys_time값 설정해주고 아래 if문 타이머 실행 
   //Hall 상태가 변하면 LPM_TIMER_RESET_EVET 발생 하여 아래 check_timer sys_time 재설정 
	if (get_event(main_data, LPM_TIMER_RESET_EVENT))
		main_data->sys_time = sys_get_tick();

	if (check_timer(main_data->sys_time,
					main_data->lpm_enter_timer[main_data->hall_status]))
	{
		/* used by power_state_lpm to enter shutdown */
		main_data->sys_time = sys_get_tick();
		main_data->op_mode = LPM_MODE;
		sysreg_drv_set_lpm(1);  // 2번째 main if의 check timer의 printf문이 출력이 안됨
		return POWER_STATE_LPM;
	}

	return main_data->power_state;
}

power_state_t power_state_charging(struct s2mua01_data *main_data)
{
	if (get_event(main_data, CHARGING_CURRENT_CHANGED_EVENT))
		sc_drv_set_fast_charge_current(main_data->charging_current);

	if (!main_data->charger_attach)
	{
		main_data->charging_current = 0;
		sc_drv_set_reg_mode(BUCK_MODE);
		DB("power_state_charging(!main_data->charger_attach)-BUCK_MODE\r\n");
		return POWER_STATE_READY;
	}

	if (main_data->pogo_attach)
	{
		DB("power_state_charging(main_data->pogo_attach) \r\n");
		return POWER_STATE_CHARGING_WITH_BUD;
	}
	return main_data->power_state;
}

power_state_t power_state_bud(struct s2mua01_data *main_data)
{
	if (main_data->charger_attach)
	{
		sc_drv_set_fast_charge_current(main_data->charging_current);
		sc_drv_set_reg_mode(CHG_MODE);

		DB("power_state_bud(main_data->charger_attach)-CHG_MODE \r\n");
		return POWER_STATE_CHARGING_WITH_BUD;
	}

	if (!main_data->pogo_attach)
	{
		sc_drv_set_reg_mode(BUCK_MODE);
		DB("power_state_bud(!main_data->pogo_attach)-BUCK_MODE \r\n");
		return POWER_STATE_READY;
	}

	/* TODO
	if (pogo full)
		start timer for shutdown
	*/

	return main_data->power_state;
}

power_state_t power_state_charging_with_bud(struct s2mua01_data *main_data)
{
	if (get_event(main_data, CHARGING_CURRENT_CHANGED_EVENT))
		sc_drv_set_fast_charge_current(main_data->charging_current);

	if (!main_data->charger_attach)
	{
		main_data->charging_current = 0;
		sc_drv_set_reg_mode(BST_MODE);
		DB("power_state_charging_with_bud(!main_data->charger_attach)-BST_MODE\r\n");
		return POWER_STATE_BUD;
	}
    // R/L 둘다 떨어져야 함
	if (!main_data->pogo_attach)
	{
		DB("power_state_charging_with_bud(!main_data->pogo_attach) \r\n");
		return POWER_STATE_CHARGING;
	}

	return main_data->power_state;
}

void main_data_init(struct s2mua01_data *main_data)
{
	main_data->power_state = POWER_STATE_READY;
	main_data->event_flag = LPM_TIMER_RESET_EVENT; /* for initial timer setting */
	main_data->temp_status = NORMAL_TEMP;
	main_data->hall_status = HALL_CLOSE;
	main_data->lpm_enter_timer[HALL_OPEN] = 60000; /* 1 min */
	main_data->lpm_enter_timer[HALL_CLOSE] = 5000; /* 5 sec */

	main_data->shutdown_enter_timer[HALL_OPEN] = 7680; /* 2 min */
	main_data->shutdown_enter_timer[HALL_CLOSE] = 3840; /* 1 min */

	main_data->op_mode = NORMAL_MODE;

	main_data->pogo_attach = 0;
	main_data->chgin_attach = 0;
	main_data->wcin_attach = 0;
	main_data->charging_current = 0;

	main_data->charger_attach = FALSE;
	main_data->chg_done = FALSE;

	main_data->loop_delay_pm = 0;

	main_data->wpt = wpt_main_init();
	main_data->charger = charger_init();
	main_data->led = led_init();
	main_data->pogo = pogo_init();
	main_data->fg = fg_init();
}

void variable_area_clear(void)
{
	uint32_t *ClrAdr, ulCnt;

	ClrAdr = (uint32_t *)(DATA_AREA_BASE);
	for (ulCnt = 0; ulCnt < (FLASH_DUMP_SIZE / 4); ulCnt++)
		ClrAdr[ulCnt] = 0;

	ClrAdr = (uint32_t *)(EXT_SRAM_BASE + 0x10);
	for (ulCnt = 0; ulCnt < 16; ulCnt++)
		ClrAdr[ulCnt] = 0xFFFFFFFF;
}

void delay_for_stablization(void)
{
	uint32_t cnt;
	for (cnt = 0; cnt < 10000;cnt++)
	{
		__NOP();
	}
}

int main(void)
{
	struct s2mua01_data *main_data;
	uint32_t ult=0, ult_low=0, loopDelay1=0, loopDelay2=0;
	static uint32_t ulWPTdelay_ms = 0;
	power_state_t next_state;

	uint8_t vtempi2c;
	uint32_t vtemp;
	NVIC_EnableIRQ(IRQ22_DET_HALL);

	NVIC->ICER[0] = (uint32_t)0xFFFFFFFF;       /* Disable All IRQ */
	NVIC->ICPR[0] = (uint32_t)0xFFFFFFFF;       /* Interrupt Pending Clear */

	/* OM LOW Debounce time */
	SYSREG.OM_DBNC_PDLY.BITS.OM_DBNC_PDLY = 0x8000; /* 0x8000 =2 ms */
	SYSREG.DMA_Flash.BITS.PI2C_TO_FLASH_AUTO_PGM = 0;
	PM.REG_4C.BITS.VBAT1CO = 1;

	systimer_initialize();
	NVIC_EnableIRQ(IRQ00_NOR);
	variable_area_clear();
	gpio_drv_set_to_uart();
	uart_drv_init();

	delay_for_stablization();

	/*-------- while start here -----------*/
	ult = sys_get_tick();
	ult_low = sys_get_tick();
	ulWPTdelay_ms = sys_get_tick();

	loopDelay1 = EVENT_DELAY_LOOP_NORMAL;
	loopDelay2 = EVENT_DELAY_LOOP_SUB_NORMAL;

//	SYSREGDrvSetWDT();


	main_data = malloc(sizeof(struct s2mua01_data));
	if (!main_data)
	{
		printf("%s, failed to allocate main driver data\r\n", __func__);
		return 0;
	}

	main_data_init(main_data);
	
	fg_drv_set_if_en(3);
	vtemp = FG.VTEMP_I2C.DATA;
	//FG.VTEMP_I2C.DATA = (vtemp & 0xFFFFFF00) | 0xCD;
	FG.VTEMP_I2C.DATA = (vtemp & 0xFFFFFF00) | 0xB9;
	printf("%s, S2MUA01 is Loaded, %x\r\n", __func__, FG.VTEMP_I2C.DATA );

	while(1)
	{
		/*Determines whether the WPT is connected while the MCU is awake.*/
		if (check_timer(ulWPTdelay_ms, 100) &&
						(main_data->wpt->uWPTdelayFlag == 0))
			main_data->wpt->uWPTdelayFlag = 1;

		WPTProcess(main_data->wpt);

		if (main_data->op_mode == LPM_MODE) {
			loopDelay1 = EVENT_DELAY_LOOP_LPM;
			loopDelay2 = EVENT_DELAY_LOOP_SUB_LPM;
		} else {
			loopDelay1 = EVENT_DELAY_LOOP_NORMAL;
			loopDelay2 = EVENT_DELAY_LOOP_SUB_NORMAL;
		}

		if (check_timer(ult, loopDelay1)) {
			ult = sys_get_tick();

			charger_poll(main_data->charger, &main_data->event_flag);
			/* PM_Poll(&main_data->event_flag); */
			fuelgauge_poll(main_data->fg);

            // 포고R/L detect 감지 
			pm_poll(main_data);

			monitor_work(main_data);

			while (1) {

			
				//초기 power_state : ready 
				next_state = power_state_machine[main_data->power_state](main_data);
				if (next_state == main_data->power_state)
					break;
				
				if (next_state == POWER_STATE_READY) 
				{
				//lpm상태에서  power_state_ready 상태로  바뀌면   아래 플래그를 더 설정 해준다  그래야 power_state_ready 함수의 main_data->sys_time를 설정할 수 있다. 
					main_data->event_flag |= LPM_TIMER_RESET_EVENT;
				}
				
				main_data->power_state = next_state;
			}

			if (main_data->pogo_attach)
				main_data->pogo_attach = pogo_state_engine(main_data->pogo,
													main_data->pogo_attach);

			led_queue_task(main_data->led);

			/* clear event flag */
			main_data->event_flag = 0;
		}

		if (check_timer(ult_low, loopDelay2)) {
			ult_low = sys_get_tick();
			
			//온도 값 레지스터
		    vtempi2c = (uint8_t)(FG.VTEMP_I2C.DATA & 0xFF);
			vtemp	 = FG.VTEMP_I2C.DATA;

	
			printf("hall_s : %d, power_s : %x, pogo : %x, chgin : %x, wcin : %x, temp_s : %d, current : %x, temp %f, VTEMPI2C %x\r\n",
						main_data->hall_status,
						main_data->power_state, main_data->pogo_attach,
						main_data->chgin_attach, main_data->wcin_attach,
						main_data->temp_status, main_data->charging_current,
						main_data->temp, vtempi2c);

			led_print_out(main_data->led);
    
			if(vtempi2c < 0x9B)
			     FG.VTEMP_I2C.DATA = (vtemp & 0xFFFFFF00) | 0xCD;
			else
			{
				vtempi2c -=2;
				FG.VTEMP_I2C.DATA = (vtemp & 0xFFFFFF00) | vtempi2c;
			}
			
		}

		sysreg_drv_set_wdt_reset();
	}
	//return 0;
}

#pragma arm section code
