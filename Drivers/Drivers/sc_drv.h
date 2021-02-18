#ifndef __SC_DRV_H
#define __SC_DRV_H

//usb전원 인가 인식 하는 값 : ok  인식 못하는 값 : off 
#define CHGIN_UNDER_UVLO                   0  //off
#define CHGIN_VOLTAGE_LOW                  1  //off
#define CHGIN_OVER_OVLO                    2  //ok
#define CHGIN_IN_CURRENT_IS_LIMITED_REGUL  3  //ok
#define CHGIN_IN_SWITCH_IS_OFF             4  //off
#define CHGIN_IS_VALID                     5  //ok

//무선충전 전원 인가 인식 하는 값 : ok  인식 못하는 값 : off 
#define WCIN_UNDER_UVLO                    0  //off
#define WCIN_VOLTAGE_LOW                   1  //off
#define WCIN_OVER_OVLO                     2  //on
#define WCIN_IN_CURRENT_IS_LIMITED_REGUL   3  //ok
#define WCIN_IN_SWITCH_IS_OFF              4  //off
#define WCIN_IS_VALID                      5  //ok

// Charger faultt status details
#define CHG_FAULT_NORMAL                 0x00
#define CHG_FAULT_WATCHDOG_SUS           0x01
#define CHG_FALUT_WATCHDOG_AP_RST        0x02
#define CHG_FALUT_THERMAL_SUHTDOWN       0x03
#define CHG_FALUT_THERMAL_FOLDBACK       0x04
#define CHG_FALUT_THERMAL_TMR_PRE_CHR    0x05
#define CHG_FALUT_THERMAL_TMR_TRI_CHR    0x06
#define CHG_FALUT_THERMAL_TMR_FAS_CHR    0x07
#define CHG_FALUT_THERMAL_TMR_TOP_OFF    0x08
#define CHG_FALUT_LOW_FLY_CAP_VOLT       0x09
#define CHG_FALUT_HIGH_FLY_CAP_VOLT      0x0A

// VBUS_Short_Status
#define VBUS_NO_SHORT        0
#define VBUS_SHORT           1

// SYS status
#define VSYS_OVER_VSYSOROVP   0
#define VSYS_UNDER_VSYSORUVLO 1
#define VSYS_IS_OKAY          3

// Switching charger operating mode setting
#define CHARGER_OFF_MODE1       0x00
#define BUCK_MODE               0x01
#define BST_MODE                0x02
#define CHG_MODE                0x03
#define CHARGER_OFF_MODE2       0x04
#define OTG_WCIN_BUCK_MODE      0x05
#define OTG_BST_MODE            0x06
#define OTG_WCIN_CHG_MODE       0x07
#define CHARGER_OFF_MODE3       0x08
#define TX_CHGIN_BUCK_MODE      0x09
#define TX_BST_MODE             0x0A
#define TX_CHGIN_CHG_MODE       0x0B
#define CHARGER_OFF_MODE4       0x0C
#define CHARGER_OFF_MODE5       0x0D
#define OTG_TX_BST_MODE         0x0E
#define CHARGER_OFF_MODE6       0x0F

// SET_IVR_CHGIN, SET_IVR_WCIN
#define IVR_4P2V       0x00
#define IVR_4P3V       0x01
#define IVR_4P4V       0x02
#define IVR_4P5V       0x03
#define IVR_4P6V       0x04
#define IVR_4P7V       0x05
#define IVR_4P8V       0x06
#define IVR_4P9V       0x07


//Minimum VSYS voltage regulation setting
#define VSYSMIN_3P0V   0x00
#define VSYSMIN_3P4V   0x01
#define VSYSMIN_3P5V   0x02
#define VSYSMIN_3P6V   0x03
#define VSYSMIN_3P7V   0x04
#define VSYSMIN_3P8V   0x05
#define VSYSMIN_3P9V   0x06
#define VSYSMIN_4P0V   0x07

//VF VSYS
#define VF_VSYS_3P6    0x00
#define VF_VSYS_3P7    0x01
#define VF_VSYS_3P8    0x02
#define VF_VSYS_3P9    0x03
#define VF_VSYS_4P0    0x04
#define VF_VSYS_4P1    0x05
#define VF_VSYS_4P2    0x06
#define VF_VSYS_4P3    0x07
#define VF_VSYS_4P4    0x08
#define VF_VSYS_4P5    0x09
#define VF_VSYS_4P6    0x0A
#define VF_VSYS_4P7    0x0C

