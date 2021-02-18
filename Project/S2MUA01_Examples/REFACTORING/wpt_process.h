#ifndef __WPT_PROCESS_H
#define __WPT_PROCESS_H

struct wpt_data {
	char			WPCVoutOn;
	char			WPCVoutOnFlag;
	char			WPCVoutOnTick;
	
	char			WPCTXIDSend;
	char			WPCTXIDCnt;
	char			WPCTXIDTick;
	char			WPCTXID;
	uint32_t		WPCPingTick;

	uint8_t			WPTStatus;

	float			fCur_CC;
	uint8_t			VRectStatus;
	uint8_t			VRectOldStatus;
	uint8_t			CS100Cnt;
	uint32_t		CS100Tick;
	uint8_t			WPTAutoZeroStart;
	uint32_t		WPTAutoZeroStartTick;
	uint32_t		WPTAutoZeroStepTick;
	uint8_t			WPTAutoZeroCalFlag;
	uint8_t			WPTAutoZeroOldCurSet;
	uint8_t			uWPTdelayFlag;

	float			VBAT;
	uint8_t			VBUS;
};

void S2MUA01VoutOn(void);
void S2MUA01SetWPCTXID(uint8_t ucTXID);
void WPTProcess(struct wpt_data *wpt);
void wpt_auto_zero(struct wpt_data *wpt);
struct wpt_data *wpt_main_init(void);
#endif /* __WPT_PROCESS_H */
