target remote :3333
load
symbol-file debug/kernel.debug
add-symbol-file debug/app_1.debug 0x08020000
add-symbol-file debug/app_2.debug 0x08040000
