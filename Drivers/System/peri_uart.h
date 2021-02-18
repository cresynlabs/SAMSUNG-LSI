/*
******************************************************************************
* @file    peri_uart.h
* @author  Power Device Team
* @version V1.0.0
* @date    2015.01.27
* @brief   Header for UART Block
******************************************************************************
*/
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef _PERI_UART_H_
#define _PERI_UART_H_


typedef union
{
     uint32_t DATA0;
     uint32_t DATA4;
     uint32_t DATA8;
     uint32_t DATAC;
} Reserved_Bulk_Type;


typedef union
{
    Reserved_Bulk_Type  DATA10;
    Reserved_Bulk_Type  DATA20;
    Reserved_Bulk_Type  DATA30;
    Reserved_Bulk_Type  DATA40;
    Reserved_Bulk_Type  DATA50;
    Reserved_Bulk_Type  DATA60;
    Reserved_Bulk_Type  DATA70;
    Reserved_Bulk_Type  DATA80;
    Reserved_Bulk_Type  DATA90;
    Reserved_Bulk_Type  DATAA0;
    Reserved_Bulk_Type  DATAB0;
    Reserved_Bulk_Type  DATAC0;
    Reserved_Bulk_Type  DATAD0;
    Reserved_Bulk_Type  DATAE0;
    Reserved_Bulk_Type  DATAF0;
} Reserved_uart1_Type;

typedef union
{
    Reserved_Bulk_Type  DATA10;
    Reserved_Bulk_Type  DATA20;
    Reserved_Bulk_Type  DATA30;
    Reserved_Bulk_Type  DATA40;
    Reserved_Bulk_Type  DATA50;
    Reserved_Bulk_Type  DATA60;
    Reserved_Bulk_Type  DATA70;
    Reserved_Bulk_Type  DATA80;
    Reserved_Bulk_Type  DATA90;
    Reserved_Bulk_Type  DATAA0;
    Reserved_Bulk_Type  DATAB0;
    Reserved_Bulk_Type  DATAC0;
    Reserved_Bulk_Type  DATAD0;
} Reserved_uart2_Type;

typedef union
{
    uint32_t DATA;
    struct {
        uint32_t   DATA:8,
                   FE:1,
                   PE:1,
                   BE:1,
                   OE:1,
                   Reserved:20;
  } BITS;
} UARTDR_Type;

typedef union
{
    uint32_t DATA;
    struct {
        uint32_t   FE:1,
                   PE:1,
                   BE:1,
                   OE:1,
                   Reserved:28;
  } BITS;
} UARTRSR_Type;

typedef union
{
    uint32_t DATA;
    struct {
        uint32_t   CTS:1,
                   DCR:1,
                   DCD:1,
                   BUSY:1,
                   RXFE:1,
                   TXFF:1,
                   RXFF:1,
                   TXFE:1,
                   RI:1,
                   Reserved:23;
  } BITS;
} UARTFR_Type;

typedef union
{
    uint32_t DATA;
    struct {
        uint32_t   BAUD_DIVINT:16,
                   Reserved:16;
  } BITS;
} UARTIBRD_Type;

typedef union
{
    uint32_t DATA;
    struct {
        uint32_t   BAUD_DIVFRAC:16,
                   Reserved:16;
  } BITS;
} UARTFBRD_Type;

typedef union
{
    uint32_t DATA;
    struct {
        uint32_t   BRK:1,
                   PEN:1,
                   EPS:1,
                   STP2:1,
                   FEN:1,
                   WLEN:2,
                   SPS:1,
                   Reserved:24;
  } BITS;
} UARTLCR_H_Type;

typedef union
{
    uint32_t DATA;
    struct {
        uint32_t   UARTEN:1,
                   SIREN:1,
                   SIRLP:1,
                   Reserved1:4,
                   LBE:1,
                   TXE:1,
                   RXE:1,
                   DTR:1,
                   RTS:1,
                   Out1:1,
                   Out2:1,
                   RTSEn:1,
                   CTSEn:1,
                   Reserved2:16;
  } BITS;
} UARTCR_Type;

typedef union
{
    uint32_t DATA;
    struct {
        uint32_t   TXIFLSEL:3,
                   RXIFSEL:3,
                   Reserved:26;
  } BITS;
} UARTIFLS_Type;

typedef union
{
    uint32_t DATA;
    struct {
        uint32_t   RIMIM:1,
                   CTSMIM:1,
                   DCDMIM:1,
                   DSRMIM:1,
                   RXIM:1,
                   TXIM:1,
                   RTIM:1,
                   FEIM:1,
                   PEIM:1,
                   BEIM:1,
                   OEIM:1,
                   Reserved:21;
  } BITS;
} UARTIMSC_Type;

