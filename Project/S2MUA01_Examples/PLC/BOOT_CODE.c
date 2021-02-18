/*
******************************************************************************
* @file    boot_code.c
* @author  Power Device Team
* @version V1.0.0
* @date    15-March-2016
* @brief   Boot System Function
******************************************************************************
*/

#include "cm0pikmcu.h"
#include "System.h"
#include "uart_cmd.h"
#include "common_drv.h"
#include "PLC.h"
#include "sc_drv.h"
#include "led_drv.h"

#include "wpc.h"
#include "wpc_common.h"

#pragma arm section code = "region_main_func"

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
	for (cnt = 0; cnt < 10000; cnt++)
	{
		__NOP();
	}
}

void charging_event(plc_t *plc)
{
	uint8_t stats;

	/* occur VBUS(CHGIN) interrupt */
	stats = sc_drv_get_chgin_status();

	//if (wpc_get_vrect_status() != TRUE)
	{
		if (stats == CHGIN_UNDER_UVLO || stats == CHGIN_VOLTAGE_LOW || stats == CHGIN_IN_SWITCH_IS_OFF)
		{
			if (plc_get_plc_mode(RIGHT) == PLC_MODE_LDO || plc_get_plc_mode(LEFT) == PLC_MODE_LDO)
			{
				//printf("BOOST, UNDER_UVLO\r\n");
				sc_drv_set_reg_mode(BST_MODE);
			}
			else
			{
				//printf("BUCK, UNDER_UVLO\r\n");
				sc_drv_set_reg_mode(BUCK_MODE);
			}
			plc[0].ta_in = FALSE;
		}
		
		if (stats == CHGIN_OVER_OVLO || stats == CHGIN_IN_CURRENT_IS_LIMITED_REGUL || stats == CHGIN_IS_VALID)
		{
			//printf("CHARGER, OVER_OVLO\r\n");
			sc_drv_set_reg_mode(CHG_MODE);
			plc[0].ta_in = TRUE;
		}
		//plc[0].wpt_in = FALSE;
	}
	/*
	else
	{
		printf("WPT CHARGER MODE\r\n");
		sc_drv_set_reg_mode(CHG_MODE);
		plc[0].wpt_in = TRUE;
	}
	*/
	if (wpc_get_vrect_status() != TRUE)
		plc[0].wpt_in = FALSE;
}

void POGO_Process(uint8_t dir, plc_t *plc)
{
	uint16_t vout, iout;
	static uint16_t detach_cnt_r, detach_cnt_l;

	if (plc_get_plc_mode(dir) == PLC_MODE_OFF)
	{
		//printf("POGO_Process LDO OFF\r\n");
		vout = pm_drv_get_vpogo(dir);
		if (vout < 100)
		{
			printf("POGO_Process < 100\r\n");		
			/* Enable LDO */
			plc_set_plc_mode(dir, PLC_MODE_LDO);

			/* If CHG_MODE is BUCK, you must turn on the Booster */
			if (sc_drv_get_reg_mode() == BUCK_MODE)
				sc_drv_set_reg_mode(BST_MODE);

			/* For PLC, VOUT need a difference between Vout and Booster more than 100mV  */
			sc_drv_set_bst_voltage(PLC_LDO_BST_4_7V);
			plc_set_plc_output(dir, PLC_LDO_4_6V);

			plc_init(dir, plc);

			if (dir == LEFT)
			{
				printf("Left attached\r\n");
				led_drv_set_mode_en(LED2_RED, LED_CONSTANT_MODE);
				plc[0].attach_l=TRUE; 
			}
			else
			{
				printf("Right attached\r\n");
				led_drv_set_mode_en(LED5_RED, LED_CONSTANT_MODE);
				plc[0].attach_r=TRUE;
			}
		}
	}
	else
	{
		iout = pm_drv_get_ipogo(dir);
		if (dir == LEFT)
		{
			/* If the Current is less than 3mA during 1sec (10ms X 100count), turn off LDO.
			   And Resetart detection.
			 */
			if (iout < 3)
				detach_cnt_l++;
			else
				detach_cnt_l = 0;

			if (detach_cnt_l > 100)
			{
				printf("Left detached, iout%d\r\n", iout);
				led_drv_set_mode_en(LED2_RED, LED_OFF_MODE);
				sysreg_drv_seten_det_reset_pogo(dir);
				sysreg_drv_seten_det_pogo(dir, ON);
				plc_set_plc_mode(dir, PLC_MODE_OFF);
				plc[0].attach_l=FALSE; 
			}
		}
		else
		{
			if (iout < 3)
				detach_cnt_r++;
			else
				detach_cnt_r = 0;

			if (detach_cnt_r > 100)
			{
				printf("Right detached, iout%d\r\n", iout);
				led_drv_set_mode_en(LED5_RED, LED_OFF_MODE);
				sysreg_drv_seten_det_reset_pogo(dir);
				sysreg_drv_seten_det_pogo(dir, ON);
				plc_set_plc_mode(dir, PLC_MODE_OFF);
				plc[0].attach_r=FALSE; 
			}
		}
	}
}

