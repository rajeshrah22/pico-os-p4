CC	:=	arm-none-eabi-gcc
LD	:=	arm-none-eabi-gcc
AS	:=	arm-none-eabi-gcc
AR	:=	arm-none-eabi-ar
OBJCOPY	:=	arm-none-eabi-objcopy
GDB	:=	arm-none-eabi-gdb
FLASH=

SRC := $(wildcard *.S)
SRC += $(wildcard *.c)

OBJ := $(SRC:%.S=%.o)
OBJ := $(OBJ:%.c=%.o)

CPU	:=	cortex-m0plus

ELF := app_1.elf

ASFLAGS = -mthumb \
		  -mcpu=$(CPU) \
		  -I../include/core \
		  -D__KERNEL \

CFLAGS = -mthumb \
		 -I../include/core \
		 -I../lib/include \
		 -mcpu=$(CPU) \
		 -ffunction-sections \
		 -fdata-sections \
		 -Wall -Os \
		 -Wno-main

LDFLAGS = -mthumb \
		  -mcpu=$(CPU) \
		  -nostdlib \
		  -Wl,--gc-sections

LDSCRIPTS = ldscript.ld 

LDS_OPTS = $(foreach lds, $(LDSCRIPTS), -Wl,-T./$(lds))

LIBS = rt
LIBPATHS =../lib

BIN = $(ELF:%.elf=%.bin)

LIB = $(foreach l, $(LIBS), -l$(l))
LIBPATH = $(foreach lp, $(LIBPATHS), -L$(lp))

all: $(ELF)

bin: $(BIN)
	$(OBJCOPY) -Barm -I binary -O elf32-littlearm \
	--rename-section .data=.app_1_image,contents,alloc,load,readonly,data \
	$(BIN) $(BIN:%.bin=%.eo)

clean:
	-rm -f $(OBJ) $(ELF) $(BIN) $(BIN:%.bin=%.eo)

debug: CLFAGS += -g
debug: all

$(BIN): $(ELF)
	$(OBJCOPY) -O binary $(ELF) $(BIN)

$(ELF): $(OBJ)	
	$(LD) $(LDS_OPTS) $(LDFLAGS) -o $@ $(OBJ) $(LIBPATH) $(LIB)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

%.o: %.S
	$(AS) $(ASFLAGS) -c $< -o $@


