#ifndef _PERI_SC_
#define _PERI_SC_

typedef union
{
    uint32_t DATA;
    struct {
        uint32_t   Reserved:32;
  } BITS;
}SCReserved_Type;

typedef union
{
	  uint32_t DATA;
	  struct {
		  uint32_t SYS_INT:1,
		  	       CV_INT:1,
		  	       CHG_Fault_INT:1,
		  	       CHG_Restart_INT:1,
		  	       DONE_INT:1,
		  	       TOP_OFF_INT:1,
		  	       WCIN_INT:1,
		  	       CHGIN_INT:1,
		  	       ICR_INT:1,
		  	       IVR_INT:1,
		  	       AICL_INT:1,
		  	       VBUS_Short_INT:1,
		  	       BST_INT:1,
		  	       OTG_INT:1,
		  	       BAT_INT:1,
		  	       DET_VBUS_INT:1,
		  	       BATID_INT:1,
		  	       BATID_DONE_INT:1,
		  	       QBAT_OFF_INT:1,
		  	       Reserved1:1,
		  	       BATN_OPEN_INT:1,
		  	       BATP_OPEN_INT:1,
		  	       BAT_CONTACT_CK_DONE_INT:1,
		  	       Reserved2:9;

	} BITS;
}SC_REG_00;

typedef union
{
	  uint32_t DATA;
	  struct {
		  uint32_t SYS_INT_MASK:1,
		  	       CV_INT_MASK:1,
		  	       CHG_Fault_INT_MASK:1,
		  	       CHG_Restart_INT_MASK:1,
		  	       DONE_INT_MASK:1,
		  	       TOP_OFF_INT_MASK:1,
		  	       CHGIN_INT_MASK:1,
		  	       Reserved1:1,
		  	       ICR_INT_MASK:1,
		  	       IVR_INT_MASK:1,
		  	       AICL_INT_MASK:1,
		  	       VBUS_Short_INT_MASK:1,
		  	       BST_INT_MASK:1,
		  	       OTG_INT_MASK:1,
		  	       BAT_INT_MASK:1,
		  	       DET_VBUS_INT_MASK:1,
		  	       BATID_INT_MASK:1,
		  	       BATID_DONE_INT_MASK:1,
		  	       QBAT_OFF_MASK:1,
		  	       Reserved2:1,
		  	       BATN_OPEN_MASK:1,
		  	       BATP_OPEN_MASK:1,
		  	       BAT_CONTACK_OK_DONE_MASK:1,
		  	       Reserved3:9;
	} BITS;
}SC_REG_08;

typedef union
{
	  uint32_t DATA;
	  struct {
		  uint32_t WCIN_Status:3,
		  	       Reserved:1,
		  	       CHGIN_Status:3,
		  	       MAX_Duty_Status:1,
		  	       DONE_Status:1,
		  	       TOP_OFF_Status:1,
		  	       CHG_Restart_Status:1,
		  	       CV_Status:1,
		  	       CHG_Fault_Status:4,
		  	       Input_ICR_Code_Status:7,
		  	       AUTO_ICR_SEARCH_CHGIN:1,
		  	       ICR_Status:1,
		  	       IVR_Status:1,
		  	       AICL_Status:2,
		  	       VBUS_Short_Status:1,
		  	       DET_VBUS_DB:1,
		  	       Reserved2:2;
	} BITS;
}SC_REG_10;

typedef union
{
	  uint32_t DATA;
	  struct {
		  uint32_t SYS_Status:2,
		  	       BST_Status:2,
		  	       TX_Status:2,
		  	       OTG_Status:2,
		  	       BAT_Status:3,
		  	       QBAT_OFF:1,
		  	       BATID_Status:2,
		  	       BATN_OPEN_STATUS:1,
		  	       BATP_OPEN_STATUS:1,
		  	       Reserved:16;
	} BITS;
}SC_REG_14;

