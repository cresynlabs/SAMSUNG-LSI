#include <stdlib.h>
#include "cm0pikmcu.h"

#include "main.h"
#include "common_drv.h"
#include "PLC.h"
#include "sc_drv.h"
//#include "pogo_process.h"

const pogo_fp pogo_state_machine[] = {
	pogo_state_ready,
	pogo_state_ldo_mode,
	pogo_state_attached,
	pogo_state_full,
};

void set_pogo_detection(uint8_t dir)
{
	//if((dir == LEFT) && (SYSREG.DET_POGO.BITS.REG_EN_DET_POGO_L==0))
	{
		//plc_set_plc_mode(dir, PLC_MODE_OFF);
		sysreg_drv_seten_det_reset_pogo(dir);

		delay_for_stablization();//need 50us delay

		sysreg_drv_seten_det_pogo(dir,ON);
		plc_set_plc_mode(dir, PLC_MODE_OFF);
	}
}

void set_pogo_off(uint8_t dir)
{
	sysreg_drv_seten_det_pogo(dir,OFF);
	plc_set_plc_mode(dir, PLC_MODE_OFF);
	sysreg_drv_seten_det_reset_pogo(dir);

	//sc_drv_set_reg_mode(BUCK_MODE);
}

void set_earbud_pogo_1p5v(uint8_t dir)
{
	// Set POGO R/L to about 1.5V
	plc_set_plc_mode(LEFT, PLC_MODE_OFF);
	plc_set_plc_mode(RIGHT, PLC_MODE_OFF);

	// VOUT, IOUT ADC Enable
	pm_drv_set_vpogo_co(ON);
	pm_drv_set_ipogo_co(ON);
}

void pogo_moving_avgcnt(struct pogo_data *pogo, uint8_t dir_shift)
{
	uint16_t iout;
	uint8_t i;
	uint8_t dir = 1 << dir_shift;
	pogo_state_t state = pogo->bud_state[dir_shift];

	iout = pm_drv_get_ipogo(dir);

	pogo->bud[dir_shift].curr_arr[pogo->bud[dir_shift].pos++] = iout;
	if (pogo->bud[dir_shift].pos >= 10)
		pogo->bud[dir_shift].pos = 0;

	DB_C("\t\t pogo_moving_avgcnt: ");

	for (i = 0; i < JUDGE_CNT_POGO_DETTACHED; i++)
	{
		if (pogo->bud[dir_shift].curr_arr[i] < JUDGE_LEVEL_POGO_FULL
				&& pogo->bud[dir_shift].curr_arr[i] > JUDGE_LEVEL_POGO_DETACH)
			pogo->bud[dir_shift].full_cnt++;
		if (pogo->bud[dir_shift].curr_arr[i] < JUDGE_LEVEL_POGO_DETACH)
			pogo->bud[dir_shift].detach_cnt++;
		DB_C("%2d ", pogo->bud[dir_shift].curr_arr[i]);
	}
	DB_C(" / %d\r\n", pogo->bud[dir_shift].pos);
	DB_C("state(%d) - full_cnt %d detach_cnt %d\r\n",	state, pogo->bud[dir_shift].full_cnt, pogo->bud[dir_shift].detach_cnt);

}

pogo_state_t pogo_state_ready(struct pogo_data *pogo, uint8_t dir_shift)
{
	uint8_t dir = 1 << dir_shift;
	pogo_state_t state = pogo->bud_state[dir_shift];

	if (pogo->pogo_attach & dir)
	{
		DB("pogo_state_ready(dir(%d), state(%d)) \r\n", dir, state);
		plc_set_plc_mode(dir, PLC_MODE_LDO);
		sc_drv_set_bst_voltage(PLC_LDO_BST_4_7V);
		plc_set_plc_output(dir, PLC_LDO_4_6V);
		/* TODO */
		/* PLC_init(dir); */

		/* when attached, notify to the other Bud
		if (PLC_get_PLC_MODE(dir)!=PLC_MODE_OFF)
			PLC_msg_Q(dir, PLC_HDR_STAT, 1, PLC_CDL_STAT_DOUBLE_BUD);*/

		pogo->bud[dir_shift].ldo_status_cnt = 0;
		return POGO_STATE_LDO_MODE;
	}

	return state;
}

pogo_state_t pogo_state_ldo_mode(struct pogo_data *pogo, uint8_t dir_shift)
{
	pogo_state_t state = pogo->bud_state[dir_shift];
	uint16_t vout, iout;
	uint8_t dir = 1 << dir_shift;

	vout=pm_drv_get_vpogo(dir);
	iout=pm_drv_get_ipogo(dir);

	//DB("pogo_state_ldo_mode(dir(%d), state(%d)) vout(%d) iout(%d) attach_cnt(%d)\r\n",
	//	dir, state, vout, iout, pogo->bud[dir_shift].attach_cnt);

	pogo->bud[dir_shift].ldo_status_cnt++;

	if(pogo->bud[dir_shift].ldo_status_cnt > 10)
	{
		pogo->pogo_attach &= ~(1 << dir_shift);
		/*set pogo detection mode*/
		if(plc_get_plc_mode(dir)==PLC_MODE_LDO)
			set_pogo_detection(dir);
		return POGO_STATE_READY;
	}
	if (vout > JUDGE_LEVEL_POGO_NORMAL_VOUT && iout > JUDGE_LEVEL_POGO_DETACH)
		pogo->bud[dir_shift].attach_cnt++;
	else
		pogo->bud[dir_shift].attach_cnt = 0;

	if (pogo->bud[dir_shift].attach_cnt >= JUDGE_CNT_POGO_ATTACHED)
	{
		DB("pogo_state_ldo_mode(attach_cnt >= JUDGE_CNT_POGO_ATTACHED) (dir(%d), state(%d)) \r\n", dir, state);
		pogo->bud[dir_shift].tag = TRUE;
		pogo->bud[dir_shift].detach_cnt = 0;
		pogo->bud[dir_shift].ldo_status_cnt = 0;
		return POGO_STATE_ATTACHED;
	}

	return state;
}

