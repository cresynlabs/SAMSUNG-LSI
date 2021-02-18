/*
******************************************************************************
* @file    plc.h
* @PLCor  Power Device Team
* @version V1.0.0
* @date    15-Aug-2019
* @brief
******************************************************************************
*/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __PLC_H_
#define __PLC_H_

#define PLC_ENABLE
#define PLC_1214_LOG

#define PLC_CLK_TUNE
#define SW_CHKSUM

#define PLC_TX_RETRY_CNT          10
#define PLC_TX_RETRY_INTERVAL_MS    330

#define PLC_CPL_TOUT_MS 15000

#define ADAPTIVE_VPOGO
#define PLC_WORK_PERIOD_MS    15
#define PLC_MULT_PKT_WAIT_TIME_MS    3000
#define NUM_PLC_DATA_MAX    1
#define NUM_PLC_TX_Q 20
#define NUM_PLC_RX_Q 10
#define PLC_MULTI_START_CODE 0x5
#define PLC_MULTI_END_CODE 0xE

#define PLC_LDO_4_8V (0x15)
#define PLC_LDO_4_2V (PLC_LDO_4_8V-12) /* 9 */
#define PLC_LDO_4_4V (PLC_LDO_4_8V-8) /* 13 */
#define PLC_LDO_4_6V (PLC_LDO_4_8V-4) /* 17 */
#define PLC_LDO_4_7V (PLC_LDO_4_8V-2) /* 19 */
#define PLC_LDO_4_9V (PLC_LDO_4_8V+2) /* 23 */
#define PLC_LDO_DEFAULT PLC_LDO_4_6V

#define PLC_LDO_BST_4_3V 0x14
#define PLC_LDO_BST_4_5V 0x1C
#define PLC_LDO_BST_4_7V 0x24


#define PLC_ONGOING 0
#define PLC_OK  1
#define PLC_TOUT 2
#define PLC_ERR 3

/* PLC data 8 bit */
#define PLC_DAT_SHIP_MODE       0x57

#define PLC_MODE_OFF            0x00
#define PLC_MODE_BYPASS         0x01
#define PLC_MODE_LDO            0x02



#ifdef DEBUG_PLC_HIGH
    #define PLC_PRT_HIGH(...) printf(__VA_ARGS__)
#else
    #define PLC_PRT_HIGH(...)
#endif

#ifdef DEBUG_PLC_LVL1
    #define PLC_PRT(...) printf(__VA_ARGS__)
#else
    #define PLC_PRT(...)
#endif

#ifdef DEBUG_PLC_LVL2
    #define _PLC_PRT(...) printf(__VA_ARGS__)
#else
    #define _PLC_PRT(...)
#endif

#ifdef DEBUG_PLC_LVL3
    #define __PLC_PRT(...) printf(__VA_ARGS__)
#else
    #define __PLC_PRT(...)
#endif

/* PLC Header Type (4bits) */
#define PLC_HDR_VERSION     0x1
#define PLC_HDR_STAT        0x2
#define PLC_HDR_SOC         0x3
#define PLC_HDR_SN_0        0x4
#define PLC_HDR_SN_1        0x5
#define PLC_HDR_SN_2        0x6
#define PLC_HDR_SN_3        0x7
#define PLC_HDR_SN_4        0x8
#define PLC_HDR_SN_5        0x9
#define PLC_HDR_CPL         0xA
#define PLC_HDR_VBAT        0xB
#define PLC_HDR_ACK         0xC
#define PLC_HDR_ERR         0xE
#define PLC_HDR_TEST        0xF

/* bud stat data type */
#define PLC_BUD_STAT_VBAT       0x07
#define PLC_BUD_STAT_TEMP       0x18
#define PLC_BUD_STAT_SAFETY_TMR 0x60
#define PLC_BUD_STAT_SOC_100    0x80

/* coupling data type */
#define PLC_BUD_STAT_CPL_END    0x80

/* bud stat : temp detail */
#define PLC_BUD_STAT_TEMP_OK    (0x01) << 3
#define PLC_BUD_STAT_TEMP_LOW   (0x02) << 3
#define PLC_BUD_STAT_TEMP_HIGH  (0x03) << 3

/* bud stat : safety timer detail */
#define PLC_BUD_STAT_STMR_OFF   (0x01) << 5
#define PLC_BUD_STAT_STMR_ON    (0x02) << 5

/* cradle stat : detail */
#define PLC_CDL_STAT_WCIN_ON     0x03
#define PLC_CDL_STAT_VBUS_ON     0x02
#define PLC_CDL_STAT_BATT        0x01
#define PLC_CDL_STAT_TEMP_OK     0x10
#define PLC_CDL_STAT_TEMP_CTRL   0x20
#define PLC_CDL_STAT_TEMP_BLK    0x30

#define PLC_CDL_STAT_D2D_ON         0x08
#define PLC_CDL_STAT_D2D_OFF        0x04
#define PLC_CDL_STAT_SINGLE_BUD 0x40
#define PLC_CDL_STAT_DOUBLE_BUD 0x80

/* Earbud -> Cradle */
#define PLC_EC_HDR_CMD          0x9
#define PLC_EC_HDR_STAT         0xA
#define PLC_EC_HDR_VBAT          0xB
#define PLC_EC_HDR_SN           0xD
#define PLC_EC_HDR_BT_ADDR      0xE
#define PLC_EC_HDR_USR_DFN      0xF

