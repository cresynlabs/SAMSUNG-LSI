#include "cm0pikmcu.h"
#include "common_drv.h"
#include "sc_drv.h"
#include "wpc.h"
#include "PLC.h"

void wpc_cb_vout_on(uint8_t *pdata)
{
	plc_t *plc = get_memory_addr();

	printf("cb vout on\r\n");
//	S2MUA01VoutOn();

	sc_drv_set_reg_mode(CHG_MODE);
	plc[0].wpt_in = TRUE;
	//printf("plc[0].wpt_in (%d), plc addr(%#x)\r\n", plc[0].wpt_in, plc);	
	
}

void wpc_cb_charger_mode(uint8_t *pdata)
{
//	printf("cb charger mode\r\n");
}

void wpc_cb_can_send_plc(uint8_t *pdata)
{
	//printf("can send plc\r\n");
	plc_tx_process(get_memory_addr());
}

void sysreg_drv_seten_wpt(void)
{
	WPT_EN_Type wpt_en;

	wpt_en.DATA = SYSREG.WPT_EN.DATA;

	wpt_en.BITS.REG_EN_WPT_UVLO_MCU = 1;
	wpt_en.BITS.REG_SEL_EN_WPT_UVLO_MCU = 1;

	SYSREG.WPT_EN.DATA = wpt_en.DATA;
}

//int wpc_irq_cbtx_data_rcv(uint8_t *pData)
//{
//	#ifdef WPC_UART_DEBUG
//	printf("WPC IRQ TX Data 0x%x 0x%x 0x%x\r\n", pData[0], pData[1], pData[2]);
//	#endif
//	return 0;
//}

//	int WPCIRQCBMisAlign(uint8_t *pData)
//	{
//		#ifdef WPC_UART_DEBUG
//		printf("WPC IRQ Mis Align\r\n");
//		#endif
//		WPCSendPPP(eWPC_APCOM_MIS_ALIGN, 0xFF);
//		return 0;
//	}

//int wpc_irq_cbchg_mode(uint8_t *pData)
//{
//	#ifdef WPC_UART_DEBUG
//	printf("WPC IRQ CHG MODE\r\n");
//	#endif
//	sc_drv_set_reg_mode(BUCK_MODE); sysdelay_us(5);
//	sc_drv_set_reg_mode(CHG_MODE);
//	return 0;
//}

//int wpc_irq_cbvout_gd(uint8_t *pData)
//{
//	#ifdef WPC_UART_DEBUG
//	printf("WPC IRQ VoutGD\r\n");
//	#endif
//	printf("WPC IRQ VoutGD\r\n");
//
//	S2MUA01VoutOn();
//
//	return 0;
//}

//int wpc_irq_cbtxid(uint8_t *pData)
//{
//
//	S2MUA01SetWPCTXID(pData[0]);
//
//	return 0;
//}


