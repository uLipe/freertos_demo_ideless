#
# Makafile used to build free rtos demo
# Author: Felipe Silva Neves
#
TOOLCHAN_PATH=../toolchain/bin
PREFIX=arm-none-eabi-
CC=gcc
LD=g++
AS=as
GDB=gdb
CFLAGS= -Wall -O0 -c -g -mthumb -mcpu=cortex-m4 -mlittle-endian

#
# Add include directories:
#
CFLAGS += -I ../freertos_nxp/Source/include
CFLAGS += -I ../freertos_nxp/Source/portable/GCC/ARM_CM4F
CFLAGS += -I proj_include
CFLAGS += -I proj_include/cmsis
CFLAGS += -I drivers
CFLAGS += -I debug_util
CFLAGS += -I board


#
# Add source directories:
#
SRC  = $(wildcard ../freertos_nxp/Source/*.c)
SRC += $(wildcard ../freertos_nxp/Source/portable/GCC/ARM_CM4F/*.c)
SRC += ../freertos_nxp/Source/portable/MemMang/heap_1.c

# add drivers folder:
SRC += $(wildcard drivers/*.c)

#add debug drivers:
SRC += $(wildcard debug_util/*.c)

#add bsp files:
SRC += $(wildcard board/*.c)

#add main or other c file stuff
SRC += $(wildcard *.c)
SRC += $(wildcard system/*.c)


#add startup code:
AS_SRC = system/startup.S

#
# Define linker script files:
#
LDS=system/hw1.ld
LDFLAGS = -T$(LDS) -specs=nosys.specs -specs=nano.specs -Xlinker -Map=hw1.map


#
# .c to .o recursion magic:
#
OBJS  = $(SRC:.c=.o)
OBJS += $(AS_SRC:.s=.o)


#
# Define the build chain:
#
.PHONY: all, clean,connect,debug

all: hw1.elf
	@echo "generated $< file successfully!"

connect:

debug:

clean:
	rm -f *.elf
	rm -f  ../freertos_nxp/Source/*.o
	rm -f  ../freertos_nxp/Source/portable/GCC/ARM_CM4F/*.o
	rm -f  ../freertos_nxp/Source/portable/portable/MemMang/*.o
	rm -f  system/*.o
	rm -f  *.o
	rm -f  drivers/*.o
	rm -f  debug_util/*.o
	rm -f  board/*.o


#
# Linking step:
#
hw1.elf: $(OBJS)
	@echo "Linking files"
	$(TOOLCHAN_PATH)/$(PREFIX)$(LD) $(LDFLAGS) $(OBJS) -o $@
	@echo "cleaning up..."
	rm -f  ../freertos_nxp/Source/*.o
	rm -f  ../freertos_nxp/Source/portable/GCC/ARM_CM4F/*.o
	rm -f  ../freertos_nxp/Source/portable/portable/MemMang/*.o
	rm -f  system/*.o
	rm -f  *.o
	rm -f  drivers/*.o
	rm -f  debug_util/*.o
	rm -f  board/*.o


#
# Compiling step:
#
.c.o:
	@echo "Compiling $< file"
	$(TOOLCHAN_PATH)/$(PREFIX)$(CC) $(CFLAGS) -o $@  $<

#
# startup code step:
#
.s.o:
	@echo "Assembling $< file"
	$(TOOLCHAN_PATH)/$(PREFIX)$(AS) -o $@  $<
