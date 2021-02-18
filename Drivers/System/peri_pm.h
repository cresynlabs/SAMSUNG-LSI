#ifndef _PERI_PM_H_
#define _PERI_PM_H_

typedef union
{
    uint32_t DATA;
    struct {
        uint32_t   Reserved:32;
  } BITS;
}PMReserved_Type;

typedef union
{
	  uint32_t DATA;
	  struct {
		  uint32_t TDIEUP:1,
		  	       VPOGORUP:1,
		  	       VPOGOLUP:1,
		  	       VBATUP:1,
		  	       VSYSUP:1,
		  	       VBYPUP:1,
		  	       VWCINUP:1,
		  	       VCHGINUP:1,
		  	       Reserved1:1,
		  	       RSVD3UP:1,
		  	       RSVD2UP:1,
		  	       RSVD1UP:1,
		  	       IPOGORUPL:1,
		  	       IPOGOLUP:1,
		  	       IWCINUP:1,
		  	       ICHGINUP:1,
		  	       Reserved2:4,
		  	       RPOGORUP:1,
		  	       RPOGOLUP:1,
		  	       IMODRUP:1,
		  	       IMODLUP:1,
		  	       PM_OFF:1,
		  	       PM_ON:1,
		  	       POGOR_Detach:1,
		  	       POGOL_Detach:1,
		  	       Reserved3:4;
	} BITS;
}PM_REG_00;

typedef union
{
	  uint32_t DATA;
	  struct {
		  uint32_t TDIEI:1,
		  	       VPOGORI:1,
		  	       VPOGOLI:1,
		  	       VBATI:1,
		  	       VSYSI:1,
		  	       VBYPI:1,
		  	       VWCINI:1,
		  	       VCHGINI:1,
		  	       Reserved1:1,
		  	       RSVD3I:1,
		  	       RSVD2I:1,
		  	       RSVD1I:1,
		  	       IPOGORI:1,
		  	       IPOGOLI:1,
		  	       IWCINI:1,
		  	       ICHGINI:1,
		  	       Reserved2:4,
		  	       RPOGORI:1,
		  	       RPOGOLI:1,
		  	       IMODRI:1,
		  	       IMODLI:1,
		  	       IWCIN_TH:1,
		  	       ICHGIN_TH:1,
		  	       PM_OSC_OFF:1,
		  	       PM_OSC_ON:1,
		  	       Reserved3:4;
	} BITS;
}PM_REG_04;


typedef union
{
	  uint32_t DATA;
	  struct {
		  uint32_t TDIEUM:1,
		  	       VPOGORUM:1,
		  	       VPOGOLUM:1,
		  	       VBATUM:1,
		  	       VSYSUM:1,
		  	       VBYPUM:1,
		  	       VWCINUM:1,
		  	       VCHGINUM:1,
		  	       Rserved1:1,
		  	       RSVD3UM:1,
		  	       RSVD2UM:1,
		  	       RSVD1UM:1,
		  	       IPOGORUM:1,
		  	       IPOGOLUM:1,
		  	       IWCINUM:1,
		  	       ICHGINUM:1,
		  	       Reserved2:4,
		  	       RPOGORUM:1,
		  	       RPOGOLUM:1,
		  	       IMODRUM:1,
		  	       IMODLUM:1,
		  	       PM_OFFM:1,
		  	       PM_ONM:1,
		  	       POGOR_DetachM:1,
		  	       POGOL_DetachM:1,
		  	       Reserved3:4;
	} BITS;
}PM_REG_08;

typedef union
{
	  uint32_t DATA;
	  struct {
		  uint32_t TDIEIM:1,
		  	       VPOGORIM:1,
		  	       VPOGOLIM:1,
		  	       VBATIM:1,
		  	       VSYSIM:1,
		  	       VBYPIM:1,
		  	       VWCINIM:1,
		  	       VCHGINIM:1,
		  	       Reserved1:1,
		  	       RSVD3IM:1,
		  	       RSVD2IM:1,
		  	       RSVD1IM:1,
		  	       IOGORIM:1,
		  	       IPOGOLIM:1,
		  	       IWCINIM:1,
		  	       ICHGINIM:1,
		  	       Reserved2:4,
		  	       RPOGORIM:1,
		  	       RPOGOLIM:1,
		  	       IMODRIM:1,
		  	       IMODLIM:1,
		  	       IWCIN_THM:1,
		  	       ICHGIN_TMH:1,
		  	       PM_OSCOFFM:1,
		  	       PM_OSC_ONM:1,
		  	       Reserved3:4;
	} BITS;
}PM_REG_0C;


