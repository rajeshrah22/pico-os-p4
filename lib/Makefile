CC	:=	arm-none-eabi-gcc
LD	:=	arm-none-eabi-gcc
AS	:=	arm-none-eabi-gcc
AR	:=	arm-none-eabi-ar
SIZE :=	arm-none-eabi-size
OBJCOPY	:=	arm-none-eabi-objcopy
RM := rm -f

DIRS = . rt svc

SRC := $(wildcard $(foreach dir, $(DIRS), $(dir)/*.S))
SRC += $(wildcard $(foreach dir, $(DIRS), $(dir)/*.c))
OBJ := $(SRC:%.S=%.o)
OBJ := $(OBJ:%.c=%.o)

LIB := librt.a

CPU := cortex-m0plus

ASFLAGS = -mthumb \
		  -mcpu=$(CPU) \
		  -I../include/core \
		  -I../include/user

CFLAGS =	-mthumb -mno-thumb-interwork \
			-Wall -Os \
			-mcpu=$(CPU) \
			-I../include/core \
			-I../include/user \
			-Iinclude

.PHONY: all clean

all: $(LIB)
	$(SIZE) $(LIB)

clean:
	-$(RM) $(LIB) $(OBJ)

$(LIB): $(OBJ)
	$(AR) rcs $(LIB) $(OBJ)

%.o: %.S
	$(AS) $(ASFLAGS) -c $< -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@
