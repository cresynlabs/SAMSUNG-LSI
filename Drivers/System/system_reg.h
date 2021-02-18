/*
******************************************************************************
* @file    system_reg.h
* @author  Power Device Team
* @version V1.0.0
* @date    2015.01.27
* @brief   Header for Flash Memory Control module
******************************************************************************
*/
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef _SYSTEM_REG_H_
#define _SYSTEM_REG_H_

typedef union
{
    uint32_t DATA;
    struct {
        uint32_t   TENMS:24,
                   SKEW:1,
                   NOREF:1,
                   Reserved:6;
  } BITS;
} STCALIB_Type;

typedef union
{
    uint32_t DATA;
    struct {
        uint32_t   IRQLATENCY:8,
                   Reserved:24;
  } BITS;
} IRQLATENCY_Type;

typedef union
{
    uint32_t DATA;
    struct {
        uint32_t   ECOREVNUM:28,
                   Reserved:4;
  } BITS;
} ECOREVNUM_Type;

typedef union
{
    uint32_t DATA;
    struct {
        uint32_t   sram0_mcs0:1,
                   sram0_mcs1:1,
                   sram1_mcs0:1,
                   sram1_mcs1:1,
                   Reserved:28;
  } BITS;
} SRAM_MCS_Type;

typedef union
{
    uint32_t DATA;
    struct {
        uint32_t   NIDEN:1,
                   DBGEN:1,
                   Reserved:30;
  } BITS;
} Debug_Authentication_Type;

typedef union
{
	uint32_t DATA;
	struct {
		uint32_t TESTMODE:1,
			     STOPH:1,
			     Reserved1:1,
			     LPM_STOP_EN:1,
			     Reserved2:28;
		} BITS;
} Flash_Configuration_Type;

typedef union
{
	uint32_t DATA;
	struct {
		uint32_t PI2C_TO_FLASH_AUTO_PGM:1,
			     READ_STAT_CMD_EN:1,
			     RESET_HALT_CMD_EN:1,
			     FLASH_ERASE_CMD_EN:1,
			     READ_CRC_CMD_EN:1,
			     FMEM_AUTO_WR_NOT_x4_ADD_CLR:1,
			     FMEM_AUTO_WR_NOT_x4_ADD_LATCH:1,
			     Reserved:25;
		} BITS;
} DMA_Flash_Type;

typedef union
{
    uint32_t DATA;
    struct {
        uint32_t   CLK_Enx_CORE:1,
				   CLK_Enx_Flash:1,
				   CLK_Enx_SRAM:1,
				   CLK_Enx_Boot:1,
				   CLK_Enx_SYSREG:1,
				   Reserved1:2,
				   CLK_Enx_RGB:1,
				   CLK_Enx_INTC:1,
				   CLK_Enx_PI2C:1,
				   CLK_Enx_MI2C:1,
				   CLK_Enx_UART:1,
				   CLK_Enx_TIMER:1,
				   Reserved2:2,
				   CLK_Enx_APB_Bridge:1,
				   CLK_Enx_PM:1,
				   CLK_Enx_SC:1,
				   CLK_Enx_WPT:1,
				   CLK_Enx_Filter:1,
				   CLK_Enx_PM_262KHz:1,
				   CLK_Enx_SC_262KHz:1,
				   CLK_Enx_RGB_262KHz:1,
				   CLK_Enx_CM_262KHz:1,
				   CLK_Enx_FG:1,
				   Reserved3:1,
				   CLK_Enx_PLC:1,
				   Reserved4:5;
  } BITS;
} Clock_Enable_Type;

