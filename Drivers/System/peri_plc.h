#ifndef _PERI_PLC_H_
#define _PERI_PLC_H_

typedef union
{
    uint32_t DATA;
    struct {
        uint32_t   Reserved:32;
  } BITS;
}PLCReserved_Type;

typedef union
{
	  uint32_t DATA;
	  struct {
		  uint32_t DATA_MOD_START_R_INT:1,
		  	       TX_data_msg_end_R:1,
		  	       TX_trans_done_R:1,
		  	       TX_ack_wait_done_R:1,
		  	       TX_data_not_rcv_ack_R:1,
		  	       TX_data_wait_retry_done_R:1,
		  	       TX_start_overlab_ignore_R:1,
		  	       TX_start_debounce_work_R:1,
		  	       RX_start_bit_R:1,
		  	       RX_data_head_update_R:1,
		  	       RX_data_msg_update_R:1,
		  	       RX_data_rcv_done_R:1,
		  	       RX_pre_cnt_timeout_R:1,
		  	       RX_pre_after_cnt_timeout_R:1,
		  	       RX_err_occurred_R:1,
		  	       Reserved1:1,
		  	       DATA_DEMOD_START_R_INT:1,
		  	       Reserved2:1,
		  	       RX_data_wait_done_for_ack_R:1,
		  	       RX_data_wait_done_for_ack_expired_R:1,
		  	       RX_ack_rcv_done_R:1,
		  	       RX_ack_wait_done_R:1,
		  	       Reserved3:2,
		  	       LDO_OUT_SCP_PE_R_INT:1,
		  	       LDO_OUT_SCP_NE_R_INT:1,
		  	       POTO_OUT_SCP_PE_R_INT:1,
		  	       POGO_OUT_SCP_NE_R_INT:1,
		  	       POGO_OUT_OCP_PE_R_INT:1,
		  	       POGO_OUT_OCP_NE_R_INT:1,
		  	       PLC_MH_RDY_R_INT:1,
		  	       Resrerved4:1;
	} BITS;
}PLC_REG_00;

typedef union
{
	  uint32_t DATA;
	  struct {
		  uint32_t DAT_MOD_STRT_R_MASK:1,
		  	       TX_data_msg_end_R_MASK:1,
		  	       DATA_MOD_DONE_R_MASK:1,
		  	       TX_ack_wait_done_R_MASK:1,
		  	       TX_data_not_rcv_ack_R_MASK:1,
		  	       TX_data_wait_retry_doe_R_MASK:1,
		  	       TX_start_overlab_ignore_R_MASK:1,
		  	       TX_start_debounce_work_R_MASK:1,
		  	       RX_start_bit_R_MASK:1,
		  	       RX_data_head_update_R_MASK:1,
		  	       RX_data_msg_update_R_MASK:1,
		  	       DATA_DEMOD_DONE_R_MASK:1,
		  	       RX_pre_cnd_timeout_R_MASK:1,
		  	       RX_pre_after_cnt_timeout_R_MASK:1,
		  	       RX_err_occurred_R_MASK:1,
		  	       Reserved1:1,
		  	       DATA_DMOD_START_R_MASK:1,
		  	       Reserved2:1,
		           ACK_MOD_RDY_R_MASK:1,
		  	       ACK_FAIL_R_MASK:1,
		  	       RX_ack_rcv_done_R_MASK:1,
		  	       RX_ack_wait_done_R_MASK:1,
		  	       Reserved3:2,
		  	       LDO_OUT_SCP_PE_R_MASK:1,
		  	       LDO_OUT_SCP_NE_R_MASK:1,
		  	       POGO_OUT_SCP_PE_R_MASK:1,
		  	       POGO_OUT_SCP_NE_R_MASK:1,
		  	       POGO_OUT_OCP_PE_R_MASK:1,
		  	       POGO_OUT_OCP_NE_R_MASK:1,
		  	       PLC_MH_RDY_R_MASK:1,
		  	       Reserved4:1;
	} BITS;
}PLC_REG_04;