typedef union
{
	  uint32_t DATA;
	  struct {
		  uint32_t VADC_CHGIN:16,
		  	       IADC_CHGIN:16;
	} BITS;
}PM_REG_10;

typedef union
{
	  uint32_t DATA;
	  struct {
		  uint32_t VADC_WCIN:16,
		  	       IADC_WCIN:16;
	} BITS;
}PM_REG_14;

typedef union
{
	  uint32_t DATA;
	  struct {
		  uint32_t VADC_SYS:16,
		  	       VADC_BAT:16;
	} BITS;
}PM_REG_18;

typedef union
{
	  uint32_t DATA;
	  struct {
		  uint32_t VADC_POGOL:16,
		  	       IADC_POGOL:16;
	} BITS;
}PM_REG_1C;

typedef union
{
	  uint32_t DATA;
	  struct {
		  uint32_t VADC_POGOR:16,
		  	       IADC_POGOR:16;
	} BITS;
}PM_REG_20;

typedef union
{
	  uint32_t DATA;
	  struct {
		  uint32_t TADC_DIE:16,
		  	       VADC_BYP:16;
	} BITS;
}PM_REG_24;

typedef union
{
	  uint32_t DATA;
	  struct {
		  uint32_t VADC_RSVD1:16,
		  	       VADC_RSVD2:16;
	} BITS;
}PM_REG_28;

typedef union
{
	  uint32_t DATA;
	  struct {
		  uint32_t VADC_RSVD3:16,
		  	       Reserved:16;
	} BITS;
}PM_REG_2C;

typedef union
{
	  uint32_t DATA;
	  struct {
		  uint32_t IADC_MODL:16,
		  	       IADC_MODR:16;
	} BITS;
}PM_REG_30;

typedef union
{
	  uint32_t DATA;
	  struct {
		  uint32_t RADC_POGOL:16,
		  	       RADC_POGOR:16;
	} BITS;
}PM_REG_34;

typedef union
{
	  uint32_t DATA;
	  struct {
		  uint32_t IWCIN_STAT:1,
		  	       ICHGIN_STAT:1,
		  	       Reserved1:6,
		  	       DAC_MODR:12,
		  	       DAC_MODEL:12;
	} BITS;
}PM_REG_38;

typedef union
{
	  uint32_t DATA;
	  struct {
		  uint32_t TDIECM_TA:1,
		  	       RSCD2CM_TA:1,
		  	       RSVD1CM_TA:1,
		  	       VBATCM_TA:1,
		  	       VSYSCM_TA:1,
		  	       VBYPCM_TA:1,
		  	       ICHGINCM_TA:1,
		  	       VCHGINCM_TA:1,
		  	       TDIECM_WC:1,
		  	       RSVD2CM_WC:1,
		  	       RSVD1CM_WC:1,
		  	       VBATCM_WC:1,
		  	       VSYSCM_WC:1,
		  	       VBYPCM_WC:1,
		  	       IWCINCM_WC:1,
		  	       VWCINCM_WC:1,
		  	       TDIECM_PGLL:1,
		  	       Reserved1:3,
		  	       IMODLCM_PGL:1,
		  	       VBYPCM_PGL:1,
		  	       IPOGOLCM_PGL:1,
		  	       VPOGOLCM_PGL:1,
		  	       TDIECM_PGR:1,
		  	       Reserved2:3,
		  	       IMODRCM_PGR:1,
		  	       VBYPCM_PGR:1,
		  	       IPOGORCM_PGR:1,
		  	       VPOGORCM_PGR:1;
	} BITS;
}PM_REG_3C;


typedef union
{
	  uint32_t DATA;
	  struct {
		  uint32_t TDIECD:1,
		  	       VPOGORCD:1,
		  	       VPOGOLCD:1,
		  	       VBATCD:1,
		  	       VSYSCD:1,
		  	       VBYPCD:1,
		  	       VWCINCD:1,
		  	       VCHGINCD:1,
		  	       Reserved1:1,
		  	       RSVD3CD:1,
		  	       RSVD2CD:1,
		  	       RSVD1CD:1,
		  	       IPOGORCD:1,
		  	       IPOGOLCD:1,
		  	       IWCINCD:1,
		  	       ICHGINCD:1,
		  	       Reserved2:6,
		  	       RPOGORCD:1,
		  	       RPOGOLCD:1,
		  	       Reserved3:8;
	} BITS;
}PM_REG_40;


