#ifndef _PERI_FG_H_
#define _PERI_FG_H_

typedef union
{
    uint32_t DATA;
    struct {
        uint32_t   Reserved:32;
  } BITS;
}FGReserved_Type;

typedef union
{
    uint32_t DATA;
    struct {
        uint32_t SOC_L:1,
			     VBAT_L:1,
			     TEMP_H:1,
			     TEMP_L:1,
			     Reserved1:1,
			     Chg_Stat:1,
			     VM:1,
			     Reserved2:1,                    // 7
			     PEADEN:1,
			     DUMP_DONE_ST:1,
			     Reserved3:2,
			     VM1_FLAG:1,
			     VM2_FLAG:1,
			     VM3_FLAG:1,
			     Reserved4:1,                    // 15
			     SOC_L_I:1,
			     VBAT_L_I:1,
			     TEMP_H_I:1,
			     TEMP_L_I:1,
			     Reserved5:4,                    // 23
			     SOC_L_IM:1,
			     VBAT_L_IM:1,
			     TEMP_H_IM:1,
			     TEMP_L_IM:1,
			     IF_EN:2,
			     SOC_UPDATE_SEL:1,
			     Reserved6:1;			         // 31
  } BITS;
}FG_REG_00;

typedef union
{
    uint32_t DATA;
    struct {
        uint32_t VBat:16,
			     CUR_CC:16;
  } BITS;
}FG_REG_04;

typedef union
{
    uint32_t DATA;
    struct {
        uint32_t SOC_CC:16,
			     MONOUT:16;
  } BITS;
}FG_REG_08;

typedef union
{
	  uint32_t DATA;
	  struct {
		  uint32_t MONOUT_SEL:6,
		  	       BATCAP_OCV_EN:1,
		  	       Reserved1:5,
		  	       ADC_AVCC_EN:2,
		  	       Reserved2:2,
		  	       BATCAP_OCV:16;
	} BITS;
}FG_REG_0C;

typedef union
{
	  uint32_t DATA;
	  struct {
		  uint32_t BATCAP:14,
		  	       Reserved1:2,
		  	       ZADJ_CHG:8,
		  	       ZADJ_CHG2:8;
	} BITS;

}FG_REG_10;

typedef union
{
	  uint32_t DATA;
	  struct {
		  uint32_t EDV:8,
		  	       ZADJ:8,
		  	       Z0:8,
		  	       Z1:8;
	} BITS;
}FG_REG_14;

typedef union
{
	  uint32_t DATA;
	  struct {
		  uint32_t Z2:8,
		  	       Z3:8,
		  	       VBAT_L_LVL:4,
		  	       SOC_L_LVL:4,
		  	       MONSEL:7,
		  	       MON_EN:1;
	} BITS;
}FG_REG_18;

typedef union
{
	  uint32_t DATA;
	  struct {
		  uint32_t TEMP_H_LVL:7,
		  	       ZERO:1,
		  	       TEMP_L_LVL:8,
		  	       DUMP_DONE:2,
		  	       RESTART:2,
		  	       Reserved:4,
		  	       FG_RST:1,
		  	       T_START:1,
		  	       SD_TEST_EN:1,
		  	       SD_TEST_ON:1,
		  	       JIGB:1,
		  	       IRQ_DEAULT_LOW:1,
		  	       OTP_REDUMP:1,
		  	       SIM_MODE:1;
	} BITS;
}FG_REG_1C;

typedef union
{
	  uint32_t DATA;
	  struct {
		  uint32_t CAD_REG_00:8,
		  	       CAD_REG_01:8,
		  	       CAD_REG_04:4,
		  	       CAD_REG_02:4,
		  	       CAD_REG_03:8;
	} BITS;
}FG_REG_20;

typedef union
{
	  uint32_t DATA;
	  struct {
		  uint32_t VBAT_FORCE_EN:1,
		  	       VBAT_I2C:11,
		  	       JIG_ON_I2C_EN:1,
		  	       JIG_ON_I2C:1,
		  	       CHG_ON_I2C_EN:1,
		  	       CHG_ON_I2C:1,
		  	       CUR_CC_FORCE_EN:1,
		  	       CUR_CC_I2C:11,
		  	       Reserved:3,
		  	       VT_EN_MODE:1;
	} BITS;
}FG_REG_24;

typedef union
{
	  uint32_t DATA;
	  struct {
		  uint32_t VTEMP_FORCE_EN:1,
		  	       VTEMPI2C:7,
//		  	       SOC_FORCE_EN:1,			// SOC_FORCE_EN is also soc value(lowest bit of soc). but it is always '1'
		  	       SOC_I2C:8,
		  	       SC_R:16;
	} BITS;
}FG_REG_28;

typedef union
{
	  uint32_t DATA;
	  struct {
		  uint32_t OCV_VM:16,
		  	       Reserved:16;
	} BITS;
}FG_REG_2C;