typedef union
{
	  uint32_t DATA;
	  struct {
		  uint32_t DATA_MOD_START_R_CLR:1,
		  	       TX_data_msg_end_R_CLR:1,
		  	       DATA_MOD_DON_R_CLR:1, // TX_trans_done_R
		  	       TX_ack_wait_done_R_CLR:1,
		  	       TX_data_not_rcv_ack_R_CLR:1,
		  	       TX_data_wait_retry_done_R_CLR:1,
		  	       TX_start_overlab_ignore_R_CLR:1,
		  	       TX_start_debounce_work_R_CLR:1,
		  	       RX_start_bit_R_CLR:1,
		  	       RX_data_head_update_R_CLR:1,
		  	       TX_data_msg_update_R_CLR:1,
		  	       DATA_DEMOD_DONE_R_CLR:1,
		  	       RX_pre_cnt_timeout_R_CLR:1,
		  	       RX_pre_after_cnt_timeout_R_CLR:1,
		  	       RX_err_occurred_R_CLR:1,
		  	       Reserved1:1,
		  	       DATA_DEMOD_START_R_CLR:1,
		  	       Reserved2:1,
		  	       ACK_MOD_READY_R_CLR:1, // RX_data_wait_done_for_ack_R
		  	       ACK_FAIL_R_CLR:1, // RX_data_wait_done_for_ack_expired_R
		  	       RX_ack_rcv_DONE_R_CLR:1,
		  	       RX_ack_wait_done_R_CLR:1,
		  	       Reserved3:2,
		  	       LDO_OUT_SCP_PE_R_CLR:1,
		  	       LDO_OUT_SCP_NE_R_CLR:1,
		  	       POGO_OUT_SCP_PE_R_CLR:1,
		  	       POGO_OUT_SCP_NE_R_CLR:1,
		  	       POGO_OUT_OCP_PE_R_CLR:1,
		  	       POGO_OUT_OCP_NE_R_CLR:1,
		  	       PLC_MH_RDY_R_CLR:1,
		  	       Reserved4:1;
	} BITS;
}PLC_REG_08;

typedef union
{
	  uint32_t DATA;
	  struct {
		  uint32_t RX_data_wait_R_STATE:1,
		  	       RX_ack_trans_rdy_R_STATE:1,
		  	       RX_ac_wait_R_STATE:1,
		  	       Reserved1:1,
		  	       TX_wait_1bit_R_STATE:1,
		  	       TX_wait_R_STATE:1,
		  	       TX_data_wait_retry_R_STATE:1,
		  	       Reserved2:1,
		  	       TX_check_sum_result_R:4,
		  	       Reserved3:4,
		  	       PLC_CUR_MODE_RIGHT:3,
		  	       Reserved4:5,
		  	       POGO_OUT_SCP_R_STATE:1,
		  	       LDO_OUT_SCP_R_STATE:1,
		  	       POGO_OUT_OCP_R_STATE:1,
		  	       Reserved5:1,
		  	       PLC_MH_READY_R_STATE:1,
		  	       Reserved6:3;
	} BITS;
}PLC_REG_0C;

typedef union
{
	  uint32_t DATA;
	  struct {
		  uint32_t TX_DATA_SEND_START_R:1,
		  	       TX_ACK_SEND_START_R:1,
		  	       TX_DATA_SEND_START_L:1,
		  	       TX_ACK_SEND_START_L:1,
		  	       Reserved1:4,
		  	       TX_msg_size:8,
		  	       TX_preamble_size_R:3,
		  	       Reserved2:1,
		  	       TX_parity_polarity_R:1,
		  	       TX_chk_sum_Auto_Disagle_R:1,
		  	       TX_Wait_Not_R:1,
		  	       TX_DATA_TEMP_Enable_R:1,
		  	       TX_ack_wait_done_Timer_R:8;
	} BITS;
}PLC_REG_10;

typedef union
{
	  uint32_t DATA;
	  struct {
		  uint32_t TX_HEADER_R:4,
		  	       Reserved1:4,
		  	       TX_DATA_R:8,
		  	       TX_CHK_SUM_Manual_VAL_R:4,
		  	       REserved:4,
		  	       TX_DATA_TEMP_R:8;
	} BITS;
}PLC_REG_14;

typedef union
{
	  uint32_t DATA;
	  struct {
		  uint32_t TX_CLK_DIVIDE_VAL_R:14,
		  	       count_stretch_R:2,
		  	       TX_data_not_rcv_ack_Timer:8,
		  	       TX_data_wait_retry_done_Timer:8;
	} BITS;
}PLC_REG_18;

