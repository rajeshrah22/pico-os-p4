#include <ioregs.h>

void gpio_init(void) {
        IO_BANK0.io[25].ctrl = 5;
}