typedef union
{
    uint32_t DATA;
    struct {
        uint32_t   CLK_Enx_CORE:1,
				   CLK_Enx_Flash:1,
				   CLK_Enx_SRAM:1,
				   CLK_Enx_Boot:1,
				   CLK_Enx_SYSREG:1,
				   Reserved1:2,
				   CLK_Enx_RGB:1,
				   CLK_Enx_INTC:1,
				   CLK_Enx_PI2C:1,
				   CLK_Enx_MI2C:1,
				   CLK_Enx_UART:1,
				   CLK_Enx_TIMER:1,
				   Reserved2:2,
				   CLK_Enx_APB_Bridge:1,
				   CLK_Enx_PM:1,
				   CLK_Enx_SC:1,
				   CLK_Enx_WPT:1,
				   CLK_Enx_Filter:1,
				   CLK_Enx_PM_262KHz:1,
				   CLK_Enx_SC_262KHz:1,
				   CLK_Enx_RGB_262KHz:1,
				   CLK_Enx_CM_262KHz:1,
				   CLK_Enx_FG:1,
				   Reserved3:1,
				   CLK_Enx_PLC:1,
				   Reserved4:5;
  } BITS;
} SLEEP_CLK_EN_SEL_Type;

typedef union
{
    uint32_t DATA;
    struct {
        uint32_t    CORE_RESET:1,
                    FLASH_CTRL_RESET:1,
                    SRAM_CTRL_RESET:1,
                    BOOT_CTRL_RESET:1,
                    SYSREG_RESET:1,
                    Reserved1:2,
                    RGB_RESET:1,
                    INTC_RESET:1,
                    PI2C_RESET:1,
                    MI2C_RESET:1,
                    UART_RESET:1,
                    TIMER_RESET:1,
                    Reserved2:2,
                    APB_BRIDGE_RESET:1,
                    PM_RESET:1,
                    SC_RESET:1,
                    WPT_RESET:1,
                    Reserved3:5,
                    FG_RESET:1,
                    Reserved4:1,
                    PLC_RESET:1,
                    Reserved5:3,
                    PI2C_DMA_RESET:1,
					Reserved6:1;
  } BITS;
} Soft_Rst_Type;

typedef union
{
	uint32_t DATA;
	struct{
		uint32_t POR_PDLY:16,
			     Reserved:16;
		}BITS;
} POR_PDLY_Type;

typedef union
{
	uint32_t DATA;
	struct {
		uint32_t POR_NDLY:16,
		         Reserved:16;
		}BITS;
} POR_NDLY_Type;

typedef union
{
    uint32_t DATA;
    struct {
        uint32_t   HRST_CORE_PDLY:16,
			   	   RESETREQ_PDLY:16;
  } BITS;
} HRST_CORE_PDLY_Type;

typedef union
{
    uint32_t DATA;
    struct {
        uint32_t   HRST_CORE_NDLY:16,
				   RESETREQ_NDLY:16;
  } BITS;
} HRST_CORE_NDLY_Type;


typedef union
{
	uint32_t DATA;
	struct {
		uint32_t FCON_CORE_PDLY:16,
			     Reserved:16;
		} BITS;
} FCON_CORE_PDLY_Type;

typedef union
{
	uint32_t DATA;
	struct {
		uint32_t FCON_CORE_NDLY:16,
			     Reserved:16;
		}BITS;
} FCON_CORE_NDLY_Type;

typedef union
{
	uint32_t DATA;
	struct {
		uint32_t DMA_MON:8,
			     Reserved:24;
		}BITS;
} DMA_MON_Type;

typedef union
{
    uint32_t DATA;
    struct {
        uint32_t   EXT_RST_TIME1:32;
  } BITS;
} EXT_RST_TIME1_Type;

typedef union
{
    uint32_t DATA;
    struct {
        uint32_t   EXT_RST_TIME2:32;
  } BITS;
} EXT_RST_TIME2_Type;

typedef union
{
    uint32_t DATA;
    struct {
        uint32_t   EXT_RST_TIME3:32;
  } BITS;
} EXT_RST_TIME3_Type;

typedef union
{
    uint32_t DATA;
    struct {
        uint32_t  OM_SELECT:1,
				  Reserved0:31;
  } BITS;
} OM_MAN_SEL_Type;

typedef union
{
    uint32_t DATA;
    struct {
        uint32_t   OM_RST_REQ_PERIOD:2,
				   Reserved:30;
  } BITS;
} OM_RST_REQ_PERIOD_Type;


typedef union
{
    uint32_t DATA;
    struct {
        uint32_t   OM_DBNC_PDLY:16,
				   Reserved:16;
  } BITS;
} OM_DBNC_PDLY_Type;