typedef union
{
	uint32_t DATA;
	  struct {
		  uint32_t TCLK_EN:1,
		  	       TEST_BUF_EN:1,
		  	       VREF_TOSEL:1,
		  	       STC_EXT_EN:1,
		  	       AEXT_VREF_SEL:1,
		  	       CLKSEL_EXT:1,
		  	       STBY_EXT:1,
		  	       TEST_ANALOG:1,
		  	       CHSEL_EXT0:1,
		  	       CHSEL_EXT1:1,
		  	       CHSEL_EXT2:1,
		  	       CHSEL_EXT3:1,
		  	       CHSEL_EXT4:1,
		  	       Reserved1:1,
		  	       TCLKSEL0:1,
		  	       TCLKSEL1:1,
		  	       PM_MONITOR0:1,
		  	       PM_MONITOR1:1,
		  	       PM_MONITOR2:1,
		  	       PM_MONITOR3:1,
		  	       PM_MONITOR4:1,
		  	       Reserved2:2,
		  	       TEST_BUF_OS:1,
		  	       Reserved3:4,
		  	       IMODRCO:1,
		  	       IMODLCO:1,
		  	       IMODRRR:1,
		  	       IMODLRR:1;
	} BITS;
}PM_REG_44;

typedef union
{
	uint32_t DATA;
	  struct {
		  uint32_t TDIERR:1,
		  	       VPOGORRR:1,
		  	       VPOGOLRR:1,
		  	       VBAT1RR:1,
		  	       VSYSRR:1,
		  	       VBYPRR:1,
		  	       VWCINRR:1,
		  	       VCHGINRR:1,
		  	       Reserved1:1,
		  	       RSVD3RR:1,
		  	       RSVD2RR:1,
		  	       RSVD1RR:1,
		  	       IPOGORRR:1,
		  	       IPOGOLRR:1,
		  	       IWCINRR:1,
		  	       ICHGINRR:1,
		  	       Reserved2:16;
	} BITS;
}PM_REG_48;

typedef union
{
	uint32_t DATA;
	  struct {
		  uint32_t TDIECO:1,
		  	       VPOGORCO:1,
		  	       VPOGOLCO:1,
		  	       VBAT1CO:1,
		  	       VSYSCO:1,
		  	       VBYPCO:1,
		  	       VWCINCO:1,
		  	       VCHGINCO:1,
		  	       Reserved1:1,
		  	       RSVD3CO:1,
		  	       RSVD2CO:1,
		  	       RSVD1CO:1,
		  	       IPOGORCO:1,
		  	       IPOGOLCO:1,
		  	       IWCINCO:1,
		  	       ICHGINCO:1,
		  	       Reserved2:16;
	} BITS;
}PM_REG_4C;

typedef union
{
	uint32_t DATA;
	  struct {
		  uint32_t PM_CTRL1:8,
		  	       PM_CTRL2:8,
		  	       PM_CTRL3:8,
		  	       Reserved:8;
	} BITS;
}PM_REG_50;

typedef union
{
	uint32_t DATA;
	  struct {
		  uint32_t HV_AVG:3,
		  	       Reserved1:1,
		  	       DISCARD_SAMPLES_HV:3,
		  	       Reserved2:1,
		  	       EARBUD_AVG:3,
		  	       Reserved3:1,
		  	       DISCARD_SAMPLES_EARBUD:3,
		  	       Reserved4:1,
		  	       CUR_AVG:3,
		  	       Reserved5:1,
		  	       DISCARD_SAMPLES_CUR:3,
		  	       Reserved6:9;
	} BITS;
}PM_REG_6C;

typedef union
{
	uint32_t DATA;
	  struct {
		  uint32_t HYST_LEV_IMODR:3,
		  	       Reserved1:1,
		  	       HYST_LEV_IMODEL:3,
		  	       Reserved2:1,
		  	       HYST_LEV_IPOGOR:3,
		  	       Reserved3:1,
		  	       HYST_LEV_IPOGOL:3,
		  	       Reserved4:1,
		  	       HYST_LEV_VPOGOR:3,
		  	       Reserved5:1,
		  	       HYST_LEV_VPOGOL:3,
		  	       Reserved6:1,
		  	       HYST_LEV_VWCIN:3,
		  	       Reserved7:1,
		  	       HYST_LEV_VCHGIN:3,
		  	       Reserved8:1;
	} BITS;
}PM_REG_70;