typedef union
{
	  uint32_t DATA;
	  struct {
		  uint32_t LDO_SET_AT_SENDING_R:5,
		  	       Reserved1:3,
		  	       LDO_SEL_R:5,
		  	       Reserved2:3,
		  	       PLC_CS_SEGMENT_R:5,
		  	       Reserved3:11;
	} BITS;
}PLC_REG_1C;

typedef union
{
	  uint32_t DATA;
	  struct {
		  uint32_t RX_Enable_Digital_R:1,
		  	       RX_parity_polarity_R:1,
		  	       Reserved1:6,
		  	       RX_msg_size_R:8,
		  	       RX_period_cnt_VAL_R:15,
		  	       RX_period_cnt_SEL_R:1;
	} BITS;
}PLC_REG_20;

typedef union
{
	  uint32_t DATA;
	  struct {
		  uint32_t RX_min_period_VAL_R:15,
		  	       RX_min_period_sel_R:1,
		  	       RX_pre_after_timeout_cnt_VAL_R:15,
		  	       RX_pre_after_timeout_cnt_SEL_R:1;
	} BITS;
}PLC_REG_24;

typedef union
{
	  uint32_t DATA;
	  struct {
		  uint32_t RX_Period_CLK_Timer_R:15,
		  	       Reserved1:1,
		  	       RX_Deglitch_Timer:8,
		  	       RX_ack_wait_done_Timer:8;
	} BITS;
}PLC_REG_28;

typedef union
{
	  uint32_t DATA;
	  struct {
		  uint32_t RX_wait_done_ack_Timer_R:8,
		  	       RX_wait_done_ack_exp_Timer_R:8,
		  	       TX_msg_cnt:8,
		  	       RX_msg_cnt:8;
	} BITS;
}PLC_REG_2C;

typedef union
{
	  uint32_t DATA;
	  struct {
		  uint32_t RX_HEAD_R:4,
		  	       Reserved1:4,
		  	       RX_MSG_DATA_R:8,
		  	       RX_CHK_SUM_R:4,
		  	       Reserved2:4,
		  	       RX_err_occurred_state_R:4,
		  	       Reserved3:4;
	} BITS;
}PLC_REG_30;

typedef union
{
	  uint32_t DATA;
	  struct {
		  uint32_t RX_ring_buff:11,
		  	       Reserved1:5,
		  	       PLC_RX_err_occur_pre_State_R:7,
		  	       Reserved2:9;
	} BITS;
}PLC_REG_34;

typedef union
{
	  uint32_t DATA;
	  struct {
		  uint32_t RX_min_period:15,
		  	       Reserved1:1,
		  	       RX_period_R:15,
		  	       Reserved2:1;
	} BITS;
}PLC_REG_38;

typedef union
{
	  uint32_t DATA;
	  struct {
		  uint32_t INT_none_mask_state:32;
	} BITS;
}PLC_REG_3C;

typedef union
{
	  uint32_t DATA;
	  struct {
		  uint32_t DATA_MOD_START_L_INT:1,
		  	       TX_data_msg_end_L:1,
		  	       TX_trans_done_L:1,
		  	       TX_ack_wait_done_L:1,
		  	       TX_data_not_rcv_ack_L:1,
		  	       TX_data_wait_retry_done_L:1,
		  	       TX_start_overlab_ignore_L:1,
		  	       TX_start_debounce_work_L:1,
		  	       RX_start_bit_L:1,
		  	       RX_data_head_update_L:1,
		  	       RX_data_msg_update_L:1,
		  	       RX_data_rcv_done_L:1,
		  	       RX_pre_cnt_timeout_L:1,
		  	       RX_pre_after_cnt_timeout_L:1,
		  	       RX_err_occurred_L:1,
		  	       Reserved1:1,
		  	       DATA_DEMOD_START_L_INT:1,
		  	       Reserved2:1,
		  	       RX_data_wait_done_for_ack_L:1,
		  	       RX_data_wait_done_for_ack_expired_L:1,
		  	       RX_ack_rcv_done_L:1,
		  	       RX_ack_wait_done_L:1,
		  	       Reserved3:2,
		  	       LDO_OUT_SCP_PE_L_INT:1,
		  	       LDO_OUT_SCP_NE_L_INT:1,
		  	       POGO_OUT_SCP_PE_L_INT:1,
		  	       POGO_OUT_SCP_NE_L_INT:1,
		  	       POGO_OUT_OCP_PE_L_INT:1,
		  	       POGO_OUT_OCP_NE_L_INT:1,
		  	       PLC_MH_RDY_L_INT:1,
		  	       Resrerved4:1;
	} BITS;
}PLC_REG_40;

