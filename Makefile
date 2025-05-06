# toplevel makefile, do not edit!

LD := arm-none-eabi-gcc
OBJCOPY := arm-none-eabi-objcopy
SIZE := arm-none-eabi-size
NM = arm-none-eabi-nm
RM := rm -f
MKDIR := mkdir -p

ELF = os_image.elf
BIN = $(ELF:%.elf=%.bin)

KERNEL := ./core/kernel.eo
LIB := ./lib/librt.a
APP_1 := ./app_1/app_1.eo
APP_2 := ./app_2/app_2.eo

DEBUGDIR := ./debug

LDFLAGS := -nostdlib -Wl,-Tlds/os_image.ld \
			-mcpu=cortex-m0plus -mthumb

.PHONY: all clean symbols

all: $(ELF) symbols
	$(SIZE) $(ELF)

clean:
	$(MAKE) -C core clean
	$(MAKE) -C lib clean
	$(MAKE) -C app_1 clean
	$(MAKE) -C app_2 clean
	-$(RM) $(ELF) $(BIN)

symbols: $(ELF)
	$(MKDIR) $(DEBUGDIR)
	$(OBJCOPY) --only-keep-debug $(KERNEL:%.eo=%.elf) $(DEBUGDIR)/kernel.debug
	$(OBJCOPY) --prefix-symbols=app_1__ --only-keep-debug \
		$(APP_1:%.eo=%.elf) $(DEBUGDIR)/app_1.debug
	$(OBJCOPY) --prefix-symbols=app_2__ --only-keep-debug \
		$(APP_2:%.eo=%.elf) $(DEBUGDIR)/app_2.debug

$(ELF): $(KERNEL) $(LIB) $(APP_1) $(APP_2)
	$(LD) -Wl,-e0x$(shell $(NM) $(KERNEL:%.eo=%.elf) | \
		grep __reset | cut -d ' ' -f 1) $(LDFLAGS) -o $(ELF) $(KERNEL) $(APP_1) $(APP_2)

$(KERNEL):
	$(MAKE) -C core debug bin

$(LIB):
	$(MAKE) -C lib

$(APP_1): $(LIB)
	$(MAKE) -C app_1 bin

$(APP_2): $(APP_1) $(LIB)
	$(MAKE) -C app_2 bin
