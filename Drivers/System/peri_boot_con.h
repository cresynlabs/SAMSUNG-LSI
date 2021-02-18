/*
* @file    peri_boot_con.h
* @author  Power Device Team
* @version V1.0.0
* @date    2019.01.15
* @brief   Header for Boot Controller module
******************************************************************************
*/
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef _PERI_BOOT_CON_H_
#define _PERI_BOOT_CON_H_

typedef struct
{
	uint32_t Reserved;
} BOOTCON_RESERVED_TYPE;

typedef union
{
    uint32_t DATA;
    struct {
        uint32_t   CORE_MAN_RESET_EN:1,
                   CORE_MAN_RESET:1,
                   CORE_RESET_STATE:1,
                   CORE_Reset_related_FLASHCON:1,
                   Reserved3:28;
  } BITS;
} CORE_RESET_CON_Type;

typedef union
{
	uint32_t DATA;
	struct{
		uint32_t FLASH_UPDATE_PATTERN:6,
			     Reserved1:20,
			     EXT_RST_SEL:2,
			     PI2C_RST_SEL:2,
			     MI2C_RST_SEL:2;
		} BITS;
} EXT_RST_SEL_Type;

typedef union
{
	uint32_t DATA;
	struct{
		uint32_t FG_RDY_MAN:1,
			     Reserved:31;
		} BITS;
} LDT_DUMP_DATA01_Type;

typedef union
{
	uint32_t DATA;
	struct{
		uint32_t GP1_T_D1_PEN:1,
			     GP2_T_D2_PEN:1,
			     GP3_T_D3_PEN:1,
			     GP4_T_D4_PEN:1,
			     GP5_T_D5_PEN:1,
			     GP6_T_D6_PEN:1,
			     GP7_UART_TX_PEN:1,
			     GP8_UART_RX_PEN:1,
			     Reserved:24;
		} BITS;
} GPIO_PEN_Type;

typedef union
{
	uint32_t DATA;
	struct{
		uint32_t  GPIO_OUTx_0:1,
                  GPIO_OUTx_1:1,
                  GPIO_OUTx_2:1,
                  GPIO_OUTx_3:1,
                  GPIO_OUTx_4:1,
                  GPIO_OUTx_5:1,
                  GPIO_OUTx_6:1,
                  GPIO_OUTx_7:1,
                  GPIO_OUTx_8:1,
                  GPIO_OUTx_9:1,
                  GPIO_OUTx_10:1,
                  GPIO_OUTx_11:1,
                  GPIO_OUTx_12:1,
                  GPIO_OUTx_13:1,
                  GPIO_OUTx_14:1,
                  GPIO_OUTx_15:1,
                  GPIO_OUTx_16:1,
                  GPIO_OUTx_17:1,
                  GPIO_OUTx_18:1,
                  GPIO_OUTx_19:1,
                  GPIO_OUTx_20:1,
                  GPIO_OUTx_21:1,
                  GPIO_OUTx_22:1,
                  GPIO_OUTx_23:1,
                  GPIO_OUTx_24:1,
                  GPIO_OUTx_25:1,
                  GPIO_OUTx_26:1,
                  GPIO_OUTx_27:1,
                  GPIO_OUTx_28:1,
                  GPIO_OUTx_29:1,
                  GPIO_OUTx_30:1,
                  GPIO_OUTx_31:1;
		} BITS;
} GPIO_OUT_Type;

