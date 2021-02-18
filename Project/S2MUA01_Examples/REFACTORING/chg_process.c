#include <stdlib.h>
#include "cm0pikmcu.h"

#include "main.h"
#include "sc_drv.h"

void charger_poll(struct charger_data *charger, uint32_t *flag)
{
	uint8_t status;
	 uint8_t ret;

	/* check chgin status */
	// chg in(usb 전원 on 되있는지 상태 판단할 수 있는 레지스터 값 읽기)
	status = sc_drv_get_chgin_status();

	switch (status) {
	case CHGIN_OVER_OVLO:
	case CHGIN_IN_CURRENT_IS_LIMITED_REGUL:
	case CHGIN_IS_VALID:
		ret = TRUE;
		break;
	default:
		ret = FALSE;
		break;
	}
	
   //chgin_status 상태가 변경될시에 진입하여 event_flag 상태를 바꿔줌 
	if (charger->chgin_status != ret) {
		charger->chgin_status = ret;
		if (ret)
			*flag |= CHGIN_ON_EVENT;
		else
			*flag |= CHGIN_OFF_EVENT;
	}
	
	/* check wcin status */
	//  in(무선충전 전원 on 되있는지 상태 판단할 수 있는 레지스터 값 읽기)
	status = sc_drv_get_wcin_status();

	switch (status) {
	case WCIN_OVER_OVLO:
	case WCIN_IN_CURRENT_IS_LIMITED_REGUL:
	case WCIN_IS_VALID:
		ret = TRUE;
		break;
	default:
		ret = FALSE;
		break;
	}

	if (charger->wcin_status != ret) {
		if (ret)
			*flag |= WCIN_ON_EVENT;
		else
			*flag |= WCIN_OFF_EVENT;
	}

	/* check whether charging is full */
	//usb 충전 완료상태 판단할 수 있는 레지스터 값 읽기 
	if (sc_drv_get_charge_done())
	{
//		printf("CHG_DONE_EVENT\r\n");
		*flag |= CHG_DONE_EVENT;
	}
}

struct charger_data *charger_init(void)
{
	struct charger_data *charger;
	uint8_t ucTrim_WCIN_OVP;

   // charger 주소 값 설정(메모리 할당)
	charger = malloc(sizeof(struct charger_data));
	if (!charger) {
		printf("%s, failed to allocate charger driver data\r\n", __func__);
		return charger;
	}

	charger->chgin_status = 0;
	charger->wcin_status = 0;

	set_scp_flag_vref();
	/* W/A  - ISSUE. PRE to chg, peak IBAT is 1A. by skcho 0905 */
	sc_drv_set_vsysmin(VSYSMIN_3P0V);
	sc_drv_set_1st_topoff(TOPOFF_40MA);
	sc_drv_set_2nd_topoff(TOPOFF_30MA);

	sc_drv_set_charger_off_by_2nd_topoff(0x08);

	/* Disable Auto restart
	   Disable Timer fault
	   CV mode stablization Walk around by skcho 0917 */
	sc_drv_set_auto_chg_restart(0);
	sc_drv_set_en_timer_fault(0);

	sc_drv_set_reg_mode(BUCK_MODE);
	
	SC.REG_34.BITS.T_EN_CVR = 3;
	SC.REG_34.BITS.T_EN_CCR = 3;
	SC.REG_34.BITS.T_EN_ICR = 3;
	SC.REG_34.BITS.T_EN_IVR = 3;
	SC.REG_7C.BITS.MIN_DIF_INC = 2;

	SC.REG_94.BITS.Time_SET_IBAT_SS = 1;

	SC.REG_8C.BITS.OVP_SW_WAIT_TIME = 2;

	sc_drv_set_switch_freq(SWITCH_FREQ_1M);

	ucTrim_WCIN_OVP = SC.REG_6C.BITS.Trim_WCIN_OVP;

	if(ucTrim_WCIN_OVP <= 41)
		SC.REG_6C.BITS.Trim_WCIN_OVP += 22;
	else
		SC.REG_6C.BITS.Trim_WCIN_OVP = 0x3B;

	SC.REG_84.BITS.SET_LCELL_R = 3;

	sc_drv_set_uvlo_debounce_time();

	return charger;
}