typedef union
{
    uint32_t DATA;
    struct {
        uint32_t   OM_DBNC_NDLY:16,
				   Reserved:16;
  } BITS;
} OM_DBNC_NDLY_Type;

typedef union
{
	uint32_t DATA;
	struct{
		uint32_t CLOCK_MUX_SEL:1,
			     Reserved1:15,
			     CLK_DIV_TRIM:10,
			     Reserved2:6;
		}BITS;
} CLOCK_MUX_SEL_Type;

typedef union
{
    uint32_t DATA;
    struct {
        uint32_t  RESET_GLOBAL:1,
				  RESET_SYSRESETREQ_CORE:1,
				  RESET_PMU_RESETREQ:1,
				  RESET_WDT:1,
				  RESET_EXT_RESETREQ3:1,
				  RESET_EXT_RESETREQ2:1,
				  RESET_OM_REQ:1,
				  RESET_SOFT_RESET_0:1,
				  Reserved:24;
  } BITS;
} RESET_REASON_latch_Type;

typedef union
{
    uint32_t DATA;
    struct {
        uint32_t   ADDR_REMAP_START:32;
  } BITS;
} ADDR_REMAP_START_Type;

typedef union
{
    uint32_t DATA;
    struct {
        uint32_t   ADDR_REMAP_END:32;
  } BITS;
} ADDR_REMAP_END_Type;

typedef union
{
    uint32_t DATA;
    struct {
        uint32_t   ADDR_REMAP_OFFSET:32;
  } BITS;
} ADDR_REMAP_OFFSET_Type;

typedef union
{
    uint32_t DATA;
    struct {
        uint32_t   ADDR_REMAP_EN:1,
                   Reserved:31;
  } BITS;
} ADDR_REMAP_EN_Type;

typedef union
{
    uint32_t DATA;
    struct {
        uint32_t   ADDR_REMAP_START2:32;
  } BITS;
} ADDR_REMAP_START2_Type;

typedef union
{
    uint32_t DATA;
    struct {
        uint32_t   ADDR_REMAP_END2:32;
  } BITS;
} ADDR_REMAP_END2_Type;

typedef union
{
    uint32_t DATA;
    struct {
        uint32_t   ADDR_REMAP_OFFSET2:32;
  } BITS;
} ADDR_REMAP_OFFSET2_Type;

typedef union
{
    uint32_t DATA;
    struct {
        uint32_t   ADDR_REMAP_EN2:1,
                   Reserved:31;
  } BITS;
} ADDR_REMAP_EN2_Type;


typedef union
{
	uint32_t DATA;
	struct {
		uint32_t IRQ_POLARITY_00:1,
			     IRQ_POLARITY_01:1,
			     IRQ_POLARITY_02:1,
			     IRQ_POLARITY_03:1,
			     IRQ_POLARITY_04:1,
			     IRQ_POLARITY_05:1,
			     IRQ_POLARITY_06:1,
			     IRQ_POLARITY_07:1,
			     IRQ_POLARITY_08:1,
			     IRQ_POLARITY_09:1,
			     IRQ_POLARITY_10:1,
			     IRQ_POLARITY_11:1,
			     IRQ_POLARITY_12:1,
			     IRQ_POLARITY_13:1,
			     IRQ_POLARITY_14:1,
			     IRQ_POLARITY_15:1,
			     IRQ_POLARITY_16:1,
			     IRQ_POLARITY_17:1,
			     IRQ_POLARITY_18:1,
			     IRQ_POLARITY_19:1,
			     IRQ_POLARITY_20:1,
			     IRQ_POLARITY_21:1,
			     IRQ_POLARITY_22:1,
			     IRQ_POLARITY_23:1,
			     IRQ_POLARITY_24:1,
			     IRQ_POLARITY_25:1,
			     IRQ_POLARITY_26:1,
			     IRQ_POLARITY_27:1,
			     IRQ_POLARITY_28:1,
			     IRQ_POLARITY_29:1,
			     IRQ_POLARITY_30:1,
			     IRQ_POLARITY_31:1;
		}BITS;
} IRQ_POLARITY_Type;


