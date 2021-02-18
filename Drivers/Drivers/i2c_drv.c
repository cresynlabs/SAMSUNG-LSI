#include "cm0pikmcu.h"
#include "i2c_drv.h"

volatile uint32_t i2c_status_flag;
volatile uint32_t i2c_data_ack;
volatile uint8_t  i2c_wr_buf;
volatile uint8_t  i2c_rd_buf;

const uint8_t REG_ACCESS_AREA[16] =
{
	I2C_REG_ACCESS_OK,
	I2C_REG_ACCESS_OK,
	I2C_REG_ACCESS_OK,
	I2C_REG_ACCESS_OK,
	I2C_REG_ACCESS_OK,
	I2C_REG_ACCESS_OK,
	I2C_REG_ACCESS_OK,
	I2C_REG_ACCESS_OK,
	I2C_REG_ACCESS_OK,
	I2C_REG_ACCESS_OK,
	I2C_REG_ACCESS_OK,
	I2C_REG_ACCESS_OK,
	I2C_REG_ACCESS_SKIP,
	I2C_REG_ACCESS_OK,
	I2C_REG_ACCESS_OK,
	I2C_REG_ACCESS_SKIP
};

extern const uint8_t REG_ACCESS_AREA[16];

void i2c_master_init(uint32_t i2c_mode)
{
	if (i2c_mode == I2C_MODE_SEL_2)
	{
		MI2C.ICCR.BITS.CLKREG = 0x3;
		MI2C.ICCR.BITS.IRQen = 0x1;
		MI2C.ICSR.BITS.SerialOutputEn = 0x1;
		MI2C.ICCR.BITS.ACKen = 0x1;
		MI2C.ICCR.BITS.SCL_UNMASK = 0x0;
	}

	return;
}

void boot_mi2c1_irqhandler(void)
{
	if (MI2C.ICSR.BITS.MST == I2C_BUS_MASTER)
	{
		if (i2c_status_flag == I2C_MASTER_TX_STATUS)
			MI2C.IDSR.BITS.DataSftReg = i2c_wr_buf;
		else if (i2c_status_flag == I2C_MASTER_RX_STATUS)
			i2c_rd_buf = (uint8_t)(MI2C.IDSR.DATA & 0xFF);
		else if (i2c_status_flag == I2C_MASTER_RX_LAST)
		{
			i2c_rd_buf = (uint8_t)(MI2C.IDSR.DATA & 0xFF);
			i2c_status_flag = I2C_MASTER_STOP;

			NVIC_DisableIRQ(IRQ02_MI2C);
		}
		else
		{
			MI2C.STOPCON.BITS.SCLRelease = 0x1;
			MI2C.ICSR.BITS.BUSY = 0x0;
			MI2C.ICSR.BITS.SerialOutputEn = 0x0;

			NVIC_DisableIRQ(IRQ02_MI2C);
		}

		i2c_data_ack = I2C_MASTER_ACK;
	}

	__clr_IRQ_I2C2();

	NVIC_ClearPendingIRQ(IRQ02_MI2C);

	return;
}

uint32_t i2c_master_data_write(uint8_t wdata)
{
	uint32_t sys_time = 0;

	i2c_data_ack = I2C_MASTER_None;
	i2c_wr_buf = wdata;

	NVIC_EnableIRQ(IRQ02_MI2C);

	sys_time = sys_get_tick();
	while (i2c_data_ack == I2C_MASTER_None)
	{
		if (sys_get_tick() - sys_time > 100)
			return RET_FAIL;
	}

	return RET_OK;
}

uint32_t i2c_master_data_read(uint8_t *rdata)
{
	uint32_t sys_time = 0;

	i2c_data_ack = I2C_MASTER_None;

	NVIC_EnableIRQ(IRQ02_MI2C);

	sys_time = sys_get_tick();
	while (i2c_data_ack == I2C_MASTER_None)
	{
		if (sys_get_tick() - sys_time > 100)
			return RET_FAIL;
	}

	*rdata = i2c_rd_buf;

	return RET_OK;
}



