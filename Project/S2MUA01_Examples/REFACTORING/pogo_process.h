#ifndef __POGO_PROCESS_H
#define __POGO_PROCESS_H

#define EARBUDS_ARRAY_INIT_CURR 0x1FF

#define JUDGE_LEVEL_POGO_ATTACHED 850	//mv
#define JUDGE_LEVEL_POGO_NORMAL_VOUT 4000
#define JUDGE_LEVEL_POGO_ABNORMAL_VOUT_L 1700
#define JUDGE_LEVEL_POGO_ABNORMAL_VOUT_H 2500
#define JUDGE_LEVEL_POGO_ABNORMAL_CNT 10

#define JUDGE_LEVEL_POGO_FULL     7   //mA
#define JUDGE_LEVEL_POGO_FULL_MIN 1
#define JUDGE_LEVEL_POGO_DETACH   2   //mA

#define JUDGE_CNT_POGO_ATTACHED  3
#define JUDGE_CNT_POGO_DETTACHED  5
#define JUDGE_CNT_POGO_FULL       10

#define POGO_LOOP_CNT       	3
#define PM_LOOP_CNT       		5

typedef enum {
	POGO_STATE_READY,
	POGO_STATE_LDO_MODE,
	POGO_STATE_ATTACHED,
	POGO_STATE_FULL,
} pogo_state_t;

struct bud_data {
	uint8_t		tag;
	uint8_t		full;
	uint16_t    curr_arr[20];
	uint8_t     pos;
	uint8_t     attach_cnt;
	uint8_t		ldo_status_cnt;
	uint8_t     full_cnt;
	uint8_t     detach_cnt;
	uint8_t		loop_delay;
};

struct pogo_data {
	uint8_t				pogo_attach;
	pogo_state_t		bud_state[2];
	struct bud_data		bud[2];
	uint8_t				loop_delay;
};

typedef pogo_state_t(*pogo_fp) (struct pogo_data *, uint8_t);

pogo_state_t pogo_state_ready(struct pogo_data *pogo, uint8_t dir_shift);
pogo_state_t pogo_state_ldo_mode(struct pogo_data *pogo, uint8_t dir_shift);
pogo_state_t pogo_state_attached(struct pogo_data *pogo, uint8_t dir_shift);
pogo_state_t pogo_state_full(struct pogo_data *pogo, uint8_t dir_shift);


void SetEarburdsPOGO1P5V(void);

uint8_t pogo_state_engine(struct pogo_data *pogo, uint8_t pogo_attach);
struct pogo_data *pogo_init(void);
#endif /*__POGO_PROCESS_H */