typedef union
{
	uint32_t DATA;
	struct {
		uint32_t IRQ_DET_SEL_00:2,
			     IRQ_DET_SEL_01:2,
			     IRQ_DET_SEL_02:2,
			     IRQ_DET_SEL_03:2,
			     IRQ_DET_SEL_04:2,
			     IRQ_DET_SEL_05:2,
			     IRQ_DET_SEL_06:2,
			     IRQ_DET_SEL_07:2,
			     IRQ_DET_SEL_08:2,
			     IRQ_DET_SEL_09:2,
			     IRQ_DET_SEL_10:2,
			     IRQ_DET_SEL_11:2,
			     IRQ_DET_SEL_12:2,
			     IRQ_DET_SEL_13:2,
			     IRQ_DET_SEL_14:2,
			     IRQ_DET_SEL_15:2;
		} BITS;
} IRQ_DET_SEL_LOW_Type;

typedef union
{
	uint32_t DATA;
	struct {
		uint32_t IRQ_DET_SEL_00:2,
			     IRQ_DET_SEL_01:2,
			     IRQ_DET_SEL_02:2,
			     IRQ_DET_SEL_03:2,
			     IRQ_DET_SEL_04:2,
			     IRQ_DET_SEL_05:2,
			     IRQ_DET_SEL_06:2,
			     IRQ_DET_SEL_07:2,
			     IRQ_DET_SEL_08:2,
			     IRQ_DET_SEL_09:2,
			     IRQ_DET_SEL_10:2,
			     IRQ_DET_SEL_11:2,
			     IRQ_DET_SEL_12:2,
			     IRQ_DET_SEL_13:2,
			     IRQ_DET_SEL_14:2,
			     IRQ_DET_SEL_15:2;
		} BITS;
} IRQ_DET_SEL_HIGH_Type;

typedef union
{
	uint32_t DATA;
	struct {
		uint32_t EXT_WAKEUP_MASK_EN:1,
			     GPIO_IRQ2_MASK_EN:1,
			     GPIO_IRQ1_MASK_EN:1,
			     Reserved1:1,
			     WI2C_MASK_EN:1,
			     INT_POLARITY_SEL:1,
			     PATH_SEL:2,
			     EXT_WATER_MASK_EN:1,
			     Reserved2:1,
			     I2C_LVL_MASK_EN:1,
			     EXT_WATER_DET_SEL:2,
			     EXT_WAKEUP_DET_SEL:2,
			     GPIO_IRQ2_DET_SEL:2,
			     GPIO_IRQ1_DET_SEL:2,
			     Reserved3:2,
			     I2C_DET_SEL:2,
			     Reserved4:2,
			     I2C_LVL_DET_SEL:2,
			     Low_PWR_EN_SRC_SEL:1,
			     LPM_SLEEP_SOURCE_SEL:1,
			     LPM_WAKEUP_SOURCE_MCU_ENB:1,
			     LPM_SLEEP_FLASH_AUTO_STOP:1,
			     Reserved5:1;
		} BITS;
} SYS_WAKE_UP_E0_Type;

typedef union
{
	uint32_t DATA;
	struct{
		uint32_t SRC_EXT_WATER_FLAG:1,
			     SRC_EXT_WAKEUP_FLAG:1,
			     SRC_GPIO2_FLAG:1,
			     SRC_GPIO1_FLAG:1,
			     SRC_MI2C_FLAG:1,
			     SRC_PI2C_FLAG:1,
			     SRC_MI2C_LVL_FLAG:1,
			     SRC_PI2C_LVL_FLAG:1,
			     Reserved:24;
		}BITS;
} SYS_WAKE_UP_E4_Type;


typedef union
{
	uint32_t DATA;
	struct{
		uint32_t ASSERTED:1,
			     Reserved:31;
		}BITS;
} SYS_WAKE_UP_E8_Type;

typedef union
{
	uint32_t DATA;
	struct {
		uint32_t A2D_WPT_NRST_INT:1,
			     A2D_WPT_nEN:1,
			     D2A_WPT_EN_UVLO:1,
			     Reserved1:1,
			     REG_SEL_EN_WPT_UVLO_MCU:1,
			     REG_EN_WPT_UVLO_MCU:1,
			     Reserved2:26;
		} BITS;
} WPT_EN_Type;

