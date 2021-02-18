/*
******************************************************************************
* @file    uart_drv.c
* @author  Power Device Team
* @version V1.0.0
* @date    09-June-2016
* @brief
******************************************************************************
*/
#include "cm0pikmcu.h"
#include "uart_drv.h"
#include "common_drv.h"

#include <stdlib.h>
#include <stdarg.h>
#include <string.h>

void uart_drv_put_char(char c)
{
	while (UART.UARTFR.BITS.TXFF != 0);
	UART.UARTDR.DATA = c;
}

void uart_drv_init(void)
{
	NVIC_EnableIRQ(IRQ05_UART_TXD);

	UART.UARTIMSC.BITS.TXIM = 0x01; /* TX interrupt mask */
	UART.UARTIMSC.BITS.RXIM = 0x01; /* RX interrupt mask */
	UART.UARTIMSC.BITS.RTIM = 0x01; /* RT interrupt mask */

	/* BRDI + BRDF = CLK/(16*BAUD_RATE+1)
	 * Example) Baud rate 460800
	 * BRDI + BRDF = 2.170
	 * BRDF = (0.170 * 2^6) + 0.5 = 11.388 */
	UART.UARTIBRD.BITS.BAUD_DIVINT = 0X08; /* baudrate = 115200 */
	UART.UARTFBRD.BITS.BAUD_DIVFRAC = 0X2C;
	//BOOTCON.GPIO_PEN.BITS.GP7_UART_TX_PEN=1;	// UART TX CMOS SET

	/* 460800
	UART.UARTIBRD.BITS.BAUD_DIVINT	= 0X02; // baudrate = 460800
	UART.UARTFBRD.BITS.BAUD_DIVFRAC = 0X0B;
	*/

	UART.UARTCR.BITS.RXE = 0x01; /* RX enalbe */
	UART.UARTCR.BITS.TXE = 0x01; /* TX enalbe */

	UART.UARTLCR_H.BITS.FEN = 0x01; /* fifo enable */
	UART.UARTLCR_H.BITS.WLEN = 0x03; /* Word length */


	UART.UARTCR.BITS.UARTEN = 0x01; /* UART enable */
}

void boot_uart_txd_irqhandler(void)
{
    NVIC_ClearPendingIRQ(IRQ05_UART_TXD);

	/* TX */
	if (UART.UARTMIS.BITS.TXMIS)
	{
		UART.UARTICR.BITS.TXIC = 0x1;
		return;
	}
	/* RX */
	if (UART.UARTMIS.BITS.RTMIS)
	{
		UART.UARTICR.BITS.RTIC = 0x1;
		return;
	}
}

