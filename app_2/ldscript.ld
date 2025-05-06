OUTPUT_FORMAT("elf32-littlearm", "elf32-bigarm", "elf32-littlearm")
OUTPUT_ARCH(arm)
ENTRY(main)

MEMORY {
	APP_FLASH (rx)	: ORIGIN = 0x08040000, LENGTH = 128K
	APP_RAM (rxw)	: ORIGIN = 0x20008000, LENGTH = 32K
}

SECTIONS {
	.text : {
		PROVIDE(__ro_section_start = .);
		KEEP(*(.app_header))
		*(.text)
		*(.text.*)
	} > APP_FLASH

	.rodata : {
		. = ALIGN(4);
		*(.rodata)
		*(.rodata.*)
	} > APP_FLASH
	
	.data : {
		. = ALIGN(4);
		PROVIDE(__data_start = .);
		*(.data)
		*(.data.*)
		. = ALIGN(4);
		PROVIDE(__data_end = .);
	} > APP_RAM  AT > APP_FLASH

    __data_rom_start = LOADADDR(.data);
	__ro_section_end = __data_rom_start + SIZEOF(.data);

	.bss : {
		. = ALIGN(4);
		PROVIDE(__bss_start = .);
		*(.bss)
		*(.bss.*)
		*(COMMON)
		. = ALIGN(4);
		PROVIDE(__bss_end = .);
	} > APP_RAM

	__ram_end = ORIGIN(APP_RAM) + LENGTH(APP_RAM);

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
