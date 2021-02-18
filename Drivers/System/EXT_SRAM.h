/*
******************************************************************************
* @file    ext_sram.h
* @author  Power Device Team
* @version V1.0.0
* @date    2016.03.28
* @brief   Header for EXT SRAM map
******************************************************************************
*/
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __EXT_SRAM_H
#define __EXT_SRAM_H

/*typedef union
{
    uint32_t DATA;
    struct {
        uint32_t   Reserved:32;
  } BITS;
} Reserved_Type;
*/

typedef union
{
    uint32_t DATA;
    struct {
        uint32_t   Reserved:32;
  } BITS;
} EXT_SRAM_Reserved_Type;


typedef union
{
    uint32_t DATA;
    struct {
        uint32_t HW_VERSION_Reserved:32;
    } BITS;
} HW_VERSION_Type;

typedef union
{
    uint32_t DATA;
    struct {
        uint32_t SW_VERSION_Reserved:32;
    } BITS;
} SW_VERSION_Type;

typedef union
{
    uint32_t DATA;
    struct {
        uint32_t    CMD_MODE_SEL:8,
                    CMD_HOST:8,
                    CMD_WR_DATA1:8,
                    CMD_WR_DATA2:8;
    } BITS;
} I2C_SLV_CMD_Type;

typedef union
{
    uint32_t DATA;
    struct {
        uint32_t    RSP_WORD1:16,
                    RSP_WORD2:16;
    } WORDS;
    struct {
        uint32_t    RSP_BYTE1:8,
                    RSP_BYTE2:8,
                    RSP_BYTE3:8,
                    RSP_BYTE4:8;
    } BYTES;
} I2C_SLV_RSP_Type;
#if 0
typedef union
{
    uint32_t DATA;
    struct {
        uint32_t    PD_State:8,
                    RSP_BYTE2:8,
                    PD_Next_State:8,
                    RSP_BYTE4:8;
    } BITS;
} FUNC_STATE_Type;

typedef union
{
    uint32_t DATA;
    struct {
        uint32_t    Flash_State:8,
                    Reserved:24;
    } BITS;
} FLASH_STATE_Type;


typedef union
{
    uint32_t DATA;
    uint8_t  BYTES[4];
    struct {
        uint32_t    SOP2p_Debug:1,
                    SOPp_Debug:1,
                    SOP2p:1,
                    SOPp:1,
                    SOP:1,
                    RSVD_1:27;
  } BITS;
} SYNC_STATUS_Type;

typedef union
{
    uint32_t DATA;
    uint8_t  BYTES[4];
    struct {
        uint32_t    FR_Swap:1,
                    Get_Source_Status:1,
                    Get_Source_Extended:1,
                    Not_Supported:1,
                    Soft_Reset:1,
                    Wait:1,
                    VCONN_Swap:1,
                    PR_Swap:1,
                    DR_Swap:1,
                    Get_Sink_Cap:1,
                    Get_Source_Cap:1,
                    PS_RDY:1,
                    Ping:1,
                    Reject:1,
                    Accept:1,
                    GotoMin:1,
                    GoodCRC:1,
                    RSVD_1:15;
  } BITS;
} CTRL_MSG_STATUS_Type;

typedef union
{
    uint32_t DATA;
    uint8_t  BYTES[4];
    struct {
        uint32_t    Attention:1,
                    Exit_Mode:1,
                    Enter_Mode:1,
                    Discover_Modes:1,
                    Discover_SVIDs:1,
                    Discover_Identity:1,
                    Source_Alert:1,
                    Battery_Status:1,
                    Vendor_Defined:1,
                    BIST_TEST_Data:1,
                    BIST_Carrier_Mode2:1,
                    Request:1,
                    Sink_Capability:1,
                    Source_Capability:1,
                    RSVD_1:18;
  } BITS;
} DATA_MSG_STATUS_Type;

typedef union
{
    uint32_t DATA;
    uint8_t  BYTES[4];
    struct {
        uint32_t    FW_UPDATE_Response:1,
                    FW_UPDATA_Request:1,
                    Security_Response:1,
                    Security_Request:1,
                    Manufacturer_Info:1,
                    Battery_Capabilities:1,
                    Get_Battery_Status:1,
                    Get_Battery_Cap:1,
                    Source_Status:1,
                    Source_Cap_Extended:1,
                    RSVD_1:21;
  } BITS;
} EXTENDED_MSG_STATUS_Type;


typedef union
{
    uint32_t DATA;
    uint8_t  BYTES[4];
    struct {
        uint32_t    Ctrl_Flag_Reserved_b0:1,        // b0
                    Ctrl_Flag_GoodCRC:1,            // b1
                    Ctrl_Flag_GotoMin:1,            // b2
                    Ctrl_Flag_Accept:1,             // b3
                    Ctrl_Flag_Reject:1,             // b4
                    Ctrl_Flag_Ping:1,               // b5
                    Ctrl_Flag_PS_RDY:1,             // b6
                    Ctrl_Flag_Get_Source_Cap:1,     // b7
                    Ctrl_Flag_Get_Sink_Cap:1,       // b8
                    Ctrl_Flag_DR_Swap:1,            // b9
                    Ctrl_Flag_PR_Swap:1,            // b10
                    Ctrl_Flag_VCONN_Swap:1,         // b11
                    Ctrl_Flag_Wait:1,               // b12
                    Ctrl_Flag_Soft_Reset:1,         // b13
                    Ctrl_Flag_Reserved_b14:1,       // b14
                    Ctrl_Flag_Reserved_b15:1,       // b15
                    Data_Flag_Reserved_b16:1,       // b16
                    Data_Flag_SRC_Capability:1,     // b17
                    Data_Flag_Request:1,            // b18
                    Data_Flag_BIST:1,               // b19
                    Data_Flag_SNK_Capability:1,     // b20
                    Data_Flag_Reserved_05:1,        // b21
                    Data_Flag_Reserved_06:1,        // b22
                    Data_Flag_Reserved_07:1,        // b23
                    Data_Flag_Reserved_08:1,        // b24
                    Data_Flag_Reserved_09:1,        // b25
                    Data_Flag_Reserved_10:1,        // b26
                    Data_Flag_Reserved_11:1,        // b27
                    Data_Flag_Reserved_12:1,        // b28
                    Data_Flag_Reserved_13:1,        // b29
                    Data_Flag_Reserved_14:1,        // b30
                    Data_Flag_Vender_Defined:1;     // b31

  } BITS;
} MSG_IRQ_STATUS_Type;