typedef union
{
	uint32_t DATA;
	struct {
		uint32_t NMI_WAKEUP_DLY:32;
		} BITS;
} NMI_WAKEUP_DLY_Type;

typedef union
{
	uint32_t DATA;
	struct {
		uint32_t RXEV_WAKEUP_DLY:32;
		} BITS;
} RXEV_WAKEUP_DLY_Type;

typedef union
{
	uint32_t DATA;
	struct {
		uint32_t Analog_LPM_MODE:32;
		} BITS;
} ANALOG_LPM_MODE_Type;

typedef union
{
	uint32_t DATA;
	struct {
		uint32_t REG_EN_DET_POGO_R:1,
			     REG_DET_POGO_RESET_R:1,
			     REG_EN_DET_POGO_L:1,
			     REG_DET_POGO_RESET_L:1,
			     DET_POGO_R_Status:2,
			     DET_POGO_L_Status:2,
			     DET_POGO_REG_R_Status:1,
			     DET_POGO_REG_L_Status:1,
			     Reserved:21,
			     A2D_CM_HOLL_INT_DB:1;
		} BITS;
}DET_POGO_Type;

typedef union
{
	uint32_t DATA;
	struct {
		uint32_t DEFAULT_EN:1,
			     rpt_match_CLR:1,
			     win_time_CLR:1,
			     rpt_num_CLR:1,
			     win_toggle_value:1,
			     win_toggle_sel:1,
			     Reserved1:1,
			     win_toggle_CLR:1,
			     OSC_22M_EN_sel:1,
			     OSC_FREQ_SEL:1,
			     LPM_EN_manual_sel:1,
			     LPM_EN_manuaa_val:1,
			     Reserved2:20;
		} BITS;
} WATER_CONTROL7_Type;

typedef union
{
    uint32_t DATA;
    struct {
        uint32_t  I2C_AHB_WR_ERR_IRQ_MASK:1,
				  I2C_AHB_RD_ERR_IRQ_MASK:1,
				  Reserved:30;
  } BITS;
} AHB_ERR_IRQ_MASK_Type;


typedef union
{
    uint32_t DATA;
    struct {
        uint32_t  I2C_AHB_WR_ERROR:1,
				  I2C_AHB_RD_ERROR:1,
				  Reserved:30;
  } BITS;
} AHB_ERR_STATUS_Type;

typedef union
{
	uint32_t DATA;
	struct {
		uint32_t MON_SEL1:4,
			     MON_SEL2:4,
			     MON1_reverse_EN:1,
			     MON2_reverse_EN:1,
			     Reserved:22;
		} BITS;
} Monitoring_MUX_Type;


