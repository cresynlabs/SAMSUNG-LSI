#ifndef _UART_CMD_H_
#define _UART_CMD_H_

#include <stdlib.h>
#include "cm0pikmcu.h"
#define FW_TN_VERSION	    "FV00_R180CXTC1"

#define UART_CMD_STR_LEN 5
#define UARTCMD_MAXLENGTH 40

extern char UARTLogWPTADCStatus;

void UARTCmdSetTNCommand(uint8_t data);
uint8_t UARTCmdGetTNCommand(void);
//	void UARTCmdAlllog(void);
//	void UARTCmdSOCStart(void);
//	void UARTCmdSOCLog(void);
char UARTcmdLogStatus(void);
char UARTcmdLogStatus2(void);
void UARTCmdProcess(void);
uint16_t UARTCmdGetVoutValue(void);

//void UARTParssingGUI(uint8_t cmd);
//	void UARTCmdSendPPP(int argc, char *argv[]);
//	void UARTCmdSendCS(int argc, char *argv[]);
//	void UARTCmdSendEPT(int argc, char *argv[]);
//	void UARTCmdSendPHM(int argc, char *argv[]);
//void UARTCmdTemp(int argc, char *argv[]);

//	void UARTCmdBlock(int argc, char *argv[]);
//	void UARTCmdNormal(int argc, char *argv[]);
//	void UARTCmdControl(int argc, char *argv[]);

#ifndef BT_JIG_MODE
void UARTCmdWPTADCDisplay(int argc, char *argv[]);
void UARTCmdWPTVOUTChagne(int argc, char *argv[]);
void UARTCmdTempChange(int argc, char *argv[]);
void UARTCmdCurrChange(int argc, char *argv[]);
uint8_t UARTCmdGetWPTCharCurrValue(void);
void UARTCmdFactoryDebug1(int argc, char *argv[]);
void UARTCmdFactoryDebug2(int argc, char *argv[]);
void UARTCmdFactoryDebugOff(int argc, char *argv[]);
void UARTCmdFactoryHWVer(int argc, char *argv[]);
void UARTCmdFactorySWVer(int argc, char *argv[]);
void UARTCmdFactoryVER1(int argc, char *argv[]);
void UARTCmdFactoryModel(int argc, char *argv[]);
void UARTCmdFactoryVBAT(int argc, char *argv[]);
void UARTCmdFactoryHALL(int argc, char *argv[]);
void UARTCmdFactoryLED_R(int argc, char *argv[]);
void UARTCmdFactoryLED_G(int argc, char *argv[]);
void UARTCmdFactoryLED_B(int argc, char *argv[]);
void UARTCmdFactoryLED_X(int argc, char *argv[]);
void UARTCmdFactorySleep(int argc, char *argv[]);
void UARTCmdFactoryReset(int argc, char *argv[]);
void UARTCmdFactoryFG(int argc, char *argv[]);
void UARTCmdFactorySNWrite(int argc, char *argv[]);
void UARTCmdFactorySNRead(int argc, char *argv[]);
void UARTCmdFactoryUNRead(int argc, char *argv[]);
void UARTCmdFactoryBootMSG(int argc, char *argv[]);
void UARTCmdFactoryTermistor(int argc, char *argv[]);
void UARTCmdFactoryCheck(int argc, char *argv[]);
void UARTCmdFactoryHWverWrite(int argc, char *argv[]);
void UARTCmdFactoryHWverRead(int argc, char *argv[]);
void UARTCmdFactoryFGCurrentRead(int argc, char *argv[]);
void UARTCmdFactoryPowerOff(int argc, char *argv[]);
void UARTCmdFactoryNVNONE01(int argc, char *argv[]);
void UARTCmdFactoryNVERR01(int argc, char *argv[]);
void UARTCmdFactoryNVPASS01(int argc, char *argv[]);
void UARTCmdFactoryNVRead01(int argc, char *argv[]);
void UARTCmdFactoryNVNONE1E(int argc, char *argv[]);
void UARTCmdFactoryNVERR1E(int argc, char *argv[]);
void UARTCmdFactoryNVPASS1E(int argc, char *argv[]);
void UARTCmdFactoryNVRead1E(int argc, char *argv[]);
void UARTCmdFactoryNVNONE21(int argc, char *argv[]);
void UARTCmdFactoryNVERR21(int argc, char *argv[]);
void UARTCmdFactoryNVPASS21(int argc, char *argv[]);
void UARTCmdFactoryNVRead21(int argc, char *argv[]);
#else   /************ DEFINE BT_JIG FUNCTION HERE *****************/
void UARTCmdFactoryBTIDWrite(int argc, char *argv[]);
//	void UARTCmdFactoryBTIDRead(int argc, char *argv[]);
//	void UARTCmdFactoryBTIDCoupW(int argc, char *argv[]);
//	void UARTCmdFactoryBTIDCoupR(int argc, char *argv[]);
#endif

#endif

