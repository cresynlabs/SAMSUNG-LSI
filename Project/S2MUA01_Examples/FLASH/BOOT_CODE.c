/*
******************************************************************************
* @file    boot_code.c
* @author  Power Device Team
* @version V1.0.0
* @date    15-March-2016
* @brief   Boot System Function
******************************************************************************
*/

#include "cm0pikmcu.h"
#include "System.h"
#include "common_drv.h"
#include "PLC.h"
#include "sc_drv.h"

#pragma arm section code = "region_main_func"

#define ERASE_MODE_PAGE     0
#define ERASE_MODE_SECTOR   1
#define ERASE_MODE_MATRIX   2

#define __isHVEN()          FLASHCON.FRWCON.BITS.HVEN
#define __setHVEN()         (FLASHCON.FRWCON.BITS.HVEN = 0x1)
#define __HVEN_WAIT()       while(__isHVEN())
#define __setPGMMODE()      (FLASHCON.FRWCON.BITS.WRMD = 0x2)
#define __enableHV()        do { \
                                __setHVEN(); \
                                __HVEN_WAIT(); \
                            } while(0)
#define __setEraseMODE(Size)    do { \
										FLASHCON.FRWCON.BITS.ERASEMD = Size; \
										FLASHCON.FRWCON.BITS.WRMD	 = 0x1; \
									} while(0)

uint32_t FlashErase(uint32_t *addr, uint32_t Size)
{
	uint32_t ret = RET_OK;

	if (addr < (uint32_t *)FLASH_CODE_BASE)
		return RET_FAIL;

	__setEraseMODE(Size);
	*((volatile uint32_t *)addr) = 0xffffffff;
	__enableHV();

	return ret;
}

uint32_t FlashWrite32bit(uint32_t *addr, uint32_t data)
{
	uint32_t ret = RET_OK;
	volatile uint32_t *addr_ptr;

	if (addr < (uint32_t *)FLASH_CODE_BASE)
		return RET_FAIL;

	addr_ptr = (uint32_t *) addr;

	__setPGMMODE();
	*addr_ptr = data ;
	__enableHV();

	return ret;
}

void variable_area_clear(void)
{
	uint32_t *ClrAdr, ulCnt;

	ClrAdr = (uint32_t *)(DATA_AREA_BASE);
	for (ulCnt = 0; ulCnt < (FLASH_DUMP_SIZE / 4); ulCnt++)
		ClrAdr[ulCnt] = 0;

	ClrAdr = (uint32_t *)(EXT_SRAM_BASE + 0x10);
	for (ulCnt = 0; ulCnt < 16; ulCnt++)
		ClrAdr[ulCnt] = 0xFFFFFFFF;
}

void delay_for_stablization(void)
{
	uint32_t cnt;
	for (cnt = 0; cnt < 10000; cnt++)
	{
		__NOP();
	}
}

int main(void)
{
	uint32_t systime=0;
	uint32_t *addr;

	NVIC->ICER[0] = (uint32_t)0xFFFFFFFF;       // Disable All IRQ
	NVIC->ICPR[0] = (uint32_t)0xFFFFFFFF;       // Interrupt Pending Clear

	//OM LOW Debounce time
	SYSREG.OM_DBNC_PDLY.BITS.OM_DBNC_PDLY = 0x8000;    //0x8000 =2 ms
	SYSREG.DMA_Flash.BITS.PI2C_TO_FLASH_AUTO_PGM = 0;
	PM.REG_4C.BITS.VBAT1CO = 1;

	systimer_initialize();
	NVIC_EnableIRQ(IRQ00_NOR);
	variable_area_clear();
	gpio_drv_set_to_uart();
	uart_drv_init();

	delay_for_stablization();

	printf("START S2MUA01 : %s\r\n",BuildTime);

	systime = sys_get_tick();

	addr = (uint32_t *)0x0000BE00;

	if (*addr == 0xFFFFFFFF)
		FlashWrite32bit(addr, 0x1234ABCD);
	else
		FlashErase(addr, ERASE_MODE_PAGE);

	while (1)
	{
		if ((sys_get_tick() - systime) > 1000)
		{
			systime = sys_get_tick();
			printf("%x \r\n",*addr);
		}
	}

}

#pragma arm section code