typedef struct
{
    Reserved_Type               RSVD_00;                //  0x0000
    STCALIB_Type                STCALIB;                //  0x0004
    IRQLATENCY_Type             IRQLATENCY;             //  0x0008
    ECOREVNUM_Type              ECOREVNUM;              //  0x000C
    SRAM_MCS_Type               SRAM_MCS;               //  0x0010
    Debug_Authentication_Type   Debug_Authentication;   //  0x0014
    Flash_Configuration_Type    Flash_Configuration;    //  0x0018
    DMA_Flash_Type              DMA_Flash;              //  0x001C
	Clock_Enable_Type			Clock_Enable;			//	0x0020
	SLEEP_CLK_EN_SEL_Type       Sleep_CLK_En_Sel;       //  0x0024
    Reserved_Type               RVSD_28;                //  0x0028
    Reserved_Type               RVSD_2C;                //  0x002C
	Soft_Rst_Type				Soft_Rst;				//	0x0030
    POR_PDLY_Type               POR_PDLY;               //  0x0034
    POR_NDLY_Type               POR_NDLY;               //  0x0038
    HRST_CORE_PDLY_Type         HRST_CORE_PDLY;         //  0x003C
    HRST_CORE_NDLY_Type         HRST_CORE_NDLY;         //  0x0040
	FCON_CORE_PDLY_Type         FCON_CORE_PDLY;         //  0x0044
	FCON_CORE_NDLY_Type         FCON_CORE_NDLY;         //  0x0048
	DMA_MON_Type                DMA_Mon;                //  0x004C
    EXT_RST_TIME1_Type          EXT_RST_TIME1;          //  0x0050
    EXT_RST_TIME2_Type          EXT_RST_TIME2;          //  0x0054
    EXT_RST_TIME3_Type          EXT_RST_TIME3;          //  0x0058
	OM_MAN_SEL_Type				OM_MAN_SEL;				//  0x005C
	OM_RST_REQ_PERIOD_Type		OM_RST_REQ_PERIOD;		//  0x0060
	OM_DBNC_PDLY_Type			OM_DBNC_PDLY;			//  0x0064
	OM_DBNC_NDLY_Type			OM_DBNC_NDLY;			//  0x0068
    Reserved_Type               RSVD_6C;                //  0x006C
    CLOCK_MUX_SEL_Type          CLK_MUX_SEL;            //  0x0070
    Reserved_Type               RSVD_74;                //  0x0074
	RESET_REASON_latch_Type		RESET_REASON_latch;		//  0x0078
    Reserved_Type               RSVD_7C;                //  0x007C
    ADDR_REMAP_START_Type       ADDR_REMAP_START;       //  0x0080
    ADDR_REMAP_END_Type         ADDR_REMAP_END;         //  0x0084
    ADDR_REMAP_OFFSET_Type      ADDR_REMAP_OFFSET;      //  0x0088
    ADDR_REMAP_EN_Type          ADDR_REMAP_EN;          //  0x008C
    ADDR_REMAP_START2_Type      ADDR_REMAP_START2;      //  0x0090
    ADDR_REMAP_END2_Type        ADDR_REMAP_END2;        //  0x0094
    ADDR_REMAP_OFFSET2_Type     ADDR_REMAP_OFFSET2;     //  0x0098
    ADDR_REMAP_EN2_Type         ADDR_REMAP_EN2;         //  0x009C
    Reserved_Type               RSVD_A0;                //  0x00A0
    Reserved_Type               RSVD_A4;                //  0x00A4
    Reserved_Type               RSVD_A8;                //  0x00A8
    Reserved_Type               RSVD_AC;                //  0x00AC
    Reserved_Type               RSVD_B0;                //  0x00B0
    Reserved_Type               RSVD_B4;                //  0x00B4
    Reserved_Type               RSVD_B8;                //  0x00B8
    Reserved_Type               RSVD_BC;                //  0x00BC
    Reserved_Type               RSVD_C0;                //  0x00C0
    Reserved_Type               RSVD_C4;                //  0x00C4
    Reserved_Type               RSVD_C8;                //  0x00C8
    Reserved_Type               RSVD_CC;                //  0x00CC
    IRQ_POLARITY_Type           IRQ_POLARITY;           //  0x00D0
    IRQ_DET_SEL_LOW_Type        IRQ_DET_SEL_LOW;        //  0x00D4
    IRQ_DET_SEL_HIGH_Type       IRQ_DET_SEL_HIGH;       //  0x00D8
    Reserved_Type               RSVD_DC;                //  0x00DC
    SYS_WAKE_UP_E0_Type         SYS_WAKEUP_E0;          //  0x00E0
    SYS_WAKE_UP_E4_Type         SYS_WAKEUP_E4;          //  0x00E4
    SYS_WAKE_UP_E8_Type         SYS_WAKEUP_E8;          //  0x00E8
    WPT_EN_Type                 WPT_EN;                 //  0x00EC
	NMI_WAKEUP_DLY_Type         NMI_WAKEUP_DLY;         //  0x00F0
	RXEV_WAKEUP_DLY_Type        RXEV_WAKEUP_DLY;        //  0x00F4
	ANALOG_LPM_MODE_Type        ANALOG_LPM_MODE;        //  0x00F8
	DET_POGO_Type               DET_POGO;               //  0x00FC
    Reserved_Type               RSVD_100;               //  0x0100
    Reserved_Type               RSVD_104;               //  0x0104
    Reserved_Type               RSVD_108;               //  0x0108
    Reserved_Type               RSVD_10C;               //  0x010C
    Reserved_Type               RSVD_110;               //  0x0110
    Reserved_Type               RSVD_114;               //  0x0114
    WATER_CONTROL7_Type         Water_Ctrl;             //  0x0118
    Reserved_Type               RSVD_11C;               //  0x011C
    Reserved_Type               RSVD_120;               //  0x0120
    Reserved_Type               RSVD_124;               //  0x0124
    Reserved_Type               RSVD_128;               //  0x0128
    Reserved_Type               RSVD_12C;               //  0x012C
    Reserved_Type               RSVD_130;               //  0x0130
    Reserved_Type               RSVD_134;               //  0x0134
    Reserved_Type               RSVD_138;               //  0x0138
    Reserved_Type               RSVD_13C;               //  0x013C
    Reserved_Type               RSVD_140;               //  0x0140
    Reserved_Type               RSVD_144;               //  0x0144
    Reserved_Type               RSVD_148;               //  0x0148
    Reserved_Type               RSVD_14C;               //  0x014C
    Reserved_Type               RSVD_150;               //  0x0150
    Reserved_Type               RSVD_154;               //  0x0154
    Reserved_Type               RSVD_158;               //  0x0158
    Reserved_Type               RSVD_15C;               //  0x015C
    Reserved_Type               RSVD_160;               //  0x0160
    Reserved_Type               RSVD_164;               //  0x0164
    Reserved_Type               RSVD_168;               //  0x0168
    Reserved_Type               RSVD_16C;               //  0x016C
    Reserved_Type               RSVD_170;               //  0x0170
    Reserved_Type               RSVD_174;               //  0x0174
    Reserved_Type               RSVD_178;               //  0x0178
    Reserved_Type               RSVD_17C;               //  0x017C
    Reserved_Type               RSVD_180;               //  0x0180
    Reserved_Type               RSVD_184;               //  0x0184
    Reserved_Type               RSVD_188;               //  0x0188
    Reserved_Type               RSVD_18C;               //  0x018C
    Reserved_Type               RSVD_190;               //  0x0190
    Reserved_Type               RSVD_194;               //  0x0194
    Reserved_Type               RSVD_198;               //  0x0198
    Reserved_Type               RSVD_19C;               //  0x019C
    Reserved_Type               RSVD_1A0;               //  0x01A0
    Reserved_Type               RSVD_1A4;               //  0x01A4
    Reserved_Type               RSVD_1A8;               //  0x01A8
    Reserved_Type               RSVD_1AC;               //  0x01AC
    Reserved_Type               RSVD_1B0;               //  0x01B0
    Reserved_Type               RSVD_1B4;               //  0x01B4
    Reserved_Type               RSVD_1B8;               //  0x01B8
    Reserved_Type               RSVD_1BC;               //  0x01BC
    Reserved_Type               RSVD_1C0;               //  0x01C0
    Reserved_Type               RSVD_1C4;               //  0x01C4
    Reserved_Type               RSVD_1C8;               //  0x01C8
    Reserved_Type               RSVD_1CC;               //  0x01CC
    Reserved_Type               RSVD_1D0;               //  0x01D0
	AHB_ERR_IRQ_MASK_Type		AHB_ERR_IRQ_MASK;		//  0x01D4
    AHB_ERR_STATUS_Type			AHB_ERR_STATUS;			//  0x01D8
    Reserved_Type               RSVD_1DC;               //  0x01DC
    Reserved_Type               RSVD_1E0;               //  0x01E0
    Reserved_Type               RSVD_1E4;               //  0x01E4
    Reserved_Type               RSVD_1E8;               //  0x01E8
    Reserved_Type               RSVD_1EC;               //  0x01EC
    Monitoring_MUX_Type         MON_MUX;                //  0x01F0
} SYSREG_BLOCK_Type;

#define	bTIMER					b12
#define	bUART					b11
#define	bI2C2					b10
#define	bI2C1					b9
#define	bWPT					b7
#define	bBOOTCON				b3
#define	bSRAMCON				b2
#define	bFLASHCON				b1
#define	bCORE					b0

#endif