typedef union
{
	uint32_t DATA;
	struct{
		uint32_t  GPIO_INx_0:1,
                  GPIO_INx_1:1,
                  GPIO_INx_2:1,
                  GPIO_INx_3:1,
                  GPIO_INx_4:1,
                  GPIO_INx_5:1,
                  GPIO_INx_6:1,
                  GPIO_INx_7:1,
                  GPIO_INx_8:1,
                  GPIO_INx_9:1,
                  GPIO_INx_10:1,
                  GPIO_INx_11:1,
                  GPIO_INx_12:1,
                  GPIO_INx_13:1,
                  GPIO_INx_14:1,
                  GPIO_INx_15:1,
                  GPIO_INx_16:1,
                  GPIO_INx_17:1,
                  GPIO_INx_18:1,
                  GPIO_INx_19:1,
                  GPIO_INx_20:1,
                  GPIO_INx_21:1,
                  GPIO_INx_22:1,
                  GPIO_INx_23:1,
                  GPIO_INx_24:1,
                  GPIO_INx_25:1,
                  GPIO_INx_26:1,
                  GPIO_INx_27:1,
                  GPIO_INx_28:1,
                  GPIO_INx_29:1,
                  GPIO_INx_30:1,
                  GPIO_INx_31:1;
		} BITS;
} GPIO_IN_Type;


typedef union
{
	uint32_t DATA;
	struct{
		uint32_t SCAN_TEST:2,
			     BIST_TEST_MODE:1,
			     ADC_SCAN_TEST_MODE:1,
			     SRC_SEL_IN_PI2C:2,
			     SRC_SEL_IN_MI2C:2,
			     SRC_SEL_IN_SWD:2,
			     SRC_SEL_IN_UART:2,
//			     Reserved1:2,
			     SRC_SEL_OUT_UART:2,
			     SRC_SEL_OUT_PI2C:2,
			     SRC_SEL_OUT_MI2C:2,
			     SRC_SEL_OUT_SWD:2,
			     SRC_SEL_OUT_PDET_B:2,
			     SRC_SEL_OUT_VOUT_GD:2,
			     SRC_SEL_OUT_VREC_GD:2,
			     SRC_SEL_OUT_PING_nEN:2,
			     Reserved2:4;
		} BITS;
} GPIO_SOURCE_SEL_Type;

typedef union
{
	uint32_t DATA;
	struct{
		uint32_t GPIO_OUT_SEL_1:2,
			     GPIO_OUT_SEL_2:2,
			     GPIO_OUT_SEL_3:2,
			     GPIO_OUT_SEL_4:2,
			     GPIO_OUT_SEL_5:2,
			     GPIO_OUT_SEL_6:2,
			     GPIO_OUT_SEL_7:2,
			     GPIO_OUT_SEL_8:2,
			     GPIO_OUT_SEL_9:2,
			     GPIO_OUT_SEL_10:2,
			     GPIO_OUT_SEL_11:2,
			     GPIO_OUT_SEL_12:2,
			     GPIO_OUT_SEL_13:2,
			     GPIO_OUT_SEL_14:2,
			     Reserved:4;
		} BITS;
} GPIO_OUT_MUX1_Type;

typedef union
{
	uint32_t DATA;
	struct{
		uint32_t GPIO_OUT_SEL15:2,
			     GPIO_OUT_SEL16:2,
			     Reserved:28;
		} BITS;
} GPIO_OUT_MUX2_Type;

typedef union
{
	uint32_t DATA;
	struct{
		uint32_t GPIO_IN_SEL0:5,
			     Reserved1:3,
			     GPIO_IN_SEL1:5,
			     Reserved2:3,
			     GPIO_IN0_REVERSE_EN:1,
			     GPIO_IN1_REVERSE_EN:1,
			     Reserved3:14;
		} BITS;
} GPIO_IN_MUX_Type;

typedef union
{
	uint32_t DATA;
	struct{
		uint32_t Reserved1:16,
			     EN_SHUT_DOWN_MODE:1,
			     Reserved2:7,
			     EN_LBAT_AUTO_SHUT_DOWN:1,
			     Time_SHUT_DOWN_DB:2,
			     Reserved3:5;
		} BITS;
} SHUT_DOWN_MODE_Type;