#define PLC_EC_STAT_BAT_FUL     0x01
#define PLC_EC_STAT_OV_TEMP     0x02
#define PLC_EC_STAT_TMR_EXP     0x04
#define PLC_EC_STAT_RECHAR      0x08
#define PLC_EC_STAT_PING        0xFF

typedef union
{
	  uint32_t DATA;
	  struct {
		  uint32_t Rxhdr:8,
		  	       Rxdata:8,
		  	       Txhdr:8,
		  	       Txdata:8;
	} BITS;
} plc_mon_t;

typedef union
{
	  uint32_t DATA;
	  struct {
		  uint32_t HEADER:4,
		  	       DATA:8,
		  	       CHKSUM:4,
		  	       ERROR:16;
	} BITS;
} plc_packet_t;

typedef enum {
	PLC_STBY            = 0,
	PLC_RX_ACK_SENT 	 = 0x11,
	PLC_RX_ACK_TRANS_DONE,
	PLC_RX_GOT_MSG,
	PLC_RX_MSG_HANDLED,
    PLC_TX_ACK_RDY      = 0x20,
    PLC_TX_ENQ,
	PLC_TX_SENDING,
	PLC_TX_WAIT_FOR_ACK,
	PLC_TX_ACK_RCVD,
	PLC_TX_ACK_NOT_RCVD,
} plc_state_t;

/* PLC PROTOCOL
 * single-byte Tx */
typedef enum {
	eWCIN_ON,
	eWCIN_OFF,
	eCHGIN_ON,
	eCHGIN_OFF,
	eTEMP_OK,
	eTEMP_CTRL,
	eTEMP_BLK,	
	eHALL_OPEN,
	eHALL_CLOSE,
} c2e_stat_t;

typedef struct {
	plc_state_t  plc_state;
	uint8_t     len;
	uint8_t     idx;
	uint8_t     hdr;
	uint8_t     data[NUM_PLC_DATA_MAX+1];
} plc_msg_multi_t;

typedef struct {
	uint8_t  vbatcode;
	uint8_t  wpt_in;
	uint8_t  ta_in;	
	uint8_t attach_l;
	uint8_t attach_r;
	uint8_t  tx_error_cnt;
	uint8_t  tx_queue_idx;
	plc_state_t  tx_state;
	plc_state_t  tx_state_prev;
	plc_state_t  rx_state;
	plc_state_t  rx_state_prev;
	plc_packet_t rx_packet;
	uint32_t  tx_start_time;
	plc_msg_multi_t     TxQ[NUM_PLC_TX_Q];
	uint8_t soc_full_f;
} plc_t;

typedef enum {
	eCPL_INIT = 0x0,
	eCPL_START = 0x01,
	eCPL_RX_DONE = 0x3F, /* Got 6 Bytes: bit field for each of 6 Bytes */
	eCPL_TX_DONE = 0xDD, /* Coupling data was sent to opposite Bud */
	eCPL_FAIL = 0xEE, /* Error. Give up coupling: LED Red */
	eCPL_END = 0xFF, /* Coupling data was rcvd in Bud */
} coupling_state_t;

typedef struct {
	unsigned char      SN[6];
	coupling_state_t state;
	uint32_t timer;
} coupling_info_t;

uint8_t plc_msg_q(uint8_t dir, uint8_t hdr, uint8_t len, uint8_t data, plc_t *plc);
void plc_noti_stat(c2e_stat_t estat);

uint32_t plc_tx_state_update(uint8_t dir, plc_state_t state, plc_t *plc);
uint32_t plc_rx_state_update(uint8_t dir, plc_state_t state, plc_t *plc);

void plc_analog_init(uint8_t dir);
void plc_init(uint8_t dir, plc_t *plc);

uint8_t plc_get_ack_rcv_done(uint8_t dir);
void plc_set_ack_rcv_done_clr(uint8_t dir);
uint8_t plc_get_data_rcv_done(uint8_t dir);
void plc_set_data_rcv_done_clr(uint8_t dir);
void plc_clr_sw(uint8_t dir, plc_t *plc);
void plc_clr_tx_reg(uint8_t dir, plc_t *plc);
void plc_clr_rx_reg(uint8_t dir, plc_t *plc);
uint32_t plc_send_data(uint8_t dir, uint8_t hdr, uint8_t data, plc_t *plc);
uint32_t plc_send_ack(uint8_t dir, plc_t *plc);

void plc_set_plc_mode(uint8_t dir, uint8_t mode);
uint8_t plc_get_plc_mode(uint8_t dir);
void plc_ocp_scp_enable(void);
uint8_t get_scp_ocp_int(uint8_t dir);
void set_scp_ocp_int_clr(uint8_t dir);
void set_scp_flag_vref(void);

void plcdrv_set_ldo_ocp(void);

void plc_set_plc_output(uint8_t dir, uint8_t data);
uint8_t plc_get_plc_output(uint8_t dir);

void plcdrv_set_fullcheck(uint8_t dir, uint8_t data, plc_t *plc);
uint8_t plcdrv_get_fullcheck(uint8_t dir, plc_t *plc);

uint8_t plc_get_pogo_is(uint8_t dir);

void plc_tx_process(plc_t *plc);
void plc_rx_process(uint8_t dir, plc_t *plc);

void plcdrv_set_stepcharging(uint8_t dir, uint8_t vbat_code);
uint32_t plc_rx_state_update_r(plc_state_t state);
uint32_t plc_rx_state_update_l(plc_state_t state);

extern void *addr_flag;
void set_memory_addr(plc_t *plc);
plc_t* get_memory_addr(void);
#endif /* __PLC_H_ */
