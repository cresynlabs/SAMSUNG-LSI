/*
******************************************************************************
* @file    FGDrv.c
* @author  Power Device Team
* @version V1.0.0
* @brief   Main System StartUp
******************************************************************************
*/

#include "cm0pikmcu.h"
#include "sc_drv.h"

uint32_t bst_start_time=0;

uint8_t sc_drv_get_chgin_status(void)
{
	return SC.REG_10.BITS.CHGIN_Status;
}

uint8_t sc_drv_get_wcin_status(void)
{
	return SC.REG_10.BITS.WCIN_Status;
}

void sc_drv_set_reg_mode(uint8_t mode)
{
	SC.REG_18.BITS.REG_MODE = mode;
	sysdelay_us(10);

	if (mode == BUCK_MODE || mode == CHG_MODE)
	{
		if (SC.REG_90.BITS.SWITCH_FREQ >= SWITCH_FREQ_1M)
		{
			if (sc_drv_get_fast_charge_current() > 0x02)
				SC.REG_38.BITS.T_GD_ASYNC = 1;
			else
				SC.REG_38.BITS.T_GD_ASYNC = 3;
		}
	}

	switch (mode)
	{
	case BUCK_MODE:
		SC.REG_28.BITS.T_SC_FAULT = 3;
		SC.REG_18.BITS.REG_MODE = CHG_MODE;
		break;
	case CHG_MODE:
		SC.REG_18.BITS.REG_MODE = CHG_MODE;
		SC.REG_28.BITS.T_SC_FAULT = 1;
		break;
	case BST_MODE:
		if (SC.REG_18.BITS.REG_MODE != BST_MODE)
			bst_start_time = sys_get_tick();
		SC.REG_18.BITS.REG_MODE = BST_MODE;
		SC.REG_28.BITS.T_SC_FAULT = 1;

		break;
	default :
		break;
	}
}
uint8_t sc_drv_get_reg_mode(void)
{
	if (SC.REG_18.BITS.REG_MODE == CHG_MODE)
	{
		if (SC.REG_28.BITS.T_SC_FAULT == 3)
			return 1;
		else
			return 3;
	}
	else
		return 2;
}

/* SET_IVR_CHGIN, SET_IVR_WCIN
 * IVR_4P2V       0x00
 * IVR_4P3V       0x01
 * IVR_4P4V       0x02
 * IVR_4P5V       0x03
 * IVR_4P6V       0x04
 * IVR_4P7V       0x05
 * IVR_4P8V       0x06
 * IVR_4P9V       0x07 */

void sc_drv_set_ivr_chgin_ilim(uint8_t data)
{
	SC.REG_1C.BITS.SET_IVR_CHGIN = data;
}

void sc_drv_set_ivr_wcin_ilim(uint8_t data)
{
	SC.REG_1C.BITS.SET_IVR_WCIN = data;
}

/*	Battery regulation voltage setting for buck on, charger off mode or CV state,
 *	000_0000: 3.900V
 *	000_0001: 3.905V
 *	000_0010: 3.910V
 *	--------------------------------------
 *	011_1100: 4.200V (default)
 *	011_1101: 4.205V
 *	---------------------------------------
 *	111_1111: 4.535V */
void sc_drv_set_vf_vbat(uint16_t data)
{
	SC.REG_1C.BITS.SET_VF_VBAT = (uint8_t)data;
}

/*
 * Minimum VSYS voltage regulation setting
 * VSYSMIN_3P0V   0x00
 * VSYSMIN_3P4V   0x01
 * VSYSMIN_3P5V   0x02
 * VSYSMIN_3P6V   0x03
 * VSYSMIN_3P7V   0x04
 * VSYSMIN_3P8V   0x05
 * VSYSMIN_3P9V   0x06
 * VSYSMIN_4P0V   0x07 */
void sc_drv_set_vsysmin(uint8_t data)
{
	SC.REG_20.BITS.SET_VSYSMIN = data;
}

void sc_drv_set_auto_chg_restart(uint8_t data)
{
	SC.REG_20.BITS.Auto_CHG_RESTART = data;
}

/* CC Current setting */
void sc_drv_set_fast_charge_current(uint16_t data)
{
	if (data > 2)
		SC.REG_38.BITS.T_GD_ASYNC = 1;
	else
		SC.REG_38.BITS.T_GD_ASYNC = 3;

	SC.REG_1C.BITS.SET_Fast_Charge_Current = data;
}

uint8_t sc_drv_get_fast_charge_current(void)
{
	return SC.REG_1C.BITS.SET_Fast_Charge_Current;
}

void sc_drv_set_fast_charge_current_step(uint8_t data)
{
	static uint32_t current_step_tick = 0;

	#ifdef WPT_SWITCHING_FREQ_2MHz
	if(SC.REG_90.BITS.SWITCH_FREQ != SWITCH_FREQ_2M)
		return;
	#else
	if(SC.REG_90.BITS.SWITCH_FREQ != SWITCH_FREQ_1M)
		return;
	#endif

	if(SC.REG_1C.BITS.SET_Fast_Charge_Current < data)
	{
		if (sys_get_tick() - current_step_tick > 100)
		{
			SC.REG_1C.BITS.SET_Fast_Charge_Current++;
			current_step_tick = sys_get_tick();
		}
	}
	else
	{
		SC.REG_1C.BITS.SET_Fast_Charge_Current = data;
	}
}

/* TOPOFF_5MA            0x03
 * TOPOFF_10MA           0x07
 * TOPOFF_15MA           0x0B
 * TOPOFF_20MA           0x0F
 * TOPOFF_25MA           0x13 */
void sc_drv_set_1st_topoff(uint8_t data)
{
	SC.REG_24.BITS.Set_1st_TOP_OFF = data;
}

void sc_drv_set_2nd_topoff(uint8_t data)
{
	SC.REG_28.BITS.SET_2nd_TOP_OFF = data;
}

uint8_t sc_drv_get_charge_done(void)
{
	return SC.REG_10.BITS.DONE_Status;
}

/*
 * Charger off automatically by 2nd TOP OFF
 * This register is in the OTP area. */
void sc_drv_set_charger_off_by_2nd_topoff(uint8_t data)
{
	volatile uint8_t *direct_addr;
	direct_addr  = (volatile uint8_t *)0xF000809B;
	*direct_addr = (*direct_addr) | data;
}

void sc_drv_set_en_timer_fault(uint8_t data)
{
	SC.REG_34.BITS.EN_Timer_Fault = data;
}

void sc_drv_set_uvlo_debounce_time(void)
{
	volatile uint8_t *direct_addr;
	direct_addr  = (volatile uint8_t *)0xF00080CA;
	*direct_addr = (*direct_addr) & 0xCF | 0x20;
}

void sc_drv_set_bst_voltage(uint8_t data)
{
	SC.REG_20.BITS.SET_BST = data;
}

void sc_drv_set_switch_freq(switch_freq_t freq)
{
	SC.REG_90.BITS.SWITCH_FREQ = (uint8_t)freq;
}

uint8_t sc_drv_get_switch_freq(void)
{
	return SC.REG_90.BITS.SWITCH_FREQ;
}

void sc_drv_set_ovp_debounce_time(uint8_t data)
{
	volatile uint8_t *direct_addr;
	direct_addr  = (volatile uint8_t *)0xF00080CA;
	*direct_addr = (*direct_addr) & 0x3F | (data << 6);
}

uint32_t sc_drv_get_bst_start_time(void)
{
	return bst_start_time;
}
