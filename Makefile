BUILD_DIR = build
PROGRAM = project2

CROSS_COMPILE := arm-none-eabi-

CC = $(CROSS_COMPILE)gcc
OBJCOPY = $(CROSS_COMPILE)objcopy
LD = $(CROSS_COMPILE)gcc
AS = $(CROSS_COMPILE)gcc

PICOTOOL := picotool

CFLAGS :=       -mcpu=cortex-m0plus \
		-mthumb \
		-mno-thumb-interwork \
		-Os \
		-ffunction-sections \
		-fdata-sections \
		-Wall \
		-Wextra \
		-Wno-unused-function

ASFLAGS := $(CFLAGS)
LDFLAGS := -mthumb -nostdlib -Wl,--gc-sections

S_SOURCES = src/rp2040-vectors.S src/rp2040-crt.S src/bl2.S
C_SOURCES = src/main.c src/uart.c src/spi.c src/mini_libgcc.c src/rtc.c src/i2c.c src/tm1637.c src/pio-handler.c

OBJECTS = $(addprefix $(BUILD_DIR)/,$(notdir $(C_SOURCES:.c=.o)))
OBJECTS += $(addprefix $(BUILD_DIR)/,$(notdir $(S_SOURCES:.S=.o)))
DEPS = $(OBJECTS:%.o=%.d)

vpath %.c $(sort $(dir $(C_SOURCES)))
vpath %.S $(sort $(dir $(S_SOURCES)))
vpath %.lds src
vpath %.o $(BUILD_DIR)
vpath %.elf $(BUILD_DIR)
vpath %.bin $(BUILD_DIR)

.PHONY: all clean debug flash

all: $(PROGRAM).uf2

debug: CFLAGS += -g
debug: all

$(OBJECTS): | $(BUILD_DIR)

$(BUILD_DIR):
	mkdir -p $@

-include $(DEPS)
$(BUILD_DIR)/%.o: %.c
	$(CC) -MMD -c $(CFLAGS) $< -o $@

-include $(DEPS)
$(BUILD_DIR)/%.o: %.S
	$(CC) -MMD -c $(ASFLAGS) $< -o $@

$(BUILD_DIR)/$(PROGRAM).elf: rp2040.lds $(OBJECTS)
	$(LD) $(LDFLAGS) -T $^ -o $@

$(PROGRAM).uf2: $(BUILD_DIR)/$(PROGRAM).uf2
	cp $< .

$(BUILD_DIR)/$(PROGRAM).uf2: $(PROGRAM).elf
	$(PICOTOOL) uf2 convert $< $@ --family rp2040

$(BUILD_DIR)/$(PROGRAM).bin: $(PROGRAM).elf
	$(OBJCOPY) -O binary $< $@

flash: $(PROGRAM).uf2
	$(PICOTOOL) load -fx $<

clean:
	-rm -rf $(BUILD_DIR)
	-rm -f project2.uf2