typedef union
{
	  uint32_t DATA;
	  struct {
		  uint32_t DAT_MOD_STRT_L_MASK:1,
		  	       TX_data_msg_end_L_MASK:1,
		  	       DATA_MOD_DONE_L_MASK:1,
		  	       TX_ack_wait_done_L_MASK:1,
		  	       TX_data_not_rcv_ack_L_MASK:1,
		  	       TX_data_wait_retry_doe_L_MASK:1,
		  	       TX_start_overlab_ignore_L_MASK:1,
		  	       TX_start_debounce_work_L_MASK:1,
		  	       RX_start_bit_L_MASK:1,
		  	       RX_data_head_update_L_MASK:1,
		  	       RX_data_msg_update_L_MASK:1,
		  	       DATA_DEMOD_DONE_L_MASK:1,
		  	       RX_pre_cnd_timeout_L_MASK:1,
		  	       RX_pre_after_cnt_timeout_L_MASK:1,
		  	       RX_err_occurred_L_MASK:1,
		  	       Reserved1:1,
		  	       DATA_DMOD_START_L_MASK:1,
		  	       Reserved2:1,
		           ACK_MOD_RDY_L_MASK:1,
		  	       ACK_FAIL_L_MASK:1,
		  	       RX_ack_rcv_done_L_MASK:1,
		  	       RX_ack_wait_done_L_MASK:1,
		  	       Reserved3:2,
		  	       LDO_OUT_SCP_PE_L_MASK:1,
		  	       LDO_OUT_SCP_NE_L_MASK:1,
		  	       POGO_OUT_SCP_PE_L_MASK:1,
		  	       POGO_OUT_SCP_NE_L_MASK:1,
		  	       POGO_OUT_OCP_PE_L_MASK:1,
		  	       POGO_OUT_OCP_NE_L_MASK:1,
		  	       PLC_MH_RDY_L_MASK:1,
		  	       Reserved4:1;
	} BITS;
}PLC_REG_44;

typedef union
{
	  uint32_t DATA;
	  struct {
		  uint32_t DATA_MOD_START_L_CLR:1,
		  	       TX_data_msg_end_L_CLR:1,
		  	       DATA_MOD_DON_L_CLR:1, // TX_trans_done_L
		  	       TX_ack_wait_done_L_CLR:1,
		  	       TX_data_not_rcv_ack_L_CLR:1,
		  	       TX_data_wait_retry_done_L_CLR:1,
		  	       TX_start_overlab_ignore_L_CLR:1,
		  	       TX_start_debounce_work_L_CLR:1,
		  	       RX_start_bit_L_CLR:1,
		  	       RX_data_head_update_L_CLR:1,
		  	       TX_data_msg_update_L_CLR:1,
		  	       DATA_DEMOD_DONE_L_CLR:1,
		  	       RX_pre_cnt_timeout_L_CLR:1,
		  	       RX_pre_after_cnt_timeout_L_CLR:1,
		  	       RX_err_occurred_L_CLR:1,
		  	       Reserved1:1,
		  	       DATA_DEMOD_START_L_CLR:1,
		  	       Reserved2:1,
		  	       ACK_MOD_READY_L_CLR:1,
		  	       ACK_FAIL_L_CLR:1,
		  	       RX_ack_rcv_DONE_L_CLR:1,
		  	       RX_ack_wait_done_L_CLR:1,
		  	       Reserved3:2,
		  	       LDO_OUT_SCP_PE_L_CLR:1,
		  	       LDO_OUT_SCP_NE_L_CLR:1,
		  	       POGO_OUT_SCP_PE_L_CLR:1,
		  	       POGO_OUT_SCP_NE_L_CLR:1,
		  	       POGO_OUT_OCP_PE_L_CLR:1,
		  	       POGO_OUT_OCP_NE_L_CLR:1,
		  	       PLC_MH_RDY_L_CLR:1,
		  	       Reserved4:1;
	} BITS;
}PLC_REG_48;

