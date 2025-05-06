OUTPUT_FORMAT("elf32-littlearm", "elf32-bigarm", "elf32-littlearm")
OUTPUT_ARCH(arm)
ENTRY(__reset)

MEMORY {
	BOOTLOADER(rx) : ORIGIN = 0x20041f00, LENGTH = 256
	KERNEL_FLASH (rx)	: ORIGIN = 0x10000000, LENGTH = 128K
	KERNEL_RAM (rxw)	: ORIGIN = 0x2001c000, LENGTH = 16K
}

SECTIONS {
	.bootloader : {
		PROVIDE_HIDDEN(__bl2_start = .);
 		KEEP(*(.bootloader))
		. = ALIGN(256);
		PROVIDE_HIDDEN(__bl2_end = .);
	} > BOOTLOADER AT > KERNEL_FLASH

	__bl2_checksum = LOADADDR(.bootloader) + LENGTH(BOOTLOADER) - 4;

	.vector_table : {
		KEEP(*(.vector_table))
	} > KERNEL_FLASH

	.text : {
		*(.text)
		*(.text.*)
	} > KERNEL_FLASH

	.rodata : {
		. = ALIGN(4);
		*(.rodata)
		*(.rodata.*)
		. = ALIGN(4);
	} > KERNEL_FLASH

	.init_array (READONLY) : {
		PROVIDE_HIDDEN(__ctors_start = .);
		KEEP(*(SORT(.init_array.*)))
		KEEP(*(.init_array))
		PROVIDE_HIDDEN(__ctors_end = .);
	} > KERNEL_FLASH

	.fini_array (READONLY) : {
		PROVIDE_HIDDEN(__dtors_start = .);
		KEEP(*(SORT(.fini_array.*)))
		KEEP(*(.fini_array))
		PROVIDE_HIDDEN(__dtors_end = .);
	} > KERNEL_FLASH
	
	.data : {
		. = ALIGN(4);
		PROVIDE(__data_start = .);
		*(.data)
		*(.data.*)
		. = ALIGN(4);
		PROVIDE(__data_end = .);
	} > KERNEL_RAM  AT > KERNEL_FLASH

    __data_load_start = LOADADDR(.data);

	.bss : {
		. = ALIGN(4);
		PROVIDE(__bss_start = .);
		*(.bss)
		*(.bss.*)
		*(COMMON)
		. = ALIGN(4);
		PROVIDE(__bss_end = .);
	} > KERNEL_RAM

	__ram_end = ORIGIN(KERNEL_RAM) + LENGTH(KERNEL_RAM);

  /* The rest are all not normally part of the runtime image.  */

  /* Stabs debugging sections.  */
  .stab          0 : { *(.stab) }
  .stabstr       0 : { *(.stabstr) }
  .stab.excl     0 : { *(.stab.excl) }
  .stab.exclstr  0 : { *(.stab.exclstr) }
  .stab.index    0 : { *(.stab.index) }
  .stab.indexstr 0 : { *(.stab.indexstr) }
  .comment       0 : { *(.comment) }
  /* DWARF debug sections.
     Symbols in the DWARF debugging sections are relative to the beginning
     of the section so we begin them at 0.  */
  /* DWARF 1 */
  .debug          0 : { *(.debug) }
  .line           0 : { *(.line) }
  /* GNU DWARF 1 extensions */
  .debug_srcinfo  0 : { *(.debug_srcinfo) }
  .debug_sfnames  0 : { *(.debug_sfnames) }
  /* DWARF 1.1 and DWARF 2 */
  .debug_aranges  0 : { *(.debug_aranges) }
  .debug_pubnames 0 : { *(.debug_pubnames) }
  /* DWARF 2 */
  .debug_info     0 : { *(.debug_info .gnu.linkonce.wi.*) }
  .debug_abbrev   0 : { *(.debug_abbrev) }
  .debug_line     0 : { *(.debug_line .debug_line.* .debug_line_end ) }
  .debug_frame    0 : { *(.debug_frame) }
  .debug_str      0 : { *(.debug_str) }
  .debug_loc      0 : { *(.debug_loc) }
  .debug_macinfo  0 : { *(.debug_macinfo) }
  /* SGI/MIPS DWARF 2 extensions */
  .debug_weaknames 0 : { *(.debug_weaknames) }
  .debug_funcnames 0 : { *(.debug_funcnames) }
}