typedef union
{
	uint32_t DATA;
	  struct {
		  uint32_t HYST_LEV_VSYS:3,
		  	       Reserved1:1,
		  	       HYST_LEV_VBYP:3,
		  	       Reserved2:5,
		  	       HYST_LEV_VBAT:3,
		  	       Reserved3:1,
		  	       HYST_LEV_IWCIN:3,
		  	       Reserved4:1,
		  	       HYST_LEV_ICHGIN:3,
		  	       Reserved5:1,
		  	       HYST_LEV_RSVD1:3,
		  	       Reserved6:1,
		  	       HYST_LEV_TDIE:3,
		  	       Reserved7:1;
	} BITS;
}PM_REG_74;


typedef union
{
	uint32_t DATA;
	  struct {
		  uint32_t HYST_LEV_VRSVD3:3,
		  	       Reserved1:1,
		  	       HYST_LEV_VRSVD2:3,
		  	       Reserved:25;
	} BITS;
}PM_REG_78;

typedef union
{
	uint32_t DATA;
	  struct {
		  uint32_t Reserved1:8,
		  	       PM_LPFC0:1,
		  	       PM_LPFC1:1,
		  	       Reserved2:14,
		  	       ATE_CLK_SEL:1,
		  	       Reserved3:1,
		  	       SEL_REDUCE_CUR:2,
		  	       SEL_REDUCE_EARBUD:2,
		  	       SEL_REDUCE_HV:2;
	} BITS;
}PM_REG_7C;

typedef union
{
	uint32_t DATA;
	  struct {
		  uint32_t PLC_DACR_INIT:1,
		  	       PLC_DACL_INIT:1,
		  	       OFFSET_SHIFT_CUR:2,
		  	       OFFSET_SHIFT_EARBUD:2,
		  	       OFFSET_SHIFTHV:2,
		  	       PLC_NONMCU_RR:1,
		  	       CLK_FORCE_EN:1,
		  	       CH_END_OPT:1,
		  	       Reset:2,
		  	       Reserved1:3,
		  	       PM_Soft_RST:1,
		  	       DIG_MONITOR:7,
		  	       Reserved2:8;
	} BITS;
}PM_REG_80;

typedef union
{
	uint32_t DATA;
	  struct {
		  uint32_t IDEMOD_THL1:2,
		  	       Sign_BIT1:1,
		  	       Reserved1:5,
		  	       IDEMOD_THL2:8,
		  	       IDEMOD_THR1:2,
		  	       Sign_BIT2:1,
		  	       Reserved2:5,
		  	       IDEMOD_THR2:8;
	} BITS;
}PM_REG_84;

typedef union
{
	uint32_t DATA;
	  struct {
		  uint32_t IADC_MODL_TEST:12,
		  	       Reserved1:1,
		  	       MODL_ING_TEST:1,
		  	       MODL_ING_TESTEN:1,
		  	       MODL_TESTEN:1,
		  	       IADC_MODR_TEST:12,
		  	       Reserved2:1,
		  	       MODR_ING_TEST:1,
		  	       MODR_ING_TESTEN:1,
		  	       MODR_TESTEN:1;
	} BITS;
}PM_REG_88;


typedef struct
{
	PM_REG_00       REG_00;
	PM_REG_04       REG_04;
	PM_REG_08       REG_08;
	PM_REG_0C       REG_0C;
	PM_REG_10       REG_10;
	PM_REG_14       REG_14;
	PM_REG_18       REG_18;
	PM_REG_1C       REG_1C;
	PM_REG_20       REG_20;
	PM_REG_24       REG_24;
	PM_REG_28       REG_28;
	PM_REG_2C       REG_2C;
	PM_REG_30       REG_30;
	PM_REG_34       REG_34;
	PM_REG_38       REG_38;
	PM_REG_3C       REG_3C;
	PM_REG_40       REG_40;
	PM_REG_44       REG_44;
	PM_REG_48       REG_48;
	PM_REG_4C       REG_4C;
	PM_REG_50       REG_50;
	PMReserved_Type REG_54;
	PMReserved_Type REG_58;
	PMReserved_Type REG_5C;
	PMReserved_Type REG_60;
	PMReserved_Type REG_64;
	PMReserved_Type REG_68;
	PM_REG_6C       REG_6C;
	PM_REG_70       REG_70;
	PM_REG_74       REG_74;
	PM_REG_78       REG_78;
	PM_REG_7C       REG_7C;
	PM_REG_80       REG_80;
	PM_REG_84       REG_84;
	PM_REG_88       REG_88;
}PM_BLOCK_Type;

#endif