typedef union
{
	uint32_t DATA;
	struct{
		uint32_t CCD_EN:1,
			     Reserved1:6,
			     CCD_EN2:1,
			     CCD_STATUS:1,
			     Reserved2:7,
			     CCD_JDG_CNT:6,
			     Reserved3:2,
			     CCD_JDG:8;
		} BITS;
} CCD_Type;

typedef union
{
	uint32_t DATA;
	struct{
		uint32_t ATE:32;
		} BITS;
} ATE_Type;

typedef union
{
	uint32_t DATA;
	struct{
		uint32_t D2A_CM_LDO_1P8_0:8,
			     D2A_CM_LDO_1P8_1:8,
			     D2A_CM_MCU_BUF_0:8,
		    	 D2A_CM_MCU_BUF_1:8;
		} BITS;
} COMMON_1P8_Type;

typedef union
{
	uint32_t DATA;
	struct {
		uint32_t D2A_REG_COMMON_CONF1:32;
		} BITS;
} ANA_COMMON1_Type;

typedef union
{
	uint32_t DATA;
	struct{
		uint32_t D2A_REG_COMMON_CONF2:8,
			     SET_MRSTBTMR:3,
			     EN_MRST:1,
			     Reserved1:3,
			     D2A_HW_RESET:1,
			     D2A_REG_COMMON_OPT1:8,
			     D2A_REG_COMMON_OPT2:8;
		} BITS;
} ANA_COMMON2_Type;

typedef union
{
	uint32_t DATA;
	struct{
		uint32_t D2A_REG_COMMON_OPT3:8,
			     D2A_REG_COMMON_OPT4:8,
			     D2A_REG_COMMON_OPT5:8,
			     D2A_REG_COMMON_OPT6:8;
		} BITS;
} ANA_COMMON3_Type;

typedef union
{
	uint32_t DATA;
	struct{
		uint32_t D2A_REG_COMMON_OPT7:8,
			     D2A_REG_COMMON_OPT8:8,
			     D2A_REG_COMMON_OPT9:8,
			     Reserved:8;
		} BITS;
} ANA_COMMON4_Type;

typedef union
{
	uint32_t DATA;
	struct{
		uint32_t OSC_TRIM:8,
			     Reserved:24;
		} BITS;
} CM_CTRL7_Type;

typedef union
{
	uint32_t DATA;
	struct{
		uint32_t PMIC_ID:8,
			     ES_NO_REV_NO:8,
			     D2A_ATEST_CTRL:8,
			     D2A_REG_COMMON_RSVD:8;
		} BITS;
} ANA_COMMON5_Type;


