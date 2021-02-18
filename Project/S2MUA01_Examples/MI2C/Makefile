# Copyright (C) ARM Limited, 2009-2010. All rights reserved.
# This makefile is intended for use with GNU make
# TEST_CASE = $(shell echo $(PWD) | sed 's/.*\/tests\///g' | sed 's/\/.*//g' )

INC_DIR = -I ./../../../Drivers \
          -I ./../../../Drivers/CMSIS \
          -I ./../../../Drivers/Drivers \
          -I ./../../../Drivers/System \
          -I ./../../../Drivers/MCU \
          -I ./../../../Drivers/WPC \
          -I ./../../../Project/S2MUA01_Examples/MI2C

#MAKE_DIR = $(PWD)

MAKE_DIR = ./../..
BASE_DIR = ../../..

WPC_LIB_DIR = $(APP_DIR)/WPC
WPC_LIB_NAME = libWPT.a

OUT_PATH := $(MAKE_DIR)/Output
OBJ_PATH := $(OUT_PATH)/Obj
BIN_PATH := $(OUT_PATH)/Bin
MAP_PATH := $(OUT_PATH)/Map

OUT_DIR := .$(OUT_PATH)
OBJ_DIR := .$(OBJ_PATH)
BIN_DIR := .$(BIN_PATH)
MAP_DIR := .$(MAP_PATH)

APP_DIR      := .$(MAKE_DIR)/Drivers
MCU_DIR      := $(APP_DIR)/MCU
SYSTEM_DIR   := $(APP_DIR)/System
DRIVERS_DIR  := $(APP_DIR)/Drivers
WPC_DIR      := $(APP_DIR)/WPC
EXAMPLE_DIR  := .$(MAKE_DIR)/Project/S2MUA01_Examples/MI2C

FILE_CM0_BOOT   := $(MCU_DIR)/boot_cm0pikmcu.c
OBJ_CM0_BOOT    := $(OBJ_DIR)/boot_cm0pikmcu.o

FILE_CM0_RETARG := $(MCU_DIR)/retarget_cm0pikmcu.c
OBJ_CM0_RETARG  := $(OBJ_DIR)/retarget_cm0pikmcu.o

FILE_SYSTEM     := $(DRIVERS_DIR)/system.c
OBJ_SYSTEM      := $(OBJ_DIR)/system.o

FILE_TimerDrv   := $(DRIVERS_DIR)/timer_drv.c
OBJ_TimerDrv    := $(OBJ_DIR)/timer_drv.o

FILE_UARTDrv    := $(DRIVERS_DIR)/uart_drv.c
OBJ_UARTDrv     := $(OBJ_DIR)/uart_drv.o

FILE_MAIN       := $(EXAMPLE_DIR)/boot_code.c
OBJ_MAIN        := $(OBJ_DIR)/boot_code.o

FILE_SCDRV      := $(DRIVERS_DIR)/sc_drv.c
OBJ_SCDRV       := $(OBJ_DIR)/sc_drv.o

FILE_FGDRV      := $(DRIVERS_DIR)/fg_drv.c
OBJ_FGDRV       := $(OBJ_DIR)/fg_drv.o

FILE_COMMONDRV  := $(DRIVERS_DIR)/common_drv.c
OBJ_COMMONDRV   := $(OBJ_DIR)/common_drv.o

FILE_LEDDRV  := $(DRIVERS_DIR)/led_drv.c
OBJ_LEDDRV   := $(OBJ_DIR)/led_drv.o

FILE_I2CDRV  := $(DRIVERS_DIR)/i2c_drv.c
OBJ_I2CDRV   := $(OBJ_DIR)/i2c_drv.o

FILE_WPC_COMMON := $(WPC_DIR)/wpc_common.c
OBJ_WPC_COMMON  := $(OBJ_DIR)/wpc_common.o

SCATTERPATH = $(BASE_DIR)/scatter.scat

OUTPUT = fw_flash
TARGET = $(BIN_DIR)/$(OUTPUT).axf $(BIN_DIR)/$(OUTPUT).bin

CC=C:\Keil_v5\ARM\ARMCC\bin\armcc
AS=C:\Keil_v5\ARM\ARMCC\bin\armasm
LD=C:\Keil_v5\ARM\ARMCC\bin\armlink
AR=C:\Keil_v5\ARM\ARMCC\bin\armar
FE=C:\Keil_v5\ARM\ARMCC\bin\fromelf
OBJ_DUMP=C:\gcc-arm-none-eabi-4_9-2015q2-20150609-win32\bin\arm-none-eabi-objdump

# Select build rules based on Windows or Unix
ifdef WINDIR
  DONE = @if exist $(1) echo Build completed
  RM = if exist $(1) del /q $(1)
  SHELL = $(WINDIR)\system32\cmd.exe
else
  ifdef windir
    DONE = @if exist $(1) echo Build completed
    RM = if exist $(1) del /q $(1)
    SHELL = $(windir)\system32\cmd.exe
  else
    DONE = @if [ -f $(1) ]; then echo Build completed; fi
    RM = rm -f $(1)
  endif
endif

all: $(TARGET)
	 $(call DONE, $(TARGET))

rebuild: clean all

