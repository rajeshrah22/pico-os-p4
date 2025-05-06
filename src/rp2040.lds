RAM_SIZE = (256 * 1024);
FLASH_SIZE = (8 * 1024 * 1024);

OUTPUT_FORMAT("elf32-littlearm", "elf32-littlearm", "elf32-littlearm")
OUTPUT_ARCH(arm)
ENTRY(__reset)

MEMORY
{
	FLASH (RX) : ORIGIN = 0x10000000, LENGTH = FLASH_SIZE
	RAM (RWX) : ORIGIN = 0x20000000, LENGTH = RAM_SIZE
	BOOTLOADER (RWX) : ORIGIN = 0x20041f00, LENGTH = 256
}

SECTIONS
{
	.bootloader : {
		KEEP(*(.bootloader))
		. = ALIGN(256);
	} > BOOTLOADER AT > FLASH
	__bl2_checksum = LOADADDR(.bootloader) + LENGTH(BOOTLOADER) - 4;

	.vectors : {
		KEEP(*(.vector_table))
	} > FLASH

	.text :
	{
		*(.text*)
		. = ALIGN(4);
		PROVIDE_HIDDEN(__text_end = .);
	} > FLASH


	.rodata : {
		*(.rodata*)
	} > FLASH

	.init_array (READONLY) : {
		. = ALIGN(4);
		PROVIDE_HIDDEN(__ctors_start = .);
		KEEP(*(SORT(.init_array.*)))
		KEEP(*(.init_array))
		PROVIDE_HIDDEN(__ctors_end = .);
	} > FLASH

	.fini_array (READONLY) : {
		. = ALIGN(4);
		PROVIDE_HIDDEN(__dtors_start = .);
		KEEP(*(SORT(.fini_array.*)))
		KEEP(*(.fini_array))
		PROVIDE_HIDDEN(__dtors_end = .);
	} > FLASH

	.data : {
		. = ALIGN(4);
		PROVIDE_HIDDEN(__data_start = .);
		*(.data*)
		. = ALIGN(4);
		PROVIDE_HIDDEN(__data_end = .);
	} > RAM AT > FLASH
	PROVIDE_HIDDEN(__data_load_start = LOADADDR(.data));

	.bss : {
		. = ALIGN(4);
		PROVIDE_HIDDEN(__bss_start = .);
		*(.bss*)
		. = ALIGN(4);
		PROVIDE_HIDDEN(__bss_end = .);
	} > RAM

	PROVIDE_HIDDEN(__ram_end = ORIGIN(RAM) + LENGTH(RAM));
}
