OUTPUT_FORMAT("elf32-littlearm", "elf32-bigarm", "elf32-littlearm")
OUTPUT_ARCH(arm)

MEMORY {
	KERNEL_FLASH (rx)   : ORIGIN = 0x10000000, LENGTH = 128K
	APP_1_FLASH (rx)	: ORIGIN = 0x10020000, LENGTH = 448K
	APP_2_FLASH (rx)	: ORIGIN = 0x10040000, LENGTH = 448K
}

SECTIONS {
	.os_image : {
		KEEP(*(.os_image))
	} > KERNEL_FLASH

	.app_1_image : {
		KEEP(*(.app_1_image))
	} > APP_1_FLASH

	.app_2_image : {
		KEEP(*(.app_2_image))
	} > APP_2_FLASH
}
