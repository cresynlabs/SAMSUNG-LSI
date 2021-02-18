/*
* @file    peri_flash_con.h
* @author  Power Device Team
* @version V1.0.0
* @date    2015.01.27
* @brief   Header for Flash Controller module
******************************************************************************
*/
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef _PERI_FLASH_CON_H_
#define _PERI_FLASH_CON_H_

typedef union
{
    uint32_t DATA;
    struct {
        uint32_t   Reserved:32;
  } BITS;
} Reserved_Type;

typedef union
{
    uint32_t DATA;
    struct {
        uint32_t   WRMD:2,
                   HVEN:1,
                   ERASEMD:2,
                   Reserved:27;
  } BITS;
} FRWCON_Type;

typedef union
{
    uint32_t DATA;
    struct {
        uint32_t    FSHSTAT:4,
                    Reserved:28;
  } BITS;
} FSHSTAT_Type;

typedef union
{
    uint32_t DATA;
    struct {
        uint32_t   LDTEN:1,
                   REDEN:1,
                   DCTEN:1,
                   Reserved1:1,
                   MODESEL:1,
                   PROTEN0:1,
                   PROTEN1:1,
                   PROTEn2:1,
                   MANUAL_LDT_UPDATE:1,
                   Reserved2:23;
  } BITS;
} LDTCON_Type;

typedef union
{
    uint32_t DATA;
    struct {
        uint32_t   IFEN:1,
                   User_Mode_test_selection:1,
                   Test_Register_access_bit:1,
                   Reserved1:2,
                   Option_value_update_bit:1,
                   Reserved2:5,
                   FLASH_IP_HVTRIM_FLAG:1,
                   Reserved3:20;
  } BITS;
} FSHCON0_Type;


typedef union
{
    uint32_t DATA;
    struct {
        uint32_t   DCT0:32;
  } BITS;
} DCT0_Type;

typedef union
{
    uint32_t DATA;
    struct {
		uint32_t	FLASH_UPDATE_PATTERN:6,
					Reserved1:29;
  } BITS;
} LDT0_Type;

typedef union
{
    uint32_t DATA;
    struct {
        uint32_t    _2X_Prefetch_enable:1,
                    Reserved1:3,
                    NOR1Data:1,
                    NOR1Pgm:1,
                    NOR0Data:1,
                    NOR0Pgm:1,
                    Bank1_2wait_Data_Read:1,
                    Bank1_3wait_Data_Read:1,
                    Bank0_2wait_Data_Read:1,
                    Bank0_3wait_Data_Read:1,
                    Reserved2:20;
  } BITS;
} DCYCRDCON_Type;

typedef struct
{
    FRWCON_Type     FRWCON;
    FSHSTAT_Type    FSHSTAT;
    Reserved_Type   RSVD_08;
    Reserved_Type   RSVD_0C;
    Reserved_Type   RSVD_10;
    Reserved_Type   RSVD_14;
    Reserved_Type   RSVD_18;
    Reserved_Type   RSVD_1C;
    Reserved_Type   RSVD_20;
	Reserved_Type	RSVD_24;
    Reserved_Type   RSVD_28;
    Reserved_Type   RSVD_2C;
    LDTCON_Type     LDTCON;
    FSHCON0_Type    FSHCON0;
    Reserved_Type   RSVD_38;
    Reserved_Type   RSVD_3C;
    DCT0_Type       DCT0;
    Reserved_Type   RSVD_44;
	LDT0_Type		LDT0;
    Reserved_Type   RSVD_48;
    Reserved_Type   RSVD_50;
    Reserved_Type   RSVD_54;
    Reserved_Type   RSVD_58;
    Reserved_Type   RSVD_5C;
    Reserved_Type   RSVD_60;
    Reserved_Type   RSVD_64;
    Reserved_Type   RSVD_68;
    Reserved_Type   RSVD_6C;
    Reserved_Type   RSVD_70;
    Reserved_Type   RSVD_74;
    Reserved_Type   RSVD_78;
    Reserved_Type   RSVD_7C;
    Reserved_Type   RSVD_80;
    Reserved_Type   RSVD_84;
    Reserved_Type   RSVD_88;
    Reserved_Type   RSVD_8C;
    Reserved_Type   RSVD_90;
    Reserved_Type   RSVD_94;
    Reserved_Type   RSVD_98;
    Reserved_Type   RSVD_9C;
    Reserved_Type   RSVD_A0;
    Reserved_Type   RSVD_A4;
    Reserved_Type   RSVD_A8;
    Reserved_Type   RSVD_AC;
    Reserved_Type   RSVD_B0;
    Reserved_Type   RSVD_B4;
    Reserved_Type   RSVD_B8;
    Reserved_Type   RSVD_BC;
    Reserved_Type   RSVD_C0;
    Reserved_Type   RSVD_C4;
    Reserved_Type   RSVD_C8;
    Reserved_Type   RSVD_CC;
    Reserved_Type   RSVD_D0;
    Reserved_Type   RSVD_D4;
    Reserved_Type   RSVD_D8;
    Reserved_Type   RSVD_DC;
    Reserved_Type   RSVD_E0;
    Reserved_Type   RSVD_E4;
    Reserved_Type   RSVD_E8;
    Reserved_Type   RSVD_EC;
    DCYCRDCON_Type  DCYCRDCON;
    Reserved_Type   RSVD_F4;
    Reserved_Type   RSVD_F8;
    Reserved_Type   RSVD_FC;
} FLASHCON_BLOCK_Type;

#endif

