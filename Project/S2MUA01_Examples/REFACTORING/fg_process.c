#include <stdlib.h>
#include "cm0pikmcu.h"

#include "main.h"
#include "fg_drv.h"

float fg_get_soc()
{
	float soc;
	soc = fg_drv_get_soc_r();
	soc *= 1.01317f;
/*
	if(soc > 1.0f) {
		soc = 1.0f;
		fg_drv_set_soc_i2c(100.0f);
		fg_drv_set_restart();
	}
*/
	return soc;
}

void fuelgauge_poll(struct fg_data *fg)
{
	fg->soc = fg_get_soc();
	fg->temp = fg_drv_get_temp();
	fg->vbat = fg_drv_get_vbat();
	fg->current = fg_drv_get_cur_cc();
}

//inline void fg_start()
void fg_start()
{
	/* FG ADC is default disable State.
	You have to enable to calculate SOC, Voltage, Current */

	fg_drv_set_if_en(3);			/* Fuelgauge I2C Enable */

	/* Set Battery Parameter,
	this will be guilded by SAMSUNG */
	fg_drv_set_ocv_soc_rs_lut();

	fg_drv_set_batcap_ocv(0x03D4);	/* set BATCAP_OCV */
	fg_drv_set_batcap(0x0093);		/* set BAT CAP */

	fg_drv_set_batcap_ocv_en(1);	/* BATCAP OCV enable */

	fg_drv_set_edv(0x67);			/* Set EDV Voltage : 2.8V */

	fg_drv_set_init_done();			/* mark FG Init Done */

	fg_drv_set_start();			/* FG start */

	sysdelay_ms(100);			/* must wait for operating FG */

	fg_drv_set_if_en(0);			/* Fuelgauge I2C Disable */
}

struct fg_data *fg_init(void)
{
	struct fg_data *fg;

	fg = malloc(sizeof(struct fg_data));
	if (!fg)
	{
		printf("%s, failed to allocate FG driver data\r\n", __func__);
		return fg;
	}

	fg_start();

	fg_drv_set_voltage_mode(FALSE);	/* Set FG CC Mode */

	/* INC OK EN Disable,
	 * INC OK EN Mean that allow increasing SOC during discharging
	 * It is usually used after charge done */
	fg_drv_set_inc_ok_en(FALSE);

	return fg;
}