uint32_t i2c_start(uint32_t slvaddr, uint32_t mode, uint32_t waitmode)
{
	uint32_t sys_time = 0;

	i2c_data_ack = I2C_MASTER_None;

	MI2C.IDSR.BITS.DataSftReg = slvaddr;
	MI2C.ICSR.BITS.MST = I2C_BUS_MASTER;

	if (mode == I2C_TX)
	{
		i2c_status_flag = I2C_MASTER_TX_STATUS;
		MI2C.ICSR.BITS.TRAN = I2C_TX; /* Master  Tx */
	}
	else
	{
		i2c_status_flag = I2C_MASTER_RX_STATUS;
		MI2C.ICSR.BITS.TRAN = I2C_RX; /* Master Rx */
	}

	MI2C.ICSR.BITS.BUSY = 0x1;

	NVIC_EnableIRQ(IRQ02_MI2C);

	if (waitmode == I2C_IRQ_WAIT)
	{
		sys_time = sys_get_tick();
		while (i2c_data_ack == I2C_MASTER_None)
		{
			if (sys_get_tick() - sys_time > 100)
				return RET_FAIL;
		}
	}

	return RET_OK;
}

uint32_t i2c_stop(uint32_t waitmode)
{
	uint32_t sys_time = 0;

	i2c_data_ack = I2C_MASTER_None;

	i2c_status_flag = I2C_MASTER_STOP;
	NVIC_EnableIRQ(IRQ02_MI2C);


	if (waitmode == I2C_IRQ_WAIT)
	{
		sys_time = sys_get_tick();
		while (i2c_data_ack == I2C_MASTER_None)
		{
			if (sys_get_tick() - sys_time > 100)
				return RET_FAIL;
		}
	}

	return RET_OK;
}

uint32_t write_i2c(uint32_t slave_addr, uint32_t reg_addr, uint8_t *wdata, uint32_t data_size)
{
	uint32_t ret_code = RET_OK;
	uint32_t data_count;

	i2c_status_flag = I2C_MASTER_STOP;
	i2c_data_ack = I2C_MASTER_None;

	i2c_master_init(I2C_MODE_SEL_2);

	ret_code = i2c_start(slave_addr, I2C_TX, I2C_IRQ_NONE);
	if (ret_code != RET_OK)
		return ret_code;

	ret_code = i2c_master_data_write(reg_addr);
	if (ret_code != RET_OK)
		return ret_code;

	for (data_count = 0; data_count <data_size; data_count++)
	{
		ret_code = i2c_master_data_write(*wdata);
		if (ret_code != RET_OK)
			return ret_code;
	}

	ret_code = i2c_stop(I2C_IRQ_WAIT);
	if (ret_code != RET_OK)
		return ret_code;

	return ret_code;
}

uint32_t read_i2c(uint32_t slave_addr, uint32_t reg_addr,
						uint8_t *rdata, uint32_t data_size)
{
	uint32_t ret_code = RET_OK;
	uint32_t data_count;

	/* Read Hang */
	i2c_status_flag = I2C_MASTER_STOP;
	i2c_data_ack = I2C_MASTER_None;

	i2c_master_init(I2C_MODE_SEL_2);

	ret_code = i2c_start(slave_addr, I2C_TX, I2C_IRQ_NONE);
	if (ret_code != RET_OK)
		return ret_code;

	ret_code = i2c_master_data_write(reg_addr);
	if (ret_code != RET_OK)
		return ret_code;

	ret_code = i2c_stop(I2C_IRQ_WAIT);
	if (ret_code != RET_OK)
		return ret_code;

	i2c_master_init(I2C_MODE_SEL_2);

	ret_code = i2c_start(slave_addr, I2C_RX, I2C_IRQ_WAIT);

	for (data_count = 0; data_count < data_size; data_count++)
	{
		if (data_count >= (data_size - 1))
		{
			i2c_status_flag = I2C_MASTER_RX_LAST;
			MI2C.ICCR.BITS.ACKen = 0x0;
		}
		ret_code = i2c_master_data_read(&rdata[data_count]);
		if (ret_code != RET_OK)
			return ret_code;
	}

	MI2C.STOPCON.BITS.DataSftCtrl = 0x1;
	ret_code = i2c_stop(I2C_IRQ_NONE);
	if (ret_code != RET_OK)
		return ret_code;
	__set_RX_STOP_MST_I2C2();

	return ret_code;
}