typedef union
{
    uint32_t DATA;
    struct {
        uint32_t   RIRMIS:1,
                   CTSRMIS:1,
                   DCDRMIS:1,
                   DSRRMIS:1,
                   RXRIS:1,
                   TXRIS:1,
                   RTRIS:1,
                   FERIS:1,
                   PERIS:1,
                   BERIS:1,
                   OERIS:1,
                   Reserved:21;
  } BITS;
} UARTRIS_Type;

typedef union
{
    uint32_t DATA;
    struct {
        uint32_t   RIMMIS:1,
                   CTSMMIS:1,
                   DCDMMIS:1,
                   DSRMMIS:1,
                   RXMIS:1,
                   TXMIS:1,
                   RTMIS:1,
                   FEMIS:1,
                   PEMIS:1,
                   BEMIS:1,
                   OEMIS:1,
                   Reserved:21;
  } BITS;
} UARTMIS_Type;

typedef union
{
    uint32_t DATA;
    struct {
        uint32_t   RIMIC:1,
                   CTSMIC:1,
                   DCDMIC:1,
                   DSRMIC:1,
                   RXIC:1,
                   TXIC:1,
                   RTIC:1,
                   FEIC:1,
                   PEIC:1,
                   BEIC:1,
                   OEIC:1,
                   Reserved:21;
  } BITS;
} UARTICR_Type;

typedef union
{
    uint32_t DATA;
    struct {
        uint32_t   RXDMAE:1,
                   TXDMAE:1,
                   DMAONERR:1,
                   Reserved:29;
  } BITS;
} UARTDMACR_Type;

typedef union
{
    uint32_t DATA;
    struct {
        uint32_t   UARTTCR:3,
                   Reserved:29;
  } BITS;
} UARTTCR_Type;

typedef union
{
    uint32_t DATA;
    struct {
        uint32_t   UARTITIP:8,
                   Reserved:24;
  } BITS;
} UARTITIP_Type;

typedef union
{
    uint32_t DATA;
    struct {
        uint32_t   UARTITOP:14,
                   Reserved:24;
  } BITS;
} UARTITOP_Type;

typedef union
{
    uint32_t DATA;
    struct {
        uint32_t   UARTTDR:11,
                   Reserved:21;
  } BITS;
} UARTTDR_Type;

typedef union
{
    uint32_t DATA;
    struct {
        uint32_t   UARTPeriphlD0:8,
                   Reserved:24;
  } BITS;
} UARTPeriphlD0_Type;

typedef union
{
    uint32_t DATA;
    struct {
        uint32_t   UARTPeriphlD1:8,
                   Reserved:24;
  } BITS;
} UARTPeriphlD1_Type;


typedef union
{
    uint32_t DATA;
    struct {
        uint32_t   UARTPeriphlD2:8,
                   Reserved:24;
  } BITS;
} UARTPeriphlD2_Type;


typedef union
{
    uint32_t DATA;
    struct {
        uint32_t   UARTPeriphlD3:8,
                   Reserved:24;
  } BITS;
} UARTPeriphlD3_Type;


typedef union
{
    uint32_t DATA;
    struct {
        uint32_t   UARTPCellD0:8,
                   Reserved:24;
  } BITS;
} UARTPCellD0_Type;

typedef union
{
    uint32_t DATA;
    struct {
        uint32_t   UARTPCellD1:8,
                   Reserved:24;
  } BITS;
} UARTPCellD1_Type;

typedef union
{
    uint32_t DATA;
    struct {
        uint32_t   UARTPCellD2:8,
                   Reserved:24;
  } BITS;
} UARTPCellD2_Type;

typedef union
{
    uint32_t DATA;
    struct {
        uint32_t   UARTPCellD3:8,
                   Reserved:24;
  } BITS;
} UARTPCellD3_Type;


