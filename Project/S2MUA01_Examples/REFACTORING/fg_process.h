#ifndef __FG_PROCESS_H
#define __FG_PROCESS_H

struct fg_data {
	float soc;
	float temp;
	float current;
	float vbat;
	float soc_r;
};

void fuelgauge_poll(struct fg_data *fg);
struct fg_data *fg_init(void);

#endif /* __FG_PROCESS_H */
