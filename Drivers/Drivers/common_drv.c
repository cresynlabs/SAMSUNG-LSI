#include "cm0pikmcu.h"
#include "sc_drv.h"
#include "common_drv.h"
#include "main.h"

/* set UART TX output source select
 * set UART RX input source select
 * set PORT to CMOS mode */
void gpio_drv_set_to_uart(void)
{
	GPIO_SOURCE_SEL_Type gpio_src_sel;

	gpio_src_sel.DATA = BOOTCON.GPIO_SRC_SEL.DATA;

	gpio_src_sel.BITS.SRC_SEL_IN_UART = 1;
	gpio_src_sel.BITS.SRC_SEL_OUT_UART = 1;

	BOOTCON.GPIO_SRC_SEL.DATA = gpio_src_sel.DATA;
}

/* set enable mode : CMOS or Open drain */
void gpio_drv_set_enable(uint8_t port, uint8_t mode)
{
	switch(port)
	{
	case GPIO_PORT1:
		BOOTCON.GPIO_PEN.BITS.GP1_T_D1_PEN = mode;
		break;
	case GPIO_PORT2:
		BOOTCON.GPIO_PEN.BITS.GP2_T_D2_PEN = mode;
		break;
	case GPIO_PORT3:
		BOOTCON.GPIO_PEN.BITS.GP3_T_D3_PEN = mode;
		break;
	case GPIO_PORT4:
		BOOTCON.GPIO_PEN.BITS.GP4_T_D4_PEN = mode;
		break;
	case GPIO_PORT5:
		BOOTCON.GPIO_PEN.BITS.GP5_T_D5_PEN = mode;
		break;
	case GPIO_PORT6:
		BOOTCON.GPIO_PEN.BITS.GP6_T_D6_PEN = mode;
		break;
	}
}

/* set GPIO port to data value (High or low) */
void gpio_drv_set_output_data(uint8_t port, uint8_t data)
{
	switch(port)
	{
	case GPIO_PORT1:
		BOOTCON.GPIO_OUT.BITS.GPIO_OUTx_1 = data;
		break;
	case GPIO_PORT2:
		BOOTCON.GPIO_OUT.BITS.GPIO_OUTx_2 = data;
		break;
	case GPIO_PORT3:
		BOOTCON.GPIO_OUT.BITS.GPIO_OUTx_3 = data;
		break;
	case GPIO_PORT4:
		BOOTCON.GPIO_OUT.BITS.GPIO_OUTx_4 = data;
		break;
	case GPIO_PORT5:
		BOOTCON.GPIO_OUT.BITS.GPIO_OUTx_5 = data;
		break;
	case GPIO_PORT6:
		BOOTCON.GPIO_OUT.BITS.GPIO_OUTx_6 = data;
		break;
	}
}

/* return  GPIO port to data value (High or low) */
uint8_t gpio_drv_get_output_data(uint8_t port)
{
	switch(port)
	{
	case GPIO_PORT1:
		return BOOTCON.GPIO_OUT.BITS.GPIO_OUTx_1;
	case GPIO_PORT2:
		return BOOTCON.GPIO_OUT.BITS.GPIO_OUTx_2;
	case GPIO_PORT3:
		return BOOTCON.GPIO_OUT.BITS.GPIO_OUTx_3;
	case GPIO_PORT4:
		return BOOTCON.GPIO_OUT.BITS.GPIO_OUTx_4;
	case GPIO_PORT5:
		return BOOTCON.GPIO_OUT.BITS.GPIO_OUTx_5;
	case GPIO_PORT6:
		return BOOTCON.GPIO_OUT.BITS.GPIO_OUTx_6;
	}
	return 0;
}


/* return data of GPIO port(High or low) */
uint8_t gpio_drv_get_input_data(uint8_t port)
{
	switch(port)
	{
	case GPIO_PORT1:
		return BOOTCON.GPIO_IN.BITS.GPIO_INx_1;
	case GPIO_PORT2:
		return BOOTCON.GPIO_IN.BITS.GPIO_INx_2;
	case GPIO_PORT3:
		return BOOTCON.GPIO_IN.BITS.GPIO_INx_3;
	case GPIO_PORT4:
		return BOOTCON.GPIO_IN.BITS.GPIO_INx_4;
	case GPIO_PORT5:
		return BOOTCON.GPIO_IN.BITS.GPIO_INx_5;
	case GPIO_PORT6:
		return BOOTCON.GPIO_IN.BITS.GPIO_INx_6;
	}
	return 0;
}

uint8_t hall_drv_get_hall_status(void)
{
	return SYSREG.DET_POGO.BITS.A2D_CM_HOLL_INT_DB;
}