typedef union
{
	  uint32_t DATA;
	  struct {
		  uint32_t REG_MODE:4,
		  	       JIG_ON_AP:1,
		  	       EN_JIG_BYPASS_MODE:1,
		  	       AUTO_DC_SC_CHG_MODE:1,
		  	       EOC_After_BAT_MODE:1,
		  	       SET_IN_CHGIN_ILIM:6,
		  	       Reserved1:2,
		  	       SET_IN_WCIN_ILIM:6,
		  	       Reserved2:2,
		  	       SET_TX_OCP:2,
		  	       SET_OTG_OCP:2,
		  	       OTG_TX_OCP_SW_OFF:1,
		  	       OTG_TX_OCP_SW_ON:1,
		  	       SEL_Prio_WCIN:1,
		  	       EN_ICR_AT_SCH:1;
	} BITS;
}SC_REG_18;

typedef union
{
	  uint32_t DATA;
	  struct {
		  uint32_t SET_IVR_WCIN:3,
		  	       SET_IVR_CHGIN:3,
		  	       AP_VBUS_Short_CK:1,
		  	       VBUS_Short_CK_Auto:1,
		  	       SET_VF_VBAT:7,
		  	       EN_BAT_CONTACT:1,
		  	       SET_COOL_Charge_Current:6,
		  	       Reserved1:1,
		  	       EN_COOL_CHG:1,
		  	       SET_Fast_Charge_Current:6,
		  	       Reserved2:2;
	} BITS;
}SC_REG_1C;

typedef union
{
	  uint32_t DATA;
	  struct {
		  uint32_t SET_VF_VSYS:4,
		  	       SET_VSYSMIN:3,
		  	       EN_JIG_Reg_AP:1,
		  	       SET_BAT_OCP:5,
		  	       EN_BAT_OCP:1,
		  	       Reserved1:1,
		  	       BAT_OCP_QBAT_OFF:1,
		  	       EN_BAT_ID_CK:1,
		  	       Reserved2:3,
		  	       SET_VBAT_RESTART:2,
		  	       Auto_CHG_RESTART:1,
		  	       CHG_OFF_at_CELL_LBAT:1,
		  	       SET_BST:7,
		  	       Reserved3:1;
	} BITS;
}SC_REG_20;

typedef union
{
	  uint32_t DATA;
	  struct {
		  uint32_t WDT_CLR:1,
		  	       Time_SET_WDT_Time:3,
		  	       EN_WDT:1,
		  	       EN_WDT_AP_RESET:1,
		  	       Reserved2:2,
		  	       Time_TRICLE_CHG:3,
		  	       Time_FC_CHG:3,
		  	       Reserved3:1,
		  	       EN_Deat_BAT_Timer:1,
		  	       Time_TOP_OFF:3,
		  	       SET_TFB:3,
		  	       SET_TSD:2,
		  	       Set_1st_TOP_OFF:5,
		  	       Reserved4:3;
	} BITS;
}SC_REG_24;

typedef union
{
	  uint32_t DATA;
	  struct {
		  uint32_t SET_2nd_TOP_OFF:5,
		  	       Reserved1:3,
		  	       T_EN_WCIN_Discharge:2,
		  	       T_EN_CHGIN_Discharge:2,
		  	       T_EN_VBAT_Discharge:2,
		  	       T_EN_VSYS_Discharge:2,
		  	       T_EN_WCIN:2,
		  	       T_EN_CHGIN:2,
		  	       T_SC_FAULT:2,
		  	       T_LC_FAULT:2,
		  	       Reserved2:8;
	} BITS;
}SC_REG_28;