void i2c_slave_init(void)
{
	/* GPIO Selection */
	BOOTCON.GPIO_SRC_SEL.BITS.SRC_SEL_OUT_PI2C = 0;
	BOOTCON.GPIO_SRC_SEL.BITS.SRC_SEL_IN_PI2C = 0;

	/* RESET */
	SYSREG.Soft_Rst.BITS.PI2C_RESET = 1;

	/* 16bit mode set */
	__set_PI2C_16BIT_MODE(); /* 2Bytes ADDR */

	/* IRQ Enable */
	NVIC_EnableIRQ(IRQ01_PI2C);
	PI2C.SLV_CONF.BITS.SLV_IRQ_EN = 0x1;

	/* IRQ Clear */
	__clr_IRQ_PI2C();
}

void i2c_register_access(void)
{
	uint32_t *reg_addr;

	uint32_t reg_acc_addr;
	uint32_t align_ofs;

	uint8_t i2c_cmd_select;
	uint8_t i2c_area_select;


	i2c_register_access_t  i2c_reg_data;

	i2c_area_select = (I2C_HOST_WR_DATA16_H >> 4);
	printf("i2c_area_select = 0x%4X\n\r", i2c_area_select);

	reg_acc_addr = PERIPH_BASE;
	align_ofs = 0;

	if (REG_ACCESS_AREA[i2c_area_select] == I2C_REG_ACCESS_OK)
	{
		reg_acc_addr = (reg_acc_addr + ((uint32_t)I2C_HOST_WR_DATA16));

		align_ofs = (reg_acc_addr % 4);
		reg_acc_addr = (reg_acc_addr - align_ofs);

		i2c_cmd_select = I2C_HOST_CMD_SEL;
	}
	else
		i2c_cmd_select = SEL_REG_BLANK;

	if (i2c_area_select == 0xE) /* PLC */
		printf("PLC Data Received\n\r");

	switch (i2c_cmd_select)
	{
	case SEL_WRITE_BYTE:
		reg_addr = (uint32_t *)reg_acc_addr;
		i2c_reg_data.DATA = *reg_addr;

		i2c_reg_data.BYTES.BDATA[align_ofs] = (I2C_SLV_DATA8 & 0xFF);
		*reg_addr = i2c_reg_data.DATA;
		printf("reg_addr = 0x%8X    Wrdata = 0x%2X\n\r",reg_addr,I2C_SLV_DATA8);

		I2C_SLV_DATA32 = 0;
		break;
	case SEL_WRITE_WORD:
		align_ofs = (align_ofs>>1);

		reg_addr = (uint32_t *)reg_acc_addr;
		i2c_reg_data.DATA = *reg_addr;

		i2c_reg_data.WORDS.WDATA[align_ofs] = (I2C_SLV_DATA16 & 0xFFFF);

		*reg_addr = i2c_reg_data.DATA;

		I2C_SLV_DATA32 = 0;
		break;
	case SEL_WRITE_LONG:
		reg_addr = (uint32_t *)reg_acc_addr;
		*reg_addr = I2C_SLV_DATA32;
		I2C_SLV_DATA32 = 0;
		break;
	case SEL_READ_BYTE:
		reg_addr = (uint32_t *)reg_acc_addr;
		i2c_reg_data.DATA = *reg_addr;

		I2C_SLV_DATA8 = (uint8_t)(i2c_reg_data.BYTES.BDATA[align_ofs] & 0xFF);

		break;
	case SEL_READ_WORD:
		align_ofs = (align_ofs>>1);
		reg_addr = (uint32_t *)reg_acc_addr;

		i2c_reg_data.DATA = *reg_addr;

		I2C_SLV_DATA16 = (uint16_t)(i2c_reg_data.WORDS.WDATA[align_ofs] & 0xFFFF);
		break;
	case SEL_READ_LONG:
		reg_addr = (uint32_t *)reg_acc_addr;
		I2C_SLV_DATA32 = *reg_addr;
		break;
	default :
		I2C_SLV_DATA32 = 0;
		break;
	}

	return;
}

void boot_pi2c1_irqhandler(void)
{
	__clr_IRQ_PI2C();

	printf("0x10(%#x), 0x11(%#x), 0x12(%#x), 0x13(%#x)\n\r",
		I2C_HOST_CMD_MODE, I2C_HOST_CMD_SEL, I2C_HOST_WR_DATA16_L, I2C_HOST_WR_DATA16_H);

	switch (I2C_HOST_CMD_MODE)
	{
	case MODE_BLANK:
		break;
	case MODE_INT_CLEAR:
		break;
	case MODE_REGISTER:
		i2c_register_access();
		break;
	default :
		break;
	}

	NVIC_ClearPendingIRQ(IRQ01_PI2C);
	return;
}
