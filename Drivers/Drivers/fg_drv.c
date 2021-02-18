/*
******************************************************************************
* @file    fg_drv.c
* @author  Power Device Team
* @version V1.0.0
* @brief   Main System StartUp
******************************************************************************
*/

#include "cm0pikmcu.h"
#include "fg_drv.h"
#include "common_drv.h"
#include "sc_drv.h"

void fg2_irq_enable(void)
{
	NVIC_EnableIRQ(IRQ04_FG2);
}

void boot_fg2_irqhandler(void)
{
	NVIC_ClearPendingIRQ(IRQ04_FG2);
}

/* 0x03[5:4] IF_EN
 * TRUE : 0b11
 * FALSE : 0b00 */
void fg_drv_set_if_en(char data)
{
	FG.STATUS.BITS.IF_EN = data;
}

/* 0x0C[6] BATCAP_OCV_EN */
void fg_drv_set_batcap_ocv_en(char data)
{
	FG.MONOUT_SEL.BITS.BATCAP_OCV_EN = data;
}

/* 0x0F ~ 0x0E BATCAP_OCV */
void fg_drv_set_batcap_ocv(uint16_t data)
{
	FG.MONOUT_SEL.BITS.BATCAP_OCV = data;
}

/* 0x11 ~ 0x10 BATCAP */
void fg_drv_set_batcap(uint16_t data)
{
	FG.BATCAP.BITS.BATCAP = data;
}

/* DUMP done
 * 0x1E[1:0]DUMP_DONE */
void fg_drv_set_start(void)
{
	/* FG.TEMP_LVL.BITS.DUMP_DONE=3;
	 * FG.TEMP_LVL.BITS.RESTART=3;
	   write DUMP_DONE & RESTART at the same time */
	FG.TEMP_LVL.DATA |= 0xf << 16;
}

/* Restart
 * 0x1E[3:2] RESTART */
void fg_drv_set_restart(void)
{
	FG.TEMP_LVL.BITS.RESTART = 3;
}

/* 0x29[7:1] SOC_I2C, 0x29[0] SOC_FORCE_EN
 * Lowest bit of SOC_I2C is enable bit. then it is always '1'
 * 1lsb is 0.39 % */
void fg_drv_set_soc_i2c(float data)
{
	uint8_t socdata;

	data = data / SOC_RESOLUTION;

	if (data >= 255)
		socdata = 0xFF;
	else
		socdata = (uint8_t)data;
	socdata |= 0x01;		/* lowest bit is always 1(enable bit and data bit) */
	FG.VTEMP_I2C.BITS.SOC_I2C = socdata;
}

/*
 * Get SOC data
 * 0x81 ~ 0x80 rSOC_R[16] */
float fg_drv_get_soc_r(void)
{
	signed short int raw_soc;
	double ori_soc;


	raw_soc = FG.SOC_R.BITS.SOC_R;
	ori_soc = raw_soc / (double)(1<<14);

	if (ori_soc > 1.0f)
		ori_soc = 1.0f;

	return (float)ori_soc;
}

void fg_drv_set_design_cap(uint16_t data)
{
	FG.SOH.BITS.Design_CAP = data;
}

float fg_drv_get_cur_cc(void)
{
	int16_t curr;
	float currf;

	curr = FG.VBAT.BITS.CUR_CC;

	currf = curr / (float)(1 << 13);


	return currf;
}

float fg_drv_get_cur_cc_avg(void)
{
	int16_t curr;
	float currf;

	FG.MONOUT_SEL.BITS.MONOUT_SEL = 0x17;
	sysdelay_us(10);

	curr = FG.SOC_CC.BITS.MONOUT;

	currf = curr / (float)(1 << 13);

	return currf;

}

float fg_drv_get_temp(void)
{
	int16_t temp;
	float tempf;

	FG.MONOUT_SEL.BITS.MONOUT_SEL = 0x10;
	sysdelay_us(10);

	temp = FG.SOC_CC.BITS.MONOUT;
	tempf = temp / (float)(1 << 8) - 1.5f;		/* Set -1.5 offset by ssh */
	sysdelay_us(10);
	
	return tempf;

}