typedef union
{
	  uint32_t DATA;
	  struct {
		  uint32_t RX_data_wait_L_STATE:1,
		  	       RX_ack_trans_rdy_L_STATE:1,
		  	       RX_ac_wait_L_STATE:1,
		  	       Reserved1:1,
		  	       TX_wait_1bit_L_STATE:1,
		  	       TX_wait_L_STATE:1,
		  	       TX_data_wait_retry_L_STATE:1,
		  	       Reserved2:1,
		  	       TX_check_sum_result_L:4,
		  	       Reserved3:4,
		  	       PLC_CUR_MODE_LEFT:3,
		  	       Reserved4:5,
		  	       POGO_OUT_SCP_L_STATE:1,
		  	       LDO_OUT_SCP_L_STATE:1,
		  	       POGO_OUT_OCP_L_STATE:1,
		  	       Reserved5:1,
		  	       PLC_MH_READY_L_STATE:1,
		  	       Reserved6:3;
	} BITS;
}PLC_REG_4C;

typedef union
{
	  uint32_t DATA;
	  struct {
		  uint32_t Reserved1:16,
		  	       TX_preamble_size_L:3,
		  	       Reserved2:1,
		  	       TX_parity_polarity_L:1,
		  	       TX_chk_sum_Auto_Disable_L:1,
		  	       TX_Wait_Not_L:1,
		  	       TX_DATA_TEMP_Enable_L:1,
		  	       TX_ack_wait_done_Timer:8;
	} BITS;
}PLC_REG_50;

typedef union
{
	  uint32_t DATA;
	  struct {
		  uint32_t TX_HEADER_L:4,
		  	       Reserved1:4,
		  	       TX_DATA_L:8,
		  	       TX_CHECK_SUM_Manual_VAL_L:4,
		  	       Reserved2:4,
		  	       TX_DATA_TEMP_L:8;
	} BITS;
}PLC_REG_54;

typedef union
{
	  uint32_t DATA;
	  struct {
		  uint32_t TX_CLK_DIVIDE_VAL_L:14,
		  	       count_stretch_L:2,
		  	       TX_data_not_rcv_ack_Timer:8,
		  	       TX_data_wait_rty_done_Timer:8;

	} BITS;
}PLC_REG_58;

typedef union
{
	  uint32_t DATA;
	  struct {
		  uint32_t LDO_SET_AT_SENDING_L:5,
		  	       Reserved1:3,
		  	       LDO_SEL_L:5,
		  	       Reserved2:3,
		  	       PLC_CS_SEGMENT_L:5,
		  	       Reserved3:11;
	} BITS;
}PLC_REG_5C;

typedef union
{
	  uint32_t DATA;
	  struct {
		  uint32_t RX_Enable_Digital_L:1,
		  	       RX_parity_polarity_L:1,
		  	       Reserved1:14,
		  	       RX_period_cnt_VAL_L:15,
		  	       RX_period_cnt_SEL_L:1;
	} BITS;
}PLC_REG_60;

typedef union
{
	  uint32_t DATA;
	  struct {
		  uint32_t RX_min_period_VAL_L:15,
		  	       RX_min_period_SEL_L:1,
		  	       RX_pre_after_timeout_cnt_VAL_L:15,
		  	       RX_pre_after_timeout_cnt_SEL_L:1;
	} BITS;
}PLC_REG_64;

typedef union
{
	  uint32_t DATA;
	  struct {
		  uint32_t RX_Period_CLK_Timer_L:15,
		  	       Reserved1:1,
		  	       RX_Deglitch_Timer:8,
		  	       RX_ack_wait_done_Timer:8;
	} BITS;
}PLC_REG_68;

typedef union
{
	  uint32_t DATA;
	  struct {
		  uint32_t RX_data_ack_done_for_ack_Timer:8,
		  	       RX_data_wait_done_for_ack_expired_Timer:8,
		  	       Reserved:16;
	} BITS;
}PLC_REG_6C;

typedef union
{
	  uint32_t DATA;
	  struct {
		  uint32_t RX_HEAD_L:4,
		  	       Reserved1:4,
		  	       RX_MSG_DATA_L:8,
		  	       RX_CHK_SUM_L:4,
		  	       Reserved2:4,
		  	       RX_err_occurred_state_L:4,
		  	       Reserved3:4;
	} BITS;
}PLC_REG_70;