int main(void)
{
	uint32_t systime=0;
	uint32_t systime_1S=0;
	uint8_t temp=0, dir=0;
	
    //uint8_t mode=BUCK_MODE;
	plc_t plc[2];

	/*WPC Variables*/
	uint8_t first_flag = 1;
	uint8_t delay_ms = 0;
	uint32_t wpc_tick;
	wpc_config_t t_wpc_config;
	/*WPC Variables END*/
	
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

	/*WPC Init*/
	wpc_initialize(4800); /* Initial Vout Voltage 4.8V */
	wpc_set_identification_data(0x0001, 0x12345678);
	#if 0
	t_wpc_config.gain0   = 0x00;
	t_wpc_config.gain1   = 0x00;
	t_wpc_config.gain2   = 0x00;
	t_wpc_config.gain3   = 0x00;
	t_wpc_config.offset0 = 0x7F;
	t_wpc_config.offset1 = 0x7F;
	t_wpc_config.offset2 = 0x7F;
	t_wpc_config.offset3 = 0x7F;
	#else
	t_wpc_config.gain0   = 0x00;
	t_wpc_config.gain1   = 0x00;
	t_wpc_config.gain2   = 0x07;
	t_wpc_config.gain3   = 0x07;
	t_wpc_config.offset0 = 0x9C;
	t_wpc_config.offset1 = 0x9A;
	t_wpc_config.offset2 = 0x95;
	t_wpc_config.offset3 = 0x95;
	
	#endif
	wpc_set_fod(&t_wpc_config);

	wpc_set_plc_length(30); // PLC Length : 30mSec
	///*
	wpc_initialize_cb_function(eWPC_CB_FUNC_VOUT_ON,  wpc_cb_vout_on);
	wpc_initialize_cb_function(eWPC_CB_FUNC_CHG_MODE, wpc_cb_charger_mode);
	wpc_initialize_cb_function(eWPC_CB_FUNC_SEND_PLC, wpc_cb_can_send_plc);

	wpc_control_temp(eWPC_CTRL_TEMP_SET_NORMAL);
	//*/
	printf("START S2MUA01 : %s\r\n", BuildTime);
	
	wpc_tick = sys_get_tick();
	delay_ms = 10;

	SC.REG_70.BITS.EN_AZ = 0;
	sc_drv_set_switch_freq(SWITCH_FREQ_1M); //Noise Suppresion	

	set_memory_addr(plc);
	/*WPC Init End*/
	
	/* Turn off the output for POGO_DET */
	plc_set_plc_mode(LEFT, PLC_MODE_OFF);
	plc_set_plc_mode(RIGHT, PLC_MODE_OFF);

	/* Enable ADC of POGO */
	pm_drv_set_vpogo_co(ON);
	pm_drv_set_ipogo_co(ON);

	/* Detection must be set in the order below */
	sysreg_drv_seten_det_reset_pogo(LEFT);
	sysreg_drv_seten_det_reset_pogo(RIGHT);

	sysreg_drv_seten_det_pogo(LEFT, ON);
	sysreg_drv_seten_det_pogo(RIGHT, ON);
	
	systime_1S = systime = sys_get_tick();

	/* GPIO Selection */
	BOOTCON.GPIO_SRC_SEL.BITS.SRC_SEL_OUT_SWD = 1;
	BOOTCON.GPIO_SRC_SEL.BITS.SRC_SEL_IN_SWD = 1;
	BOOTCON.GPIO_OUT.BITS.GPIO_OUTx_14 = 0; //Hi-Z

	while (1)
	{
		if (plc[0].ta_in == FALSE)
		{
			if (wpc_get_vrect_status() == TRUE)
			{
				wpc_process(first_flag, delay_ms);
				first_flag = 0;
			}
			else
			{
				if (first_flag == 0)
				{
					first_flag = 1;
					wpc_end_process();
				}
			}

			if ((sys_get_tick() - wpc_tick) > 100)
				delay_ms = 29;
		}

		if (sys_get_tick() - systime > 10)
		{
			charging_event(plc);
			
			systime = sys_get_tick();

			//printf("plc[0].wpt_in (%d), plc addr(%#x) in Main\r\n", plc[0].wpt_in, plc);	

			POGO_Process(RIGHT, plc);
			POGO_Process(LEFT, plc);

			if((plc[0].attach_l == TRUE) || (plc[0].attach_r == TRUE))
			{
				plc_rx_process(RIGHT, plc);
				plc_rx_process(LEFT, plc);

				if(plc[0].wpt_in == FALSE)
				{
					//printf("plc_tx_process not in WPT mode\r\n");
					plc_tx_process(plc);
				}
			}
		}
		if (sys_get_tick() - systime_1S > 1000)
		{
			systime_1S = sys_get_tick();
			for(dir = LEFT; dir < BOTH; dir++)
			{
				temp=0;
				if(plc[0].ta_in == TRUE)
					temp |= PLC_CDL_STAT_VBUS_ON;
				else
				{
					if(plc[0].wpt_in)
						temp |= PLC_CDL_STAT_WCIN_ON;
					else
						temp &= 0xFC;
				}
				if((plc[0].attach_l == TRUE) && (plc[0].attach_r == TRUE))
					temp |= PLC_CDL_STAT_DOUBLE_BUD;
				else
				{	
					if((plc[0].attach_l == TRUE) || (plc[0].attach_r == TRUE))
						temp |= PLC_CDL_STAT_SINGLE_BUD;
					else
						temp &= 0x3F;
				}
				plc_msg_q(dir, PLC_HDR_STAT, 1, temp, plc);

			}

			//plc_msg_q(RIGHT, PLC_HDR_STAT, 1, temp, plc);
			printf("TA: %d WPC: %d ATTACH L(%d) R(%d)\r\n", plc[0].ta_in, plc[0].wpt_in, plc[0].attach_l, plc[0].attach_r);
			printf("PLC Status Data(%#x) L(%#x) R(%#x)\r\n", temp, plc[0].tx_state, plc[1].tx_state);
			
		}
	}
}

#pragma arm section code