typedef struct
{
    UARTDR_Type         	UARTDR;			// 0x000
    UARTRSR_Type        	UARTRSR;		// 0x004
    Reserved_Type       	RSVD_008;		// 0x008
    Reserved_Type       	RSVD_00C;		// 0x00c
    Reserved_Type       	RSVD_010;		// 0x010
    Reserved_Type       	RSVD_014;		// 0x014
    UARTFR_Type         	UARTFR;    		// 0x018
    Reserved_Type       	RSVD_01C;		// 0x01c
    Reserved_Type       	RSVD_020;		// 0x020
    UARTIBRD_Type       	UARTIBRD;		// 0x024
    UARTFBRD_Type       	UARTFBRD;		// 0x028
    UARTLCR_H_Type      	UARTLCR_H;		// 0x02c
    UARTCR_Type         	UARTCR;			// 0x030
    UARTIFLS_Type       	UARTIFLS;		// 0x034
    UARTIMSC_Type       	UARTIMSC;		// 0x038
    UARTRIS_Type        	UARTRIS;		// 0x03c
    UARTMIS_Type        	UARTMIS;		// 0x040
    UARTICR_Type        	UARTICR;		// 0x044
    UARTDMACR_Type      	UARTDMACR;    	// 0x048
    Reserved_Type       	RSVD_04C;		// 0x04c
    Reserved_Type       	RSVD_050;		// 0x050
    Reserved_Type       	RSVD_054;		// 0x054
    Reserved_Type       	RSVD_058;		// 0x058
    Reserved_Type       	RSVD_05C;		// 0x05c
    Reserved_Type       	RSVD_060;		// 0x060
    Reserved_Type       	RSVD_064;		// 0x064
    Reserved_Type       	RSVD_068;		// 0x068
    Reserved_Type       	RSVD_06C;		// 0x06c
    Reserved_Type       	RSVD_070;		// 0x070
    Reserved_Type       	RSVD_074;		// 0x074
    Reserved_Type       	RSVD_078;		// 0x078
    Reserved_Type       	RSVD_07C;		// 0x07c
    UARTTCR_Type        	UARTTCR;		// 0x080
    UARTITIP_Type       	UARTITIP;		// 0x084
    UARTITOP_Type       	UARTITOP;		// 0x088
    UARTTDR_Type        	UARTTDR;		// 0x08c
    Reserved_Type       	RSVD_090;
    Reserved_Type       	RSVD_094;
    Reserved_Type       	RSVD_098;
    Reserved_Type       	RSVD_09C;
    Reserved_Type       	RSVD_0A0;
    Reserved_Type       	RSVD_0A4;
    Reserved_Type       	RSVD_0A8;
    Reserved_Type       	RSVD_0AC;
    Reserved_Type       	RSVD_0B0;
    Reserved_Type       	RSVD_0B4;
    Reserved_Type       	RSVD_0B8;
    Reserved_Type       	RSVD_0BC;
    Reserved_Type       	RSVD_0C0;
    Reserved_Type       	RSVD_0C4;
    Reserved_Type       	RSVD_0C8;
    Reserved_Type       	RSVD_0CC;
    Reserved_Type       	RSVD_0D0;
    Reserved_Type       	RSVD_0D4;
    Reserved_Type       	RSVD_0D8;
    Reserved_Type       	RSVD_0DC;
    Reserved_Type       	RSVD_0E0;
    Reserved_Type       	RSVD_0E4;
    Reserved_Type       	RSVD_0E8;
    Reserved_Type       	RSVD_0EC;
    Reserved_Type       	RSVD_0F0;
    Reserved_Type       	RSVD_0F4;
    Reserved_Type       	RSVD_0F8;
    Reserved_Type       	RSVD_0FC;
    Reserved_uart1_Type  	RSVD_100_1FF;
    Reserved_uart1_Type  	RSVD_200_2FF;
    Reserved_uart1_Type  	RSVD_300_3FF;
    Reserved_uart1_Type  	RSVD_400_4FF;
    Reserved_uart1_Type  	RSVD_500_5FF;
    Reserved_uart1_Type  	RSVD_600_6FF;
    Reserved_uart1_Type  	RSVD_700_7FF;
    Reserved_uart1_Type  	RSVD_800_8FF;
    Reserved_uart1_Type  	RSVD_900_9FF;
    Reserved_uart1_Type  	RSVD_A00_AFF;
    Reserved_uart1_Type  	RSVD_B00_BFF;
    Reserved_uart1_Type  	RSVD_C00_CFF;
    Reserved_uart1_Type  	RSVD_D00_DFF;
    Reserved_uart1_Type  	RSVD_E00_EFF;
    Reserved_uart2_Type  	RSVD_F00_EDF;
    UARTPeriphlD0_Type   	UARTPeriphlD0;
    UARTPeriphlD1_Type   	UARTPeriphlD1;
    UARTPeriphlD2_Type   	UARTPeriphlD2;
    UARTPeriphlD3_Type   	UARTPeriphlD3;
    UARTPCellD0_Type     	UARTPCellD0;
    UARTPCellD1_Type     	UARTPCellD1;
    UARTPCellD2_Type     	UARTPCellD2;
    UARTPCellD3_Type     	UARTPCellD3;
} UART_BLOCK_Type;

#endif /* __UART_BLOCK_H */