typedef union
{
	  uint32_t DATA;
	  struct {
		  uint32_t RX_Ring_buff:11,
		  	       Reserved1:5,
		  	       PLC_RX_err_occurred_pre_fater_State:7,
		  	       Reserved2:9;
	} BITS;
}PLC_REG_74;

typedef union
{
	  uint32_t DATA;
	  struct {
		  uint32_t RX_min_period:15,
		  	       Reserved1:1,
		  	       RX_period_L:15,
		  	       Reserved2:1;
	} BITS;
}PLC_REG_78;

typedef union
{
	  uint32_t DATA;
	  struct {
		  uint32_t INT_none_masking_state_L:32;
	} BITS;
}PLC_REG_7C;

typedef union
{
	  uint32_t DATA;
	  struct {
		  uint32_t PLC_MODE_R:2,
		  	       PLC_MODE_L:2,
		  	       Reserved1:4,
		  	       MH_PLC_TEST_R:3,
		  	       Reserved2:1,
		  	       MH_PLC_TEST_L:3,
		  	       Reserved3:1,
		  	       MONITOR_SEL:8,
		  	       Reserved4:8;
	} BITS;
}PLC_REG_80;


typedef union
{
	  uint32_t DATA;
	  struct {
		  uint32_t O_CH1_LDO_OUT_TRIM:7,
		  	       Reserved1:1,
		  	       O_CH2_LDO_OUT_TRIM:7,
		  	       Reserved2:1,
		  	       O_CH1_LDO_OCP_TRIM:8,
		  	       O_CH2_LDO_OCP_TRIM:8;
	} BITS;
}PLC_REG_90;

typedef union
{
	  uint32_t DATA;
	  struct {
		  uint32_t O_CH2_LDO_OFFSET:4,
		  	       O_CH1_LDO_OFFSET:4,
		  	       O_CH2_OCP_PUB_EN:1,
		  	       O_CH2_BIAS_BOOST:1,
		  	       Reserved1:1,
		  	       O_CH2_LDO_SINK:1,
		  	       O_CH1_LDO_OCP_PUB_EN:1,
		  	       O_CH1_BIAS_BOOST:1,
		  	       Reserved2:1,
		  	       O_CH1_LDO_SINK:1,
		  	       CH2_TEST_VMOD:1,
		  	       CH2_SET_DISCHG_40:1,
		  	       Ch2_SET_DISCHG_20:1,
		  	       O_CH2_PSRR:1,
		  	       CH1_TEST_VMOD:1,
		  	       CH1_SET_DISCHG_40:1,
		  	       CH1_SET_DISCHG_20:1,
		  	       O_CH1_PSRR:1,
		  	       Reserved3:2,
		  	       CH2_PLCOUT_LOW:1,
		  	       CH2_PLCOUT_LOW_AT_ENB:1,
		  	       Reserved4:2,
		  	       CH1_PLCOUT_LOW:1,
		  	       CH1_PLCOUT_LOW_AT_ENB:1;
	} BITS;
}PLC_REG_94;

typedef union
{
	  uint32_t DATA;
	  struct {
		  uint32_t O_CH1_ES_TRIM:8,
		  	       O_CH2_ES_TRIM:8,
		  	       Reserved1:5,
		  	       CH1_PLC_GAIN_SEL:2,
		  	       CS_SENS_GAIN_UP_L:1,
		  	       Reserved2:5,
		  	       CH2_PLC_GAIN_SEL:2,
		  	       CS_SENSE_GAIN_UP_R:1;
	} BITS;
}PLC_REG_98;

typedef union
{
	  uint32_t DATA;
	  struct {
		  uint32_t O_CH1_ISEN_VOS_TRIM:8,
		  	       O_CH2_ISEN_VOS_TRIM:8,
		  	       O_CH1_VOS_FINE_TRIM:8,
		  	       O_CH2_VOS_FINE_TRIM:8;
	} BITS;
}PLC_REG_9C;