clean:
	$(call RM,$(BIN_PATH)/*.debug)
	$(call RM,$(OBJ_PATH)/*.o)
	$(call RM,$(BIN_PATH)/*.elf)
	$(call RM,$(BIN_PATH)/*.bin)
	$(call RM,$(BIN_PATH)/*.hex)
	$(call RM,$(BIN_PATH)/*.axf)
	$(call RM,$(BIN_PATH)/*.inc)
	$(call RM,$(BIN_PATH)/*.rcf)
	$(call RM,$(MAP_PATH)/*.map)
	$(call RM,build.sh)
	$(call RM,*.log)
	$(call RM,$(TARGET))

CFLAGS = -g -O2 --cpu=Cortex-M0plus --library_type=microlib
AFLAGS = -g --cpu=Cortex-M0plus --thumb

BOOT_OBJ = $(OBJ_CM0_BOOT) \
           $(OBJ_CM0_RETARG) \
           $(OBJ_SYSTEM) \
           $(OBJ_TimerDrv) \
           $(OBJ_UARTDrv) \
           $(OBJ_MAIN) \
           $(OBJ_SCDRV) \
           $(OBJ_FGDRV) \
           $(OBJ_COMMONDRV) \
	   $(OBJ_WPC_COMMON) \
           $(OBJ_LEDDRV) \
           $(OBJ_I2CDRV) \

$(BIN_DIR)/$(OUTPUT).axf : $(BOOT_OBJ)
	$(LD) "./../../../Drivers/CMSIS/arm_cortexM0PLUS_plc.lib" --scatter $(SCATTERPATH) --userlibpath=$(WPC_LIB_DIR) $(WPC_LIB_NAME) --library_type=microlib $(BOOT_OBJ) -o $@ --info totals
$(OBJ_CM0_BOOT) : $(FILE_CM0_BOOT)
	$(CC) -o "$(OBJ_CM0_BOOT)" $(INC_DIR) -c $(CFLAGS) $<

$(OBJ_MAIN) : $(FILE_MAIN)
	$(CC) -o "$(OBJ_MAIN)" $(INC_DIR) -c $(CFLAGS) $<

# Retarget file -enable printf to use IK character devic
$(OBJ_CM0_RETARG) : $(FILE_CM0_RETARG)
	$(CC) -o "$(OBJ_CM0_RETARG)" $(INC_DIR) -c $(CFLAGS) $<

$(OBJ_SYSTEM) : $(FILE_SYSTEM)
	$(CC) -o "$(OBJ_SYSTEM)" $(INC_DIR) -c $(CFLAGS) $<

$(OBJ_TimerDrv) : $(FILE_TimerDrv)
	$(CC) -o "$(OBJ_TimerDrv)" $(INC_DIR) -c $(CFLAGS) $<

$(OBJ_UARTDrv) : $(FILE_UARTDrv)
	$(CC) -o "$(OBJ_UARTDrv)" $(INC_DIR) -c $(CFLAGS) $<

$(OBJ_FGDRV)   : $(FILE_FGDRV)
	$(CC) -o "$(OBJ_FGDRV)" $(INC_DIR) -c $(CFLAGS) $<

$(OBJ_SCDRV)   : $(FILE_SCDRV)
	$(CC) -o "$(OBJ_SCDRV)" $(INC_DIR) -c $(CFLAGS) $<

$(OBJ_COMMONDRV)   : $(FILE_COMMONDRV)
	$(CC) -o "$(OBJ_COMMONDRV)" $(INC_DIR) -c $(CFLAGS) $<

$(OBJ_WPC_COMMON)   : $(FILE_WPC_COMMON)
	$(CC) -o "$(OBJ_WPC_COMMON)" $(INC_DIR) -c $(CFLAGS) $<

$(OBJ_LEDDRV)   : $(FILE_LEDDRV)
	$(CC) -o "$(OBJ_LEDDRV)" $(INC_DIR) -c $(CFLAGS) $<

$(OBJ_I2CDRV)   : $(FILE_I2CDRV)
	$(CC) -o "$(OBJ_I2CDRV)" $(INC_DIR) -c $(CFLAGS) $<

$(BIN_DIR)/$(OUTPUT).elf: $(BOOT_OBJ)
	$(LD) "./../../../Drivers/CMSIS/arm_cortexM0PLUS_plc.lib" --map --scatter $(SCATTERPATH) --pad 0x00 --userlibpath=$(WPC_LIB_DIR) $(WPC_LIB_NAME) --library_type=microlib $(BOOT_OBJ) -o $@ --info totals
	$(OBJ_DUMP) -DSe  $(BIN_DIR)/$(OUTPUT).elf >> $(BIN_DIR)/$(OUTPUT).debug

$(BIN_DIR)/$(OUTPUT).bin: $(BIN_DIR)/$(OUTPUT).elf
	$(FE) --bin -o $@ $<
	$(FE) --i32 -o $(BIN_DIR)/$(OUTPUT)_i32.hex $<
	$(FE) --vhx --32x1 -o $(BIN_DIR)/$(OUTPUT).hex $(BIN_DIR)/$(OUTPUT).axf
	$(FE) --text -v -acdstz -o $(MAP_DIR)/$(OUTPUT).map $(BIN_DIR)/$(OUTPUT).axf

