CC	:=	arm-none-eabi-gcc
LD	:=	arm-none-eabi-gcc
AS	:=	arm-none-eabi-gcc
AR	:=	arm-none-eabi-ar
OBJCOPY	:=	arm-none-eabi-objcopy
GDB	:=	arm-none-eabi-gdb
FLASH=

DIRS := . svcalls periph asm_core lib kernel

SRC := $(wildcard $(foreach dir, $(DIRS), $(dir)/*.S))
SRC += $(wildcard $(foreach dir, $(DIRS), $(dir)/*.c))

OBJ := $(SRC:%.S=%.o)
OBJ := $(OBJ:%.c=%.o)

CPU	:=	cortex-m0plus

ELF := kernel.elf

ASFLAGS = -mcpu=$(CPU) \
		  -I../include/core \
		  -D__KERNEL \
		# -mthumb \

CFLAGS = -mthumb \
		 -I../include/core \
		 -mcpu=$(CPU) \
		 -ffunction-sections \
		 -fdata-sections \
		 -Wall -Wno-unused -Os \
		 -D__KERNEL

LDFLAGS = -mthumb \
		  -Wl,--map=$(ELF:%.elf=%.map) \
		  -mcpu=$(CPU) \
		  -nostdlib \
		  -Wl,--gc-sections

LDSCRIPTS = ldscript.ld ioregs.ld

LDS_OPTS = $(foreach lds, $(LDSCRIPTS), -Wl,-Tlds/$(lds))

LIBS =

BIN = $(ELF:%.elf=%.bin)

all: $(ELF)

bin: $(BIN)
	$(OBJCOPY) -Barm -I binary -O elf32-littlearm \
		--rename-section .data=.os_image,contents,alloc,load,readonly,data \
		$(BIN) $(BIN:%.bin=%.eo)

clean:
	-rm -f $(OBJ) $(ELF) $(BIN) $(BIN:%.bin=%.eo)

debug: CLFAGS += -g
debug: all

$(BIN): $(ELF)
	$(OBJCOPY) -O binary $(ELF) $(BIN)

$(ELF): $(OBJ)	
	$(LD) $(LDS_OPTS) $(LDFLAGS) -o $@ $(OBJ) $(LIBS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

%.o: %.S
	$(AS) $(ASFLAGS) -c $< -o $@