typedef union
{
	  uint32_t DATA;
	  struct {
		  uint32_t Reserved1:8,
		  	       TMODE:3,
		  	       GTST:1,
		  	       EN_OCL_TEST_MODE:1,
		  	       R_EN_TEST_DC_ICR:1,
		  	       TEST_LS_NMOS_ON:1,
		  	       TEST_HS_NMOS_ON:1,
		  	       EN_TSD:1,
		  	       EN_TFB:1,
		  	       EN_ATE_TFB:1,
		  	       Reserved2:5,
		  	       SET_ANA_TEST_MUX:4,
		  	       Reserved3:1,
		  	       EN_ASYNC_DET_TEST:1,
		  	       Reserved4:2;
	} BITS;
}SC_REG_30;

typedef union
{
	  uint32_t DATA;
	  struct {
		  uint32_t T_EN_CVR:2,
		  	       T_EN_CCR:2,
		  	       T_EN_ICR:2,
		  	       T_EN_IVR:2,
		  	       T_DET_DONE:1,
		  	       EN_DONE:1,
		  	       T_DET_TOP_OFF:1,
		  	       T_EN_TOP_OFF:1,
		  	       EN_BAT_TO_SYS:1,
		  	       EN_Timer_Fault:1,
		  	       Reserved1:1,
		  	       T_QUAL_VSYS:1,
		  	       T_SC_MODE:2,
		  	       T_LC_MODE:2,
		  	       T_EN_BST:2,
		  	       T_EN_BUCK:2,
		  	       T_DET_VSYS_MIN:2,
		  	       T_EN_LC:2,
		  	       T_SEL_VF:2,
		  	       T_SEL_VSYS:2;
	} BITS;
}SC_REG_34;

typedef union
{
	  uint32_t DATA;
	  struct {
		  uint32_t T_EN_SS_VSYS:2,
		  	       T_EN_CS_BAT:2,
		  	       T_STATE:3,
		  	       Reserved1:1,
		  	       T_DET_WCIN_TO_BAT:2,
		  	       T_DET_CHGIN_TO_BAT:2,
		  	       T_DET_WCIN_UVLOB:2,
		  	       T_DET_CHGIN_UVLOB:2,
		  	       T_GD_ASYNC:2,
		  	       Reserved2:2,
		  	       T_EN_VSYS_UVLOB:2,
		  	       T_EN_NMOS_ZCS_ON:2,
		  	       EN_CS_WCIN:2,
		  	       EN_CS_CHGIN:2,
		  	       T_WCIN_OK:2,
		  	       T_CHGIN_OK:2;
	} BITS;
}SC_REG_38;

typedef union
{
	  uint32_t DATA;
	  struct {
		  uint32_t EN_PSK:2,
		  	       Reserved1:2,
		  	       T_EN_CORE:2,
		  	       T_EN_CLK:2,
		  	       Reserved2:6,
		  	       RX_OTG_CP_MODE:1,
		  	       EN_INPUT_OCP:1,
		  	       Reserved3:2,
		  	       T_AMS_DB:1,
		  	       EN_IN_at_LC:1,
		  	       T_ENVSSH:2,
		  	       Reserved4:1,
		  	       SC_MONITOR_BIT:1,
		  	       EN_CHG:1,
		  	       OTP_RE_DUMP:1,
		  	       SC_RESET:1,
		  	       EN_CHG_RESTART:1,
		  	       T_EN_VDDA2BAT:2,
		  	       T_FLED_BST_ON:2;
	} BITS;
}SC_REG_3C;

typedef union
{
	  uint32_t DATA;
	  struct {
		  uint32_t SC_MONITOR_SEL:8,
		  	       Reserved:24;
	} BITS;
}SC_REG_40;

typedef union
{
	  uint32_t DATA;
	  struct {
		  uint32_t Reserved1:8,
		           Trim_WCIN_OVP:6,
		  	       Reserved2:2,
		  	       Reserved3:16;
	} BITS;
}SC_REG_6C;

typedef union
{
	  uint32_t DATA;
	  struct {
		  uint32_t Reserved1:16,
		           SET_WCIN_UVLOB_F:2,
		           SET_WCIN_UVLOB_R:2,
		  	       Reserved2:4,
		  	       Reserved3:7,
		  	       EN_AZ:1;
	} BITS;
}SC_REG_70;

