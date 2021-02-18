#include <stdlib.h>
#include "cm0pikmcu.h"

#include "main.h"
#include "pm_process.h"

#include "PLC.h"
#include "common_drv.h"


void pm_poll(struct s2mua01_data *main_data)
{
	uint16_t vout, iout, i;

	pogo_state_t state;

	for (i = LEFT_SHIFT; i <= RIGHT_SHIFT; i++)
	{
		if(plc_get_plc_mode(i+1) == PLC_MODE_OFF)
		{
			vout=pm_drv_get_vpogo(i+1);

			if(vout<JUDGE_LEVEL_POGO_ATTACHED)
			{
				DB("pm_poll(vout<JUDGE_LEVEL_POGO_ATTACHED) dir(%d) vout %d\r\n", i+1, vout);
				if(i == LEFT_SHIFT)
				{
					main_data->loop_delay_pm++;
					if (main_data->loop_delay_pm == PM_LOOP_CNT)
					{
						main_data->loop_delay_pm=0;
						main_data->event_flag |= POGOL_ATTACH_WAIT_EVENT;
					}
				}
				else
					main_data->event_flag |= POGOR_ATTACH_WAIT_EVENT;
			}
		}
		else
		{
			state = main_data->pogo->bud_state[i];
			vout=pm_drv_get_vpogo(i+1);
			if(state != POGO_STATE_READY)
				DB("pm_poll(!PLC_MODE_OFF) dir(%d) vout %d\r\n", i+1, vout);
		}
	}
}