float fg_drv_get_vbat_avg(void)
{
	int16_t vbat;
	float vbatf;

	FG.MONOUT_SEL.BITS.MONOUT_SEL = 0x16;
	sysdelay_us(10);

	vbat = FG.SOC_CC.BITS.MONOUT;
	vbatf = vbat / (float)(1 << 12);

	return vbatf;

}


/* ATL Battery data
 * by Moon */
void fg_drv_set_ocv_soc_rs_lut(void)
{
	FG.BATCAP_OCV_new_IN.BITS.BATCAP_OCV_new_IN = 0x03D4 >> 1;
	FG.BATCAP_OCV_new_IN.BITS.Wrtie_EN = 1;

	FG.BATCAP_OCV_new_IN.BITS.rOCV12_LUT0_0 = 0xFB;
	FG.BATCAP_OCV_new_IN.BITS.rOCV12_LUT0_1 = 0x08;

	/* OCV Table Example */
	FG.OCV12_LUT1.DATA = 0x087208AE;
	FG.OCV12_LUT3.DATA = 0x07E90832;
	FG.OCV12_LUT5.DATA = 0x0757079E;
	FG.OCV12_LUT7.DATA = 0x068B06FD;
	FG.OCV12_LUT9.DATA = 0x06050647;
	FG.OCV12_LUT11.DATA = 0x058005BE;
	FG.OCV12_LUT13.DATA =0x0523054E;
	FG.OCV12_LUT15.DATA =0x04BB04F1;
	FG.OCV12_LUT17.DATA =0x043F0483;
	FG.OCV12_LUT19.DATA =0x03CC0402;
	FG.OCV12_LUT21.DATA =0x08000275;

	FG.SOC12_LUT1.DATA = 0x0736079B;
	FG.SOC12_LUT3.DATA = 0x05A10606;
	FG.SOC12_LUT5.DATA = 0x05A10606;
	FG.SOC12_LUT7.DATA = 0x04D6053B;
	FG.SOC12_LUT9.DATA = 0x040C0471;
	FG.SOC12_LUT11.DATA =0x034103A7;
	FG.SOC12_LUT13.DATA =0x027702DC;
	FG.SOC12_LUT15.DATA =0x01AC0212;
	FG.SOC12_LUT17.DATA =0x00E20147;
	FG.SOC12_LUT19.DATA =0x0018007D;
	FG.SOC12_LUT21.DATA =0x0A0A0FB2;
	FG.RS8_LUT2.DATA   = 0xBAB90A0A;
	FG.RS8_LUT6.DATA   = 0xB4ACAFB7;
	FG.RS8_LUT10.DATA  = 0xB2AAAFB1;
	FG.RS8_LUT14.DATA  = 0xC2BBB8B6;
	FG.RS8_LUT18.DATA  = 0xFFFFDFCF;
}

float fg_drv_get_vbat(void)
{
	int16_t curr;
	float currf;

	sysdelay_us(10);

	curr = FG.VBAT.BITS.VBat;

	curr = curr - 0x7CCC;
	currf = 3.9f + ((curr * 0.122f) / 1000);

	return currf;

}

void fg_drv_set_edv(uint8_t data)
{
	FG.EDV.BITS.EDV = data;
}

/* Check the surge of Fuel gauge
 * If surge, Fuel gague needs to reset */
uint8_t fg_drv_get_surge(void)
{
	volatile uint8_t *direct_addr1, *direct_addr2;
	direct_addr1  = (volatile uint8_t *)0xF000301E;
	direct_addr2  = (volatile uint8_t *)0xF000301F;

	if (*direct_addr1 == 0x03 && *direct_addr2 == 0x00)
		return FALSE;
	else
		return TRUE;
}

void fg_drv_set_init_done(void)
{
	FG.TEMP_LVL.BITS.JIGB = 0;
}

void fg_drv_set_voltage_mode(uint8_t enable)
{
	FG_REG_64 temp_D0;

	temp_D0.DATA = FG.Temp_D0.DATA;

	temp_D0.BITS.VM_FORCE_EN = enable;
	temp_D0.BITS.VM_FORCE = enable;

	FG.Temp_D0.DATA = temp_D0.DATA;
}

void fg_drv_set_inc_ok_en(uint8_t enable)
{
	FG.Temp_D0.BITS.INC_OK_EN = enable;
}