//input current limit
#define ILIM_100MA            0x02
#define ILIM_125MA            0x03
#define ILIM_150MA            0x04
#define ILIM_175MA            0x05
#define ILIM_200MA            0x06
#define ILIM_225MA            0x07
#define ILIM_250MA            0x08
#define ILIM_275MA            0x09
#define ILIM_300MA            0x0A
#define ILIM_325MA            0x0B
#define ILIM_350MA            0x0C
#define ILIM_375MA            0x0D
#define ILIM_400MA            0x0E
#define ILIM_425MA            0x0F
#define ILIM_450MA            0x10
#define ILIM_475MA            0x11
#define ILIM_500MA            0x12

//top off current
#define TOPOFF_5MA            0x03
#define TOPOFF_10MA           0x07
#define TOPOFF_15MA           0x0B
#define TOPOFF_20MA           0x0F
#define TOPOFF_25MA           0x13
#define TOPOFF_30MA           0x17
#define TOPOFF_40MA           0x1F


#define VBUS_TIMER_LOW2   67800000 //1130min
#define VBUS_TIMER_LOW1   36000000 //600min
#define VBUS_TIMER_NOR    10800000 //180min
#define VBUS_TIMER_HIGH   18000000 //300min

#define WPT_TIMER_LOW2    67800000 //1130min
#define WPT_TIMER_LOW1    36000000 //600min
#define WPT_TIMER_NOR     21600000 //360min
#define WPT_TIMER_NOR_EAR 36000000 //600min



typedef enum
{
	SWITCH_FREQ_500K,
	SWITCH_FREQ_750K,
	SWITCH_FREQ_1M,
	SWITCH_FREQ_2M,
} switch_freq_t;


typedef enum {
	CHGIN_INT,
	WCIN_INT,
	TOP_OFF_INT,
	DONE_INT,
	CHG_Restart_INT,
	CHG_Fault_INT,
	CV_INT,
	SYS_INT,
	DET_VBUS_INT,
	BAT_INT,
	OTG_INT,
	BST_INT,
	VBUS_Short_INT,
	AICL_INT,
	IVR_INT,
	ICR_INT,
	BAT_CONTACT_CK_DONE_INT,
	BATP_OPEN_INT,
	BATN_OPEN_INT,
	QBAT_OFF_INT,
	BATID_DONE_INT,
	BATID_INT
} sc_int_t;

#ifdef WPT_AUTO_ZERO_WA
typedef enum
{
	CC_TRIM_UP,
	CC_TRIM_DN,
	CC_TRIM_BACK
} cc_trim_t;

typedef struct
{
	uint8_t uc_origin;
	uint8_t uc_set_flag;
} cc_trim_Info_t;
#endif


uint8_t sc_drv_get_fast_charge_current(void);
uint8_t sc_drv_get_chgin_status(void);
uint8_t sc_drv_get_wcin_status(void);
void sc_drv_set_reg_mode(uint8_t mode);
uint8_t sc_drv_get_reg_mode(void);
void sc_drv_set_ivr_chgin_ilim(uint8_t data);
void sc_drv_set_ivr_wcin_ilim(uint8_t data);
void sc_drv_set_vf_vbat(uint16_t data);
void sc_drv_set_vsysmin(uint8_t data);
void sc_drv_set_auto_chg_restart(uint8_t data);
void sc_drv_set_1st_topoff(uint8_t data);
void sc_drv_set_2nd_topoff(uint8_t data);
uint8_t sc_drv_get_charge_done(void);
void sc_drv_set_charger_off_by_2nd_topoff(uint8_t data);
void sc_drv_set_fast_charge_current(uint16_t data);
void sc_drv_set_fast_charge_current_step(uint8_t data);
void sc_drv_set_en_timer_fault(uint8_t data);
void sc_drv_set_uvlo_debounce_time(void);
void sc_drv_set_bst_voltage(uint8_t data);

void sc_drv_set_switch_freq(switch_freq_t freq);
uint8_t sc_drv_get_switch_freq(void);
uint8_t sc_drv_getfast_charge_current(void);
void sc_drv_set_ovp_debounce_time(uint8_t data);
uint32_t sc_drv_get_bst_start_time(void);
#endif /* __SC_DRV_H */