typedef union
{
    uint32_t DATA;
    uint8_t  BYTES[4];
    struct {
        uint32_t    Vdm_Flag_Reserve_b0:1,          // b0
                    Vdm_Flag_Discover_ID:1,         // b1
                    Vdm_Flag_Discover_SVIDs:1,      // b2
                    Vdm_Flag_Discover_MODEs:1,      // b3
                    Vdm_Flag_Enter_Mode:1,          // b4
                    Vdm_Flag_Exit_Mode:1,           // b5
                    Vdm_Flag_Attention:1,           // b6
                    Vdm_Flag_Reserved:25;           // b7 - b31

  } BITS;
} VDM_MSG_IRQ_STATUS_Type;


typedef union
{
    uint32_t DATA;
    uint8_t  BYTES[4];
    struct {
        uint32_t    Ssm_Flag_Reserve_b0:1,      // b0
                    Ssm_Flag_Identification:1,  // b1
                    Ssm_Flag_RandomNumber:1,    // b2
                    Ssm_Flag_Encrypted_Data:1,  // b3
                    Ssm_Flag_Reserved:27,       // b4 - b30
                    Ssm_Flag_AES_Done:1;
  } BITS;
} SSM_MSG_IRQ_STATUS_Type;

typedef union
{
    uint32_t DATA;
    uint8_t  BYTES[4];
    struct {
        uint32_t    RID:8,
                    KID:8,
                    ACC_CMD:8,
                    Reserved:8;
  } BITS;
} SSM_HW_ID_VALUE_Type;

typedef union
{
    uint32_t DATA;
    uint8_t  BYTES[4];
    struct {
        uint32_t    Product_ID:16,
                    Reserved:16;
  } BITS;
} SSM_HW_PID_VALUE_Type;

typedef union
{
    uint32_t DATA;
    uint8_t  BYTES[4];
    struct {
        uint8_t Use_CMD1   : 8,
                Use_CMD2   : 8,
                Use_Data1  : 8,
                Use_Data2  : 8;
  } BITS;
} SSM_HW_USE_MSG_Type;
#endif

typedef struct
{
    HW_VERSION_Type     HW_VERSION_1;   // 0x0000h //lse2
    HW_VERSION_Type     HW_VERSION_2;   // 0x0004h
    SW_VERSION_Type     SW_VERSION_1;   // 0x0008h
    SW_VERSION_Type     SW_VERSION_2;   // 0x000Ch
    I2C_SLV_CMD_Type    I2C_SLV_CMD;    // 0x0010h
    I2C_SLV_RSP_Type    I2C_SLV_RSP;    // 0x0014h
    #if 0
    EXT_SRAM_Reserved_Type       Reserved_18h;   // 0x0018h
    EXT_SRAM_Reserved_Type       Reserved_1Ch;   // 0x001Ch
    FUNC_STATE_Type     FUNC_STATE;     // 0x0020h
    FLASH_STATE_Type    FLASH_STATE;    // 0x0024h
    EXT_SRAM_Reserved_Type      Reserved_28h;   // 0x0028h
    EXT_SRAM_Reserved_Type      Reserved_2Ch;   // 0x002Ch
    SYNC_STATUS_Type            SYNC_STATUS;            // 0x0030h
    CTRL_MSG_STATUS_Type        CTRL_MSG_STATUS;        // 0x0034h
    DATA_MSG_STATUS_Type        DATA_MSG_STATUS;        // 0x0038h
    EXTENDED_MSG_STATUS_Type    EXTENDED_MSG_STATUS;    // 0x003Ch
    MSG_IRQ_STATUS_Type         MSG_IRQ_STATUS;         // 0x0040h
    VDM_MSG_IRQ_STATUS_Type     VDM_MSG_IRQ_STATUS;     // 0x0044h
    SSM_MSG_IRQ_STATUS_Type     SSM_MSG_IRQ_STATUS;     // 0x0048h
    VDM_MSG_IRQ_STATUS_Type     DBG_VDM_MSG_IRQ_STATUS;     // 0x004Ch
    SSM_HW_ID_VALUE_Type        SSM_HW_ID_VALUE;        // 0x0050h
    SSM_HW_PID_VALUE_Type       SSM_HW_PID_VALUE;       // 0x0054h
    SSM_HW_USE_MSG_Type         SSM_HW_USE_MSG;         // 0x0058h
    #endif
} EXT_SRAM_Type;

typedef struct
{
    uint32_t    SW_Version;
    uint32_t    SW_Start_Addr;
    uint32_t    SW_End_Addr;
    uint32_t    SW_CRC_VALUE;
} SW_IMAGE_HEADER_Type;

#endif  /* __EXT_SRAM_H */

