/*
******************************************************************************
* @file    peri_i2c.h
* @author  Power Device Team
* @version V1.0.0
* @date    2015.01.27
* @brief   Header for I2C Control module
******************************************************************************
*/
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef _PERI_I2C_H_
#define _PERI_I2C_H_

typedef union
{
	uint32_t DATA;
	struct{
		uint32_t CLKREG:4,
			     subIRQ:1,
			     IRQen:1,
			     CLKSEL:1,
			     ACKen:1,
			     IRQClr:1,
			     REG_BANK_EN:1,
			     SCL_UNMASK:1,
			     Reserved:21;
		}BITS;
}MI2C_ICCR_Type;

typedef union
{
	uint32_t DATA;
	struct{
		uint32_t LastBitFlag:1,
			     ZeroStatusFlag:1,
			     AddressMatchFlag:1,
			     ArbitrationFalg:1,
			     SerialOutputEn:1,
			     BUSY:1,
			     TRAN:1,
			     MST:1,
			     EarlyStopFlag:1,
			     EarlyStartFlag:1,
			     ArbitrationFlagState:1,
			     Reserved:21;
		}BITS;
}MI2C_ICSR_Type;

typedef union
{
	uint32_t DATA;
	struct{
		uint32_t Reserved1:1,
			     SlaveAddr:7,
			     Reserved2:24;
		}BITS;
}MI2C_IAR_Type;

typedef union
{
	uint32_t DATA;
	struct{
		uint32_t DataSftReg:8,
			     DataLatchBuf:8,
			     RECSDA_SEL:2,
			     Reserved:14;
		}BITS;
}MI2C_IDSR_Type;

typedef union
{
	uint32_t DATA;
	struct{
		uint32_t SCLRelease:1,
			     SDARelease:1,
			     DataSftCtrl:1,
			     NACK_DET_MODE:1,
			     RX_LBA_MODE:1,
			     Reserved:27;
		}BITS;
}MI2C_STOPCON_Type;

typedef union
{
	uint32_t DATA;
	struct{
		uint32_t REG_BUF1:8,
			     REG_BUF2:8,
			     Reserved:16;
		}BITS;
}MI2C_REG_BUF_Type;

typedef union
{
	uint32_t DATA;
	struct{
		uint32_t SCL_SDA_FLAG:1,
			     VALID_DATA:1,
			     I2C_BUSY:1,
			     MI2C_IRQ_FLAG:1,
			     Reserved:28;
		}BITS;

}MI2C_ISTR_Type;

typedef union
{
	uint32_t DATA;
	struct{
		uint32_t I2C_IDLE_CHK_TIM:16,
			     Reserved:16;
		}BITS;
}MI2C_IDLE_CHECK_TIME_Type;

typedef union
{
	uint32_t DATA;
	struct{
		uint32_t IDLE:1,
			     CH_BUSY:1,
			     Reserved:30;
		}BITS;

}MI2C_IDLE_FLAG_Type;

typedef union
{
	uint32_t DATA;
	struct{
		uint32_t CTC_EN:1,
			CTC_START:1,
			CTC_SYNCL:1,
			CTC_Manual_Mode:1,
			Reserved1:4,
			CRC_IN:8,
			Reserved2:16;
		}BITS;
}MI2C_CRC_CAL_Type;

typedef union
{
	uint32_t DATA;
	struct{
		uint32_t CRC_OUT:8,
			     Reserved:24;
		}BITS;
}MI2C_CRC_OUT_Type;

typedef struct
{
	MI2C_ICCR_Type            ICCR;          // 0x0000
	MI2C_ICSR_Type            ICSR;          // 0x0004
	MI2C_IAR_Type             IAR;           // 0x0008
	MI2C_IDSR_Type            IDSR;          // 0x000C
	MI2C_STOPCON_Type         STOPCON;       // 0x0010
	MI2C_REG_BUF_Type         REGBUF;        // 0x0014
	MI2C_ISTR_Type            ISTR;          // 0x0018
	MI2C_IDLE_CHECK_TIME_Type IdleChkTime;   // 0x001C
	MI2C_IDLE_FLAG_Type       IdleFlag;      // 0x0020
	MI2C_CRC_CAL_Type         CRC_CALL;      // 0x0024
	MI2C_CRC_OUT_Type         CRC_OUT;       // 0x0028
}MI2C_BLOCK_Type;