/* VOUT POGO ADC Enable */
void pm_drv_set_vpogo_co(uint8_t data)
{
	PM.REG_4C.BITS.VPOGOLCO = data;
	PM.REG_4C.BITS.VPOGORCO = data;
}

/* IOUT POGO ADC Enable */
void pm_drv_set_ipogo_co(uint8_t data)
{
	PM.REG_4C.BITS.IPOGOLCO = data;
	PM.REG_4C.BITS.IPOGORCO = data;
}

/* Return POGO VOUT */
uint16_t pm_drv_get_vpogo(uint8_t dir)
{
	uint16_t vout;

	if (dir == LEFT)
		vout = PM.REG_1C.BITS.VADC_POGOL;
	else
		vout = PM.REG_20.BITS.VADC_POGOR;
	return (uint16_t)(vout * 0.48828f);
}

/* Return POGO IOUT */
uint16_t pm_drv_get_ipogo(uint8_t dir)
{
	uint16_t vout;

	if (dir == LEFT)
		vout = PM.REG_1C.BITS.IADC_POGOL;
	else
		vout = PM.REG_20.BITS.IADC_POGOR;
	return (uint16_t)(vout * 0.48828f);
}


void sysreg_drv_seten_det_pogo(uint8_t dir, uint8_t data)
{
	if (dir == LEFT)
		SYSREG.DET_POGO.BITS.REG_EN_DET_POGO_L = data;
	else
		SYSREG.DET_POGO.BITS.REG_EN_DET_POGO_R = data;

}

void sysreg_drv_seten_det_reset_pogo(uint8_t dir)
{
	if (dir == LEFT)
		SYSREG.DET_POGO.BITS.REG_DET_POGO_RESET_L = 1;
	else
		SYSREG.DET_POGO.BITS.REG_DET_POGO_RESET_R = 1;
}

void sysreg_drv_set_lpm(uint8_t data)
{
	SYSREG.ANALOG_LPM_MODE.BITS.Analog_LPM_MODE = data;
}

void bootcon_drv_set_shutdown_mode(uint8_t data)
{
	BOOTCON.SHUTDN_MODE.BITS.EN_SHUT_DOWN_MODE = data;
}

void direct_address_access(uint32_t address, uint8_t data, uint8_t cal)
{
	volatile uint8_t *addr;

	addr = (volatile uint8_t *)address;
	if (cal == AND)
		*addr = (*addr) & data;
	else
		*addr = (*addr) | data;
}

void bootcon_drv_set_shipmode(void)
{
	BOOTCON.COMM_1P8.BITS.D2A_CM_LDO_1P8_1 = BOOTCON.COMM_1P8.BITS.D2A_CM_LDO_1P8_1 | 0x02;
	sysdelay_ms(2);
	BOOTCON.SHUTDN_MODE.BITS.EN_SHUT_DOWN_MODE = 1;
}


/************************************************************
  WATCH DOG TIMER
   MODE
	- 0 = Interrupt Mode
	- 1 = Reset Mode
   WDTVAL
    - Timout value (refer datasheet)
************************************************************/

void sysreg_drv_set_wdt(void)
{
	TIMER.WDTCON.BITS.MODE = 0;	    /* Interrupt mode */
	TIMER.WDTCON.BITS.WDTVAL = 0x1000;  /* Timeout value 2330ms */
	TIMER.WDTCON.BITS.EN = 1;       /* Enable */
}
void sysreg_drv_set_wdt_reset(void)
{
	TIMER.WDTCON.BITS.RST = 1;
}

void boot_wdt_irqhandler(void)
{
	DB("boot_wdt_irqhandler \r\n");
    NVIC_ClearPendingIRQ(IRQ07_WDT);
	BOOTCON.ANA_COMM2.BITS.D2A_HW_RESET = 1;

    return;
}

void sysreg_drv_set_wdt_disable(void)
{
	TIMER.WDTCON.BITS.EN = 0;
}


void comm_memset(uint8_t *pdest, uint8_t data, uint8_t nsize)
{
	uint16_t i;

	for (i = 0; i < nsize; i++)
		pdest[i] = data;
}

void comm_memset16(uint16_t *pdest, uint16_t data, uint8_t nsize)
{
	uint16_t i;

	for (i = 0; i < nsize; i++)
		pdest[i] = data;
}

void comm_memset16_p2p(uint16_t *pdest, uint16_t *psrc, uint8_t nsize)
{
	uint16_t i;

	for (i = 0; i < nsize; i++)
		pdest[i] = psrc[i];
}


void comm_memcpy(uint8_t *pdest, uint8_t *psource, uint8_t nsize)
{
	int i;

	for (i = 0; i < nsize; i++)
		pdest[i] = psource[i];
}

uint8_t check_timer(uint32_t time, uint32_t timer)
{
	if (sys_get_tick() - time > timer)
		return TRUE;
	else
		return FALSE;
}
