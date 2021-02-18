#ifndef __WPC_H
#define __WPC_H

#define MAINLOOP_WPT_RESTING            0
#define MAINLOOP_WPT_INIT               1
#define MAINLOOP_WPT_RUN                2

typedef void(*wpc_cb_func_fp_type)(uint8_t *pData);

typedef enum
{
	eWPC_CB_FUNC_VOUT_ON,
	eWPC_CB_FUNC_CHG_MODE,
	eWPC_CB_FUNC_SEND_PLC,
	eWPC_CB_FUNC_MAX
}eWPC_CB_FUNC_TYPE;

typedef struct
{
	uint8_t gain0;
	uint8_t offset0;
	uint8_t gain1;
	uint8_t offset1;
	uint8_t gain2;
	uint8_t offset2;
	uint8_t gain3;
	uint8_t offset3;
}wpc_config_t;

typedef enum
{
	WPC_EPT_NULL = 0x00,
	WPC_EPT_CHARGE_COMPLETE = 0x01,
	WPC_EPT_INTERNAL_FAULT = 0x02,
	WPC_EPT_OVER_TEMP = 0x03,
	WPT_EPT_OVER_VOLTAGE = 0x04,
	WPT_EPT_OVER_CURRENT = 0x05,
	WPT_EPT_BATTERY_FAULT = 0x06,
	WPT_EPT_NO_RESPONSE = 0x08
}eWPC_END_POWER_INFO;

typedef enum{
	eWPC_CTRL_TEMP_SET_HIGH,
	eWPC_CTRL_TEMP_SET_VERY_HIGH,
	eWPC_CTRL_TEMP_RET_HIGH,
	eWPC_CTRL_TEMP_RET_NORMAL,
	eWPC_CTRL_TEMP_SET_NORMAL
}eWPC_CTRL_TEMP_INFO;

void wpc_initialize(uint16_t vout);
void wpc_process(uint8_t first_check, uint8_t delay_ms);
void wpc_end_process(void);
uint8_t wpc_get_vrect_status(void);
void wpc_set_identification_data(uint16_t manufact_code, uint32_t basic_id);
void wpc_set_fod(wpc_config_t *t_wpc_config);
void wpc_set_vrect_adj(int16_t adj);
void wpc_send_endpower(eWPC_END_POWER_INFO ecode);
void wpc_send_chargestatus(uint8_t status);
void wpc_control_temp(eWPC_CTRL_TEMP_INFO temp);
void wpc_set_plc_length(uint8_t length);
uint8_t wpc_get_plc_status(void);
void wpc_initialize_cb_function(eWPC_CB_FUNC_TYPE eIRQ, wpc_cb_func_fp_type CallBackFunc);
void wpc_set_tick(uint32_t tick);
void boot_wpt_com_irqhandler(void);
void boot_wpt_adc_irqhandler(void);
void boot_wpt_ext_reg_irqhandler(void);

#endif
