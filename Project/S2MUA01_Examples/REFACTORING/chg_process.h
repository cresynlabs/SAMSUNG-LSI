#ifndef __CHG_PROCESS_H
#define __CHG_PROCESS_H

typedef enum {
	CHGIN,
	WCIN,
	BATT,
} chg_status_t;

struct charger_data {
	uint8_t chgin_status;
	uint8_t wcin_status;
};

void charger_poll(struct charger_data *charger, uint32_t *flag);
struct charger_data *charger_init(void);

#endif /*__CHG_PROCESS_H */
