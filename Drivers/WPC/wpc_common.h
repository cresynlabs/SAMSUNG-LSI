#ifndef __WPC_COMMON_H
#define __WPC_COMMON_H

void wpc_cb_vout_on(uint8_t *pdata);
void wpc_cb_charger_mode(uint8_t *pdata);
void wpc_cb_can_send_plc(uint8_t *pdata);
void sysreg_drv_seten_wpt(void);

#endif