typedef union
{
	  uint32_t DATA;
	  struct {
		  uint32_t Reserved1:16,
		  	       CAP_CC:16;
	} BITS;
}FG_REG_3C;

typedef union
{
	  uint32_t DATA;
	  struct {
		  uint32_t AvgV0:8,
		  	       AvgC0:8,
		  	       LLC0:8,
		  	       FG_OTP_FLAG1_SEL_L:6,
		  	       RS_SEL:1,
		  	       RS_CC0_SEL:1;
	} BITS;
}FG_REG_40;

typedef union
{
	  uint32_t DATA;
	  struct {
		  uint32_t TRM_CLK:12,
		  	       SD_DUTY_SEL:2,
		  	       Tperiod:2,
		  	       C1_num:2,
		  	       C2_num:2,
		  	       C1_CURR:4,
		  	       TSAMPLE:3,
		  	       Reserved1:1,
		  	       Tdelay:3,
		  	       MRSTB_DISABLE:1;
	} BITS;
}FG_REG_44;

typedef union
{
	  uint32_t DATA;
	  struct {
		  uint32_t Reserved1:4,
		  	       FG_ID:4,
		  	       FG_OTP_FLAG1_SEL_H:6,
		  	       Reserved2:1,
		  	       Short_T_EN:1,
		  	       ITH1:8,
		  	       CC_EN:1,
		  	       MX_EN:1,
		  	       Reserved3:2,
		  	       ITH2:3,
		  	       Reserved4:1;
	} BITS;
}FG_REG_48;

typedef union
{
	  uint32_t DATA;
	  struct {
		  uint32_t FG_OTP_FLAG2_SEL_L:6,
		  	       FG_OTP_FLAG2_SEL_H:6,
		  	       FG_OTP_FLAG3_SEL_L:6,
		  	       FG_OTP_FLAG3_SEL_H:6,
		  	       DCAP_LVL:4,
		  	       SOC_SEL:2,
		  	       Reserved:2;
	} BITS;
}FG_REG_4C;


typedef union
{
	  uint32_t DATA;
	  struct {
		  uint32_t Vslop1:16,
		  	       Voffset:12,
		  	       Vslop2:4;
	} BITS;
}FG_REG_50;

typedef union
{
	  uint32_t DATA;
	  struct {
		  uint32_t Tslop1:16,
		  	       Toffset:12,
		  	       Tslop2:4;
	} BITS;
}FG_REG_54;

typedef union
{
	  uint32_t DATA;
	  struct {
		  uint32_t Cslop1:16,
		  	       Coffset:12,
		  	       Cslop2:4;
	} BITS;
}FG_REG_58;

typedef union
{
	  uint32_t DATA;
	  struct {
		  uint32_t RS_CC0:8,
		  	       RS_CC1:8,
		  	       Temp_A0:16;
	} BITS;
}FG_REG_5C;


typedef union
{
	  uint32_t DATA;
	  struct {
		  uint32_t Temp_B0:16,
		  	       Temp_C0:16;
	} BITS;
}FG_REG_60;

typedef union
{
	  uint32_t DATA;
	  struct {
		  uint32_t Temp_D0:16,
		  	       Coffset_AC:8,
		  	       VM1_flag_EN:1,
		  	       VM2_flag_EN:1,
		  	       VM3_flag_EN:1,
		  	       VM_FORCE:1,
		  	       VM_FORCE_EN:1,
		  	       Fast_lm_EN:1,
		  	       EOD_EN:1,
		  	       INC_OK_EN:1;
	} BITS;
}FG_REG_64;

typedef union
{
	  uint32_t DATA;
	  struct {
		  uint32_t LVBAT_TH0:8,
		  	       LVBAT_TH1:8,
		  	       LVBAT_TH2:8,
		  	       Load_TH:4,
		  	       No4learn:4;
	} BITS;
}FG_REG_68;

typedef union
{
	  uint32_t DATA;
	  struct {
		  uint32_t TRIM_Rsns:12,
		  	       Reserved1:1,
		  	       LOW_EN:1,
		  	       Wide_lm_EN:1,
		  	       Aut_lm_EN:1,
		  	       Compl:8,
		  	       ZeroPTC_LVL:2,
		  	       ZeroPTC_EN:1,
		  	       Resered2:5;
	} BITS;
}FG_REG_6C;

typedef union
{
	  uint32_t DATA;
	  struct {
		  uint32_t Beta0:8,
		  	       Alpha0:8,
		  	       Beta1:8,
		  	       Alpha1:8;
	} BITS;
}FG_REG_70;

typedef union
{
	  uint32_t DATA;
}FG_REG_74;

typedef union
{
	  uint32_t DATA;
	  struct {
		  uint32_t Reserved1:16,
		  	       AvgC4C:8,
		  	       Reserved2:8;
	} BITS;
}FG_REG_78;