typedef union
{
	  uint32_t DATA;
	  struct {
		  uint32_t Reserved1:16,
		           MIN_DIF_INC:3,
		  	       Reserved2:5,
		  	       Reserved3:8;
	} BITS;
}SC_REG_7C;

typedef union
{
	  uint32_t DATA;
	  struct {
		  uint32_t SET_LCELL_R:3,
		           Reserved1:5,
		  	       Reserved2:24;
	} BITS;
}SC_REG_84;

typedef union
{
	  uint32_t DATA;
	  struct {
		  uint32_t Reserved1:24,
		  	       Reserved2:4,
		  	       OVP_SW_WAIT_TIME:3,
		  	       Reserved3:1;
	} BITS;
}SC_REG_8C;

typedef union
{
	  uint32_t DATA;
	  struct {
		  uint32_t Reserved1:24,
		  	       Reserved2:4,
		  	       SWITCH_FREQ:2,
		  	       Reserved3:2;
	} BITS;
}SC_REG_90;

typedef union
{
	  uint32_t DATA;
	  struct {
		  uint32_t Reserved1:6,
		           Time_SET_IBAT_SS:2,
		  	       Reserved2:24;
	} BITS;
}SC_REG_94;

typedef union
{
	  uint32_t DATA;
	  struct {
		  uint32_t Reserved0:8,
		  	       Reserved1:8,
		  	       CC_Trim:8,
		  	       Reserved2:8;		  	
	} BITS;
}SC_REG_B8;


typedef union
{
	  uint32_t DATA;
	  struct {
		  uint32_t Reserved1:16,
		  	       Reserved2:4,
		  	       WCIN_UVLOB_TIME:2,
		  	       Reserved3:2,
		  	       Reserved4:8;
	} BITS;
}SC_REG_C8;

typedef struct
{
	SC_REG_00       REG_00;
	SCReserved_Type REG_04;
	SC_REG_08       REG_08;
	SCReserved_Type REG_0C;
	SC_REG_10       REG_10;
	SC_REG_14       REG_14;
	SC_REG_18       REG_18;
	SC_REG_1C       REG_1C;
	SC_REG_20       REG_20;
	SC_REG_24       REG_24;
	SC_REG_28       REG_28;
	SCReserved_Type REG_2C;
	SC_REG_30       REG_30;
	SC_REG_34       REG_34;
	SC_REG_38       REG_38;
	SC_REG_3C       REG_3C;
	SC_REG_40       REG_40;
	SCReserved_Type REG_44;
	SCReserved_Type REG_48;
	SCReserved_Type REG_4C;
	SCReserved_Type REG_50;
	SCReserved_Type REG_54;
	SCReserved_Type REG_58;
	SCReserved_Type REG_5C;
	SCReserved_Type REG_60;
	SCReserved_Type REG_64;
	SCReserved_Type REG_68;
	SC_REG_6C       REG_6C;
	SC_REG_70       REG_70;
	SCReserved_Type REG_74;
	SCReserved_Type REG_78;
	SC_REG_7C       REG_7C;
	SCReserved_Type REG_80;
	SC_REG_84       REG_84;
	SCReserved_Type REG_88;
	SC_REG_8C       REG_8C;
	SC_REG_90       REG_90;
	SC_REG_94       REG_94;
	SCReserved_Type REG_98;
	SCReserved_Type REG_9C;
	SCReserved_Type REG_A0;
	SCReserved_Type REG_A4;
	SCReserved_Type REG_A8;
	SCReserved_Type REG_AC;
	SCReserved_Type REG_B0;
	SCReserved_Type REG_B4;
	SC_REG_B8       REG_B8;
	SCReserved_Type REG_BC;
	SCReserved_Type REG_C0;
	SCReserved_Type REG_C4;
	SC_REG_C8       REG_C8;
	SCReserved_Type REG_CC;
}SC_BLOCK_Type;
















#endif