typedef union
{
	  uint32_t DATA;
	  struct {
		  uint32_t O_SHORT_DET_LEV:1,
		  	       O_TEST_EN:1,
		  	       O_CH2_EN_VOS_FINE_TRIM:1,
		  	       Reserved1:1,
		  	       SEL_CNT_PLC:2,
		  	       O_CH1_EN_VOS_FINE_TRIM:1,
		  	       SEL_LCDATA_INV:1,
		  	       CH2_SS_dly:2,
		  	       CH2_OCP_dly:1,
		  	       SEL_OCP_LDO_CH2:1,
		  	       CH1_SS_dly:2,
		  	       CH1_OCP_dly:1,
		  	       SEL_OCP_LDO_CH1:1,
		  	       Reserved2:3,
		  	       CH2_CLAMP_OUT:1,
		  	       Reserved3:3,
		  	       CH1_CLAMP_OUT:1,
		  	       O_DHC_SEL:3,
		  	       O_CH2_CLAMP_OUT:1,
		  	       Reserved4:3,
		  	       O_CH1_LDO_SOFTSTART_EN:1;
	} BITS;
}PLC_REG_A0;

typedef union
{
	  uint32_t DATA;
	  struct {
		  uint32_t PLC_LDO_SET_FB_R:1,
		  	       PLC_LDO_SET_FB_L:1,
		  	       OCP_ACTION_R:1,
		  	       OCP_ACTION_L:1,
		  	       PLC_LDO_DISCHARGE_TIME_R:1,
		  	       PLC_LDO_DISCHARGE_TIME_L:1,
		  	       Reserved1:18,
		  	       LDO_OCP_SEL_R:3,
		  	       LDO_OCP_SEL_L:3,
		  	       Reserved2:2;
	} BITS;
}PLC_REG_AC;

typedef union
{
	  uint32_t DATA;
	  struct {
		  uint32_t EN_LDO_OCP_R:1,
		  	       EN_LDO_SCP_R:1,
		  	       EN_POGO_OUT_SCP_R:1,
		  	       LDO_OCP_PU_R:1,
		  	       EN_PLC_R:1,
		  	       DEMOD_READY_R:1,
		  	       Reserved1:2,
		  	       EN_LDO_OCP_L:1,
		  	       EN_LDO_SCP_L:1,
		  	       EN_POGO_OUT_SCP_L:1,
		  	       LDO_OCP_PU_L:1,
		  	       EN_PLC_L:1,
		  	       DEMOD_READY_L:1,
		  	       Reserved2:2,
		  	       SET_IPULSE_R:2,
		  	       SET_DEMOD_REF_R:2,
		  	       Reserved3:4,
			       SET_IPULSE_L:2,
			       SET_DEMOD_REF_L:2,
			       Reserved4:4;
	} BITS;
}PLC_REG_B0;


typedef struct
{
	PLC_REG_00       REG_00;
	PLC_REG_04       REG_04;
	PLC_REG_08       REG_08;
	PLC_REG_0C       REG_0C;
	PLC_REG_10       REG_10;
	PLC_REG_14       REG_14;
	PLC_REG_18       REG_18;
	PLC_REG_1C       REG_1C;
	PLC_REG_20       REG_20;
	PLC_REG_24       REG_24;
	PLC_REG_28       REG_28;
	PLC_REG_2C       REG_2C;
	PLC_REG_30       REG_30;
	PLC_REG_34       REG_34;
	PLC_REG_38       REG_38;
	PLC_REG_3C       REG_3C;
	PLC_REG_40       REG_40;
	PLC_REG_44       REG_44;
	PLC_REG_48       REG_48;
	PLC_REG_4C       REG_4C;
	PLC_REG_50       REG_50;
	PLC_REG_54       REG_54;
	PLC_REG_58       REG_58;
	PLC_REG_5C       REG_5C;
	PLC_REG_60       REG_60;
	PLC_REG_64       REG_64;
	PLC_REG_68       REG_68;
	PLC_REG_6C       REG_6C;
	PLC_REG_70       REG_70;
	PLC_REG_74       REG_74;
	PLC_REG_78       REG_78;
	PLC_REG_7C       REG_7C;
	PLC_REG_80       REG_80;
	PLCReserved_Type REG_84;
	PLCReserved_Type REG_88;
	PLCReserved_Type REG_8C;
	PLC_REG_90       REG_90;
	PLC_REG_94       REG_94;
	PLC_REG_98       REG_98;
	PLC_REG_9C       REG_9C;
	PLC_REG_A0       REG_A0;
	PLCReserved_Type REG_A4;
	PLCReserved_Type REG_A8;
	PLC_REG_AC       REG_AC;
	PLC_REG_B0       REG_B0;
}PLC_BLOCK_Type;

#endif