typedef union
{
	  uint32_t DATA;
	  struct {
		  uint32_t TCNT_Target:12,
		  	       TCNT_EN:1,
		  	       Reserved1:3,
		  	       TCNT:12,
		  	       Reserved2:4;
	} BITS;
}FG_REG_7C;

typedef union
{
	  uint32_t DATA;
	  struct {
		  uint32_t SOC_R:16,
		  	       SOC:16;
	} BITS;
}FG_REG_80;

typedef union
{
	  uint32_t DATA;
	  struct {
		  uint32_t SOH:16,
		  	       Design_CAP:16;
	} BITS;
}FG_REG_84;

typedef union
{
	  uint32_t DATA;
	  struct {
		  uint32_t BATCAP_OCV_new:16,
		  	       RM:16;
	} BITS;
}FG_REG_88;

typedef union
{
	  uint32_t DATA;
	  struct {
		  uint32_t FCC:16,
		  	       SOCR_I2C:16;
	} BITS;
}FG_REG_8C;




typedef union
{
	  uint32_t DATA;
	  struct {
		  uint32_t Wrtie_EN:1,
		  	       BATCAP_OCV_new_IN:15,
                   rOCV12_LUT0_0:8,
                   rOCV12_LUT0_1:8;
	} BITS;
} FG_REG_90;

typedef union
	{
		  uint32_t DATA;
} FG_REG_BAT_DATA;


typedef struct
{
	FG_REG_00 STATUS;
	FG_REG_04 VBAT;
	FG_REG_08 SOC_CC;
	FG_REG_0C MONOUT_SEL;
	FG_REG_10 BATCAP;
	FG_REG_14 EDV;
	FG_REG_18 Z2;
	FG_REG_1C TEMP_LVL;
	FG_REG_20 CAD_REG;
	FG_REG_24 VBAT_I2C;
	FG_REG_28 VTEMP_I2C;
	FG_REG_2C OVV_VM;
	FGReserved_Type REG_30;
	FGReserved_Type REG_34;
	FGReserved_Type REG_38;
	FG_REG_3C CAP_CC;
	FG_REG_40 AvgV;
	FG_REG_44 TRM_CLK;
	FG_REG_48 FG_ID;
	FG_REG_4C Pseudo_Sens;
	FG_REG_50 Vslope;
	FG_REG_54 Tslope;
	FG_REG_58 Cslope;
	FG_REG_5C RS_CC0;
	FG_REG_60 Temp_B0;
	FG_REG_64 Temp_D0;
	FG_REG_68 LVBAT_TH0;
	FG_REG_6C TRIM_Rsns;
	FG_REG_70 B0;
	FG_REG_74 NA1;
	FG_REG_78 NA2;
	FG_REG_7C FG_TCNT_CON;
	FG_REG_80 SOC_R;
	FG_REG_84 SOH;
	FG_REG_88 BATCAP_OCV_new;
	FG_REG_8C FCC;
	FG_REG_90 BATCAP_OCV_new_IN;		// 90
	FG_REG_BAT_DATA OCV12_LUT1;			// 94
	FG_REG_BAT_DATA OCV12_LUT3;			// 98
	FG_REG_BAT_DATA OCV12_LUT5;			// 9C
	FG_REG_BAT_DATA OCV12_LUT7;			// A0
	FG_REG_BAT_DATA OCV12_LUT9;			// A4
	FG_REG_BAT_DATA OCV12_LUT11;		// A8
	FG_REG_BAT_DATA OCV12_LUT13;		// AC
	FG_REG_BAT_DATA OCV12_LUT15;		// B0
	FG_REG_BAT_DATA OCV12_LUT17;		// B4
	FG_REG_BAT_DATA OCV12_LUT19;		// B8
	FG_REG_BAT_DATA OCV12_LUT21;		// BC
	FG_REG_BAT_DATA SOC12_LUT1;			// C0
	FG_REG_BAT_DATA SOC12_LUT3;			// C4
	FG_REG_BAT_DATA SOC12_LUT5;			// C8
	FG_REG_BAT_DATA SOC12_LUT7;			// CC
	FG_REG_BAT_DATA SOC12_LUT9;			// D0
	FG_REG_BAT_DATA SOC12_LUT11;		// D4
	FG_REG_BAT_DATA SOC12_LUT13;		// D8
	FG_REG_BAT_DATA SOC12_LUT15;		// DC
	FG_REG_BAT_DATA SOC12_LUT17;		// E0
	FG_REG_BAT_DATA SOC12_LUT19;		// E4
	FG_REG_BAT_DATA SOC12_LUT21;		// E8
	FG_REG_BAT_DATA RS8_LUT2;			// EC
	FG_REG_BAT_DATA RS8_LUT6;			// F0
	FG_REG_BAT_DATA RS8_LUT10;			// F4
	FG_REG_BAT_DATA RS8_LUT14;			// F8
	FG_REG_BAT_DATA RS8_LUT18;			// FC

}FG_BLOCK_Type;

#endif