typedef union
{
	uint32_t DATA;
	struct{
		uint32_t IRQ_ADDR:8,
			     ADDR_16BIT_MODE:1,
			     SLV_IRQ_EN:1,
			     SLV_IRQ_OPTION:1,
			     subIRQ:1,
			     IRQclr:1,
			     SCL_STRETCH_LPM:1,
			     SCL_STRETCH_EN:1,
			     SRAM_PROT_EN:1,
			     Reserved:16;
		}BITS;
}PI2C_SLV_CONF_Type;

typedef union
{
	uint32_t DATA;
	struct{
		uint32_t IDLE_CHK_TIM:16,
			     Reserved:16;
		}BITS;
}PI2C_IDLE_CHECK_TIME_Type;

typedef union
{
	uint32_t DATA;
	struct{
		uint32_t DEV_ADDR_FLASH:8,
			     DEV_ADDR_SRAM:8,
			     DEV_ADDR_PERI:8,
			     Reserved:8;
		}BITS;
}PI2C_SLV_ADDR_Type;

typedef union
{
	uint32_t DATA;
	struct{
		uint32_t INT_MASK:3,
			     Resred:29;
		}BITS;
}PI2C_SLV_INT_MASK;

typedef union
{
	uint32_t DATA;
	struct{
		uint32_t DMA_WADDR_OFFSET:24,
			     Reserved:8;
		}BITS;
}PI2C_DMA_WR_ADDR_OFFSET_Type;

typedef union
{
	uint32_t DATA;
	struct{
		uint32_t DMA_RADDR_OFFSET:24,
			     Reserved:8;
		}BITS;
}PI2C_DMA_RD_ADDR_OFFSET_Type;

typedef union
{
	uint32_t DATA;
	struct{
		uint32_t SRAM_LIMIT_ADDR_L:16,
			     SRAM_LIMIT_ADDR_H:16;
		}BITS;
}PI2C_DMA_SRAM_WR_LIMIT_ADDR_Type;

typedef union
{
	uint32_t DATA;
	struct{
		uint32_t SRAM_LIMIT_ADDR_L:16,
			     SRAM_LIMIT_ADDR_H:16;
		}BITS;
}PI2C_DMA_SRAM_RD_LIMIT_ADDR_Type;

typedef union
{
	uint32_t DATA;
	struct{
		uint32_t SCL_IN_DLY_SEL:2,
			     SDA_IN_DLY_SEL:2,
			     SCL_OUT_DLY_SEL:2,
			     SDA_OUT_DLY_SEL:2,
			     Reserved:24;
		}BITS;
}PI2C_IO_DLY_MUX_SEL_Type;

typedef union
{
	uint32_t DATA;
	struct{
		uint32_t SLV_START_ADDR:16,
			     SLV_LAST_ADDR:16;
		}BITS;
}PI2C_SLV_ADDR_BUF_Type;

typedef union
{
	uint32_t DATA;
	struct{
		uint32_t SLV_BUSY:1,
			     SLV_WR_Flag:1,
			     SLV_RD_Flag:1,
			     IDLE:1,
			     CH_BUSY:1,
			     SDA_Flag:1,
			     Reserved:26;
		}BITS;
}PI2C_PISTR_Type;

typedef union
{
	uint32_t DATA;
	struct{
		uint32_t DEV_MATCH:3,
			     Reserved:29;
		}BITS;
}PI2C_DMSTR_Type;


typedef struct
{
	PI2C_SLV_CONF_Type               SLV_CONF;               // 0x0000
	PI2C_IDLE_CHECK_TIME_Type        IDLE_CHK;               // 0x0004
	PI2C_SLV_ADDR_Type               SLV_ADDR;               // 0x0008
	PI2C_SLV_INT_MASK                SLV_INT_MASK;           // 0x000C
	PI2C_DMA_WR_ADDR_OFFSET_Type     DMA_WR_ADDR_OFF;        // 0x0010
	PI2C_DMA_RD_ADDR_OFFSET_Type     DMA_RD_ADDR_OFF;        // 0x0014
	PI2C_DMA_SRAM_WR_LIMIT_ADDR_Type DMA_SRAM_WR_LIMIT_ADDR; // 0x0018
	PI2C_DMA_SRAM_RD_LIMIT_ADDR_Type DMA_SRAM_RD_LIMIT_ADDR; // 0x001C
	PI2C_IO_DLY_MUX_SEL_Type         IO_DLY_MUX_SEL;         // 0x0020
	PI2C_SLV_ADDR_BUF_Type           SLV_ADDR_BUF;           // 0x0024
	PI2C_PISTR_Type                  PISTR;                  // 0x0028
	PI2C_DMSTR_Type                  DMSTR;                  // 0x002C
}PI2C_BLOCK_Type;

#endif