pogo_state_t pogo_state_attached(struct pogo_data *pogo, uint8_t dir_shift)
{
	pogo_state_t state = pogo->bud_state[dir_shift];
	uint8_t dir = 1 << dir_shift;

	pogo_moving_avgcnt(pogo, dir_shift);

	/* full */
	if (pogo->bud[dir_shift].full_cnt >= JUDGE_CNT_POGO_FULL)
	{
		DB("pogo_state_attached(full) (dir(%d), state(%d)) \r\n", dir, state);
		pogo->bud[dir_shift].full = TRUE;
		return POGO_STATE_FULL;
	}

	/* detach */
	if (pogo->bud[dir_shift].detach_cnt >= JUDGE_CNT_POGO_DETTACHED)
	{
		pogo->pogo_attach &= ~(1 << dir_shift);

		pogo->bud[dir_shift].detach_cnt = 0;
		pogo->bud[dir_shift].tag = FALSE;

		/* Init POGO current data */
		pogo->bud[dir_shift].pos = 0;
		pogo->bud[dir_shift].full = FALSE;
		comm_memset16(pogo->bud[dir_shift].curr_arr, EARBUDS_ARRAY_INIT_CURR, 20);

		/*set pogo detection mode*/
		if(plc_get_plc_mode(dir)==PLC_MODE_LDO)
			set_pogo_detection(dir);

		DB("pogo_state_attached(detach) (dir(%d), state(%d), pogo_attach(%d)) \r\n", dir, state, pogo->pogo_attach);
		return POGO_STATE_READY;
	}

	return state;
}

pogo_state_t pogo_state_full(struct pogo_data *pogo, uint8_t dir_shift)
{
	pogo_state_t state = pogo->bud_state[dir_shift];
	uint8_t dir = 1 << dir_shift;

	pogo_moving_avgcnt(pogo, dir_shift);

	if (pogo->bud[dir_shift].detach_cnt >= JUDGE_CNT_POGO_DETTACHED)
	{
		pogo->pogo_attach &= ~(1 << dir_shift);

		pogo->bud[dir_shift].detach_cnt = 0;
		pogo->bud[dir_shift].tag = FALSE;

		/* Init POGO current data */
		pogo->bud[dir_shift].pos = 0;
		pogo->bud[dir_shift].full = FALSE;
		comm_memset16(pogo->bud[dir_shift].curr_arr, EARBUDS_ARRAY_INIT_CURR, 20);

		/*set pogo detection mode*/
		if(plc_get_plc_mode(dir)==PLC_MODE_LDO)
			set_pogo_detection(dir);

		DB("pogo_state_full(detach) (dir(%d), state(%d), pogo_attach(%d)) \r\n", dir, state, pogo->pogo_attach);
		return POGO_STATE_READY;
	}

	return state;
}

uint8_t pogo_state_engine(struct pogo_data *pogo, uint8_t pogo_attach)
{
	int i = 0;
	pogo_state_t next_state;
	pogo->pogo_attach = pogo_attach;

	if (pogo->loop_delay == POGO_LOOP_CNT)
		pogo->loop_delay = 0;
	else
	{
		pogo->loop_delay++;
		return pogo_attach;
	}

	for (i = LEFT_SHIFT; i <= RIGHT_SHIFT; i++)
	{
		while (1)
		{
			next_state = pogo_state_machine[pogo->bud_state[i]](pogo, i);
			if (next_state == pogo->bud_state[i])
				break;

			pogo->bud_state[i] = next_state;
			pogo->bud[i].attach_cnt = 0;
		}
	}

	return pogo->pogo_attach;
}

struct pogo_data *pogo_init(void)
{
	struct pogo_data *pogo;

	int i = 0;
	uint8_t dir;

	pogo = malloc(sizeof(struct pogo_data));
	if (!pogo)
	{
		printf("%s, failed to allocate POGO driver data\r\n", __func__);
		return pogo;
	}

	pogo->loop_delay = 0;
	pogo->bud_state[0] = POGO_STATE_READY;
	pogo->bud_state[1] = POGO_STATE_READY;

	comm_memset((uint8_t *)pogo->bud, 0, sizeof(struct bud_data) * 2);

	for (i = LEFT_SHIFT; i <= RIGHT_SHIFT; i++)
	{
		dir = 1 << i;
		//set_earbud_pogo_1p5v(dir);

		set_pogo_detection(dir);

		pogo->bud[i].detach_cnt = 0;
	}

	/* Enable ADC of POGO */
	pm_drv_set_vpogo_co(ON);
	pm_drv_set_ipogo_co(ON);

	return pogo;
}
