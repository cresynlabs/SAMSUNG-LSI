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
#include "common_drv.h"
#include "PLC.h"
#include "sc_drv.h"
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

typedef enum
{
	eWPC_TEST_TEMP_NORMAL,
	eWPC_TEST_TEMP_HIGH,
	eWPC_TEST_TEMP_VERY_HIGH
}eWPC_TEST_TEMP_TYPE;


int main(void)
{
	wpc_config_t t_wpc_config;
	uint8_t first_flag = 1;
	uint32_t wpc_tick;
	uint32_t wpc_temp_tick=0;
	uint8_t delay_ms = 0;
	eWPC_TEST_TEMP_TYPE etemptype;
	//eWPC_TEST_TEMP_TYPE eoldtemptype;

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

	wpc_initialize(4800); /* Initial Vout Voltage 4.8V */
	wpc_set_identification_data(0x0001, 0x12345678);

	t_wpc_config.gain0 = 0x00;
	t_wpc_config.gain1 = 0x00;
	t_wpc_config.gain2 = 0x00;
	t_wpc_config.gain3 = 0x00;
	t_wpc_config.offset0 = 0x7F;
	t_wpc_config.offset1 = 0x7F;
	t_wpc_config.offset2 = 0x7F;
	t_wpc_config.offset3 = 0x7F;
	wpc_set_fod(&t_wpc_config);

	wpc_set_plc_length(30); /* PLC Length : 30mSec */
	wpc_initialize_cb_function(eWPC_CB_FUNC_VOUT_ON, wpc_cb_vout_on);
	wpc_initialize_cb_function(eWPC_CB_FUNC_CHG_MODE, wpc_cb_charger_mode);
	wpc_initialize_cb_function(eWPC_CB_FUNC_SEND_PLC, wpc_cb_can_send_plc);

	printf("START S2MUA01 : %s\r\n", BuildTime);
	etemptype = eWPC_TEST_TEMP_NORMAL;
	//eoldtemptype = eWPC_TEST_TEMP_NORMAL;
	wpc_control_temp(eWPC_CTRL_TEMP_SET_NORMAL);
	wpc_tick = sys_get_tick();
	delay_ms = 10;

	while (1)
	{
		if (wpc_get_vrect_status() == TRUE)
		{
			wpc_process(first_flag, delay_ms);
			if (first_flag == 1)
			{
				wpc_temp_tick = sys_get_tick();
				first_flag = 0;
			}
		}
		else
		{
			if (first_flag == 0)
			{
				first_flag = 1;
				wpc_end_process();
			}
		}

		if ((sys_get_tick() - wpc_temp_tick) > 10000)
		{
			switch (etemptype)
			{
			case eWPC_TEST_TEMP_NORMAL:
				wpc_control_temp(eWPC_CTRL_TEMP_SET_HIGH);
				//eoldtemptype = eWPC_TEST_TEMP_NORMAL;
				etemptype = eWPC_TEST_TEMP_HIGH;
				break;
			case eWPC_TEST_TEMP_HIGH:
				#if (1) // Normal -> High -> Normal
				wpc_control_temp(eWPC_CTRL_TEMP_RET_NORMAL);
				//eoldtemptype = eWPC_TEST_TEMP_HIGH;
				etemptype = eWPC_TEST_TEMP_NORMAL;
				#else // Normal -> High -> Very High -> High -> Normal
				if (eoldtemptype == eWPC_TEST_TEMP_NORMAL)
				{
					wpc_control_temp(eWPC_CTRL_TEMP_SET_VERY_HIGH);
					eoldtemptype = eWPC_TEST_TEMP_HIGH;
					etemptype = eWPC_TEST_TEMP_VERY_HIGH;

					SYSREG.WPT_EN.BITS.REG_SEL_EN_WPT_UVLO_MCU=1;
					SYSREG.WPT_EN.BITS.REG_EN_WPT_UVLO_MCU=0;
				}
				else if (eoldtemptype == eWPC_TEST_TEMP_VERY_HIGH)
				{
					wpc_control_temp(eWPC_CTRL_TEMP_RET_NORMAL);
					eoldtemptype = eWPC_TEST_TEMP_HIGH;
					etemptype = eWPC_TEST_TEMP_NORMAL;
				}
				#endif
				break;
			case eWPC_TEST_TEMP_VERY_HIGH:
				SYSREG.WPT_EN.BITS.REG_SEL_EN_WPT_UVLO_MCU=1;
				SYSREG.WPT_EN.BITS.REG_EN_WPT_UVLO_MCU=1;

				wpc_control_temp(eWPC_CTRL_TEMP_RET_HIGH);
				//eoldtemptype = eWPC_TEST_TEMP_VERY_HIGH;
				etemptype = eWPC_TEST_TEMP_HIGH;
				break;
			default:
				break;
			}

			wpc_temp_tick = sys_get_tick();
		}


		if ((sys_get_tick() - wpc_tick) > 100)
			delay_ms = 29;
	}
}

#pragma arm section code


