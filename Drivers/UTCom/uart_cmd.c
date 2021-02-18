#include "cm0pikmcu.h"
#include "System.h"
#include "uart_cmd.h"
#include "sc_drv.h"
#include "common_drv.h"
#include "main.h"
#include "fg_drv.h"
#include "uart_drv.h"

uint8_t gucCmdArray[10][UARTCMD_MAXLENGTH];

char UARTcmdLogStatus(void)
{
	return 0;
}