typedef struct
{
    CORE_RESET_CON_Type     CORE_RESET_CON;       // 0x0000
    EXT_RST_SEL_Type        EXT_RST_SEL;          // 0x0004
    LDT_DUMP_DATA01_Type    LDT_DUMP_DATA01;      // 0x0008
    BOOTCON_RESERVED_TYPE   Reserved_0C;          // 0x000C
    BOOTCON_RESERVED_TYPE   Reserved_10;          // 0x0010
    BOOTCON_RESERVED_TYPE   Reserved_14;          // 0x0014
    BOOTCON_RESERVED_TYPE   Reserved_18;          // 0x0018
    BOOTCON_RESERVED_TYPE   Reserved_1C;          // 0x001C
    GPIO_PEN_Type           GPIO_PEN;             // 0x0020
    GPIO_OUT_Type           GPIO_OUT;             // 0x0024
    GPIO_IN_Type            GPIO_IN;              // 0x0028
    GPIO_SOURCE_SEL_Type    GPIO_SRC_SEL;         // 0x002C
    GPIO_OUT_MUX1_Type      GPIO_OUT_MUX1;        // 0x0030
    GPIO_OUT_MUX2_Type      GPIO_OUT_MUX2;        // 0x0034
    GPIO_IN_MUX_Type        GPIO_IN_MUX;          // 0x0038
    BOOTCON_RESERVED_TYPE   Reserved_3C;          // 0x003C
    BOOTCON_RESERVED_TYPE   Reserved_40;          // 0x0040
    BOOTCON_RESERVED_TYPE   Reserved_44;          // 0x0044
    BOOTCON_RESERVED_TYPE   Reserved_48;          // 0x0048
    BOOTCON_RESERVED_TYPE   Reserved_4C;          // 0x004C
    BOOTCON_RESERVED_TYPE   Reserved_50;          // 0x0050
    BOOTCON_RESERVED_TYPE   Reserved_54;          // 0x0054
    BOOTCON_RESERVED_TYPE   Reserved_58;          // 0x0058
    BOOTCON_RESERVED_TYPE   Reserved_5C;          // 0x005C
    BOOTCON_RESERVED_TYPE   Reserved_60;          // 0x0060
    BOOTCON_RESERVED_TYPE   Reserved_64;          // 0x0064
    BOOTCON_RESERVED_TYPE   Reserved_68;          // 0x0068
    BOOTCON_RESERVED_TYPE   Reserved_6C;          // 0x006C
    BOOTCON_RESERVED_TYPE   Reserved_70;          // 0x0070
    BOOTCON_RESERVED_TYPE   Reserved_74;          // 0x0074
    BOOTCON_RESERVED_TYPE   Reserved_78;          // 0x0078
    BOOTCON_RESERVED_TYPE   Reserved_7C;          // 0x007C
    BOOTCON_RESERVED_TYPE   Reserved_80;          // 0x0080
    BOOTCON_RESERVED_TYPE   Reserved_84;          // 0x0084
    BOOTCON_RESERVED_TYPE   Reserved_88;          // 0x0088
    BOOTCON_RESERVED_TYPE   Reserved_8C;          // 0x008C
    BOOTCON_RESERVED_TYPE   Reserved_90;          // 0x0090
    BOOTCON_RESERVED_TYPE   Reserved_94;          // 0x0094
    BOOTCON_RESERVED_TYPE   Reserved_98;          // 0x0098
    BOOTCON_RESERVED_TYPE   Reserved_9C;          // 0x009C
    BOOTCON_RESERVED_TYPE   Reserved_A0;          // 0x00A0
    BOOTCON_RESERVED_TYPE   Reserved_A4;          // 0x00A4
    BOOTCON_RESERVED_TYPE   Reserved_A8;          // 0x00A8
    BOOTCON_RESERVED_TYPE   Reserved_AC;          // 0x00AC
    BOOTCON_RESERVED_TYPE   Reserved_B0;          // 0x00B0
    BOOTCON_RESERVED_TYPE   Reserved_B4;          // 0x00B4
    BOOTCON_RESERVED_TYPE   Reserved_B8;          // 0x00B8
    BOOTCON_RESERVED_TYPE   Reserved_BC;          // 0x00BC
    BOOTCON_RESERVED_TYPE   Reserved_C0;          // 0x00C0
    BOOTCON_RESERVED_TYPE   Reserved_C4;          // 0x00C4
    SHUT_DOWN_MODE_Type     SHUTDN_MODE;          // 0x00C8
    CCD_Type                CCD;                  // 0x00CC
    ATE_Type                ATE;                  // 0x00D0
    COMMON_1P8_Type         COMM_1P8;             // 0x00D4
    BOOTCON_RESERVED_TYPE   Reserved_D8;          // 0x00D8
    BOOTCON_RESERVED_TYPE   Reserved_DC;          // 0x00DC
    ANA_COMMON1_Type        ANA_COMM1;            // 0x00E0
    ANA_COMMON2_Type        ANA_COMM2;            // 0x00E4
    ANA_COMMON3_Type        ANA_COMM3;            // 0x00E8
    ANA_COMMON4_Type        ANA_COMM4;            // 0x00EC
    CM_CTRL7_Type           CM_CTRL7;             // 0x00F0
    ANA_COMMON5_Type        ANA_COMM5;            // 0x00F4
} BOOTCON_BLOCK_Type;

#endif

