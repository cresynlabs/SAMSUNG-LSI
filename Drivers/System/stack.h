/*
******************************************************************************
* @file    stack.h
* @author  Power Device Team
* @version V1.0.0
* @date    15-March-2016
* @brief   Header for Memory System
******************************************************************************
*/
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __STACK_H
#define __STACK_H

#define VECTORS_SIZE            0xC0
#define BOOT_VECTORS_BASE       0x00000000

#define BOOT_CONFIG_BASE        0x000000C0
#define BOOT_CONFIG_SIZE        (BOOT_CODE_BASE - BOOT_CONFIG_BASE)

#define BOOT_CODE_BASE			0x00000230
#define BOOT_CODE_SIZE			(STARTUP_CODE_BASE - BOOT_CODE_BASE)
 
#define STARTUP_CODE_BASE		0x00000400

#define DATA_AREA_BASE          0x20001080
#define DATA_AREA_SIZE          (HEAP_BASE - DATA_AREA_BASE)

#define FLASH_DUMP_BASE         0x20002E00
#define FLASH_DUMP_SIZE         (SRAM_END - FLASH_DUMP_BASE)
#define SRAM_END				0x20002F00

/*
** This file contains the stack and heap addresses.
*/
#define HEAP_BASE  0x20002400
#define STACK_BASE 0x20002E00

#define HEAP_SIZE  0x400	//((STACK_BASE-HEAP_BASE)/2)
#define STACK_SIZE 0x600	//((STACK_BASE-HEAP_BASE)/2)


#endif /* __STACK_H */
