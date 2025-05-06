#ifndef ADDRESS_MAP_H
#define ADDRESS_MAP_H

#include <stdint.h>

/* Based on RP2040 Datasheet found at
 * https://datasheets.raspberrypi.com/rp2040/rp2040-datasheet.pdf
 */

#define ROM_BASE                      ((volatile uint32_t *) 0x00000000)

#define XIP_BASE                      ((volatile uint32_t *) 0x10000000)
#define XIP_NOALLOC_BASE              ((volatile uint32_t *) 0x11000000)
#define XIP_NOCACHE_BASE              ((volatile uint32_t *) 0x12000000)
#define XIP_NOCACHE_NOALLOC_BASE      ((volatile uint32_t *) 0x13000000)
#define XIP_CTRL_BASE                 ((volatile uint32_t *) 0x14000000)
#define XIP_SRAM_BASE                 ((volatile uint32_t *) 0x15000000)
#define XIP_SRAM_END                  ((volatile uint32_t *) 0x15004000)
#define XIP_SSI_BASE                  ((volatile uint32_t *) 0x18000000)

#define SRAM_BASE                     ((volatile uint32_t *) 0x20000000)
#define SRAM_STRIPED_BASE             ((volatile uint32_t *) 0x20000000)
#define SRAM_STRIPED_END              ((volatile uint32_t *) 0x20040000)
#define SRAM4_BASE                    ((volatile uint32_t *) 0x20040000)
#define SRAM5_BASE                    ((volatile uint32_t *) 0x20041000)
#define SRAM_END                      ((volatile uint32_t *) 0x20042000)

#define SRAM0_BASE                    ((volatile uint32_t *) 0x21000000)
#define SRAM1_BASE                    ((volatile uint32_t *) 0x21010000)
#define SRAM2_BASE                    ((volatile uint32_t *) 0x21020000)
#define SRAM3_BASE                    ((volatile uint32_t *) 0x21030000)

#define SYSINFO_BASE                  ((volatile uint32_t *) 0x40000000)
#define SYSCFG_BASE                   ((volatile uint32_t *) 0x40004000)
#define CLOCKS_BASE                   ((volatile uint32_t *) 0x40008000)
#define RESETS_BASE                   ((volatile uint32_t *) 0x4000C000)
#define PSM_BASE                      ((volatile uint32_t *) 0x40010000)
#define IO_BANK0_BASE                 ((volatile uint32_t *) 0x40014000)
#define IO_QSPI_BASE                  ((volatile uint32_t *) 0x40018000)
#define PADS_BANK0_BASE               ((volatile uint32_t *) 0x4001C000)
#define PADS_QSPI_BASE                ((volatile uint32_t *) 0x40020000)
#define XOSC_BASE                     ((volatile uint32_t *) 0x40024000)
#define PLL_SYS_BASE                  ((volatile uint32_t *) 0x40028000)
#define PLL_USB_BASE                  ((volatile uint32_t *) 0x4002C000)
#define BUSCTRL_BASE                  ((volatile uint32_t *) 0x40030000)
#define UART0_BASE                    ((volatile uint32_t *) 0x40034000)
#define UART1_BASE                    ((volatile uint32_t *) 0x40038000)
#define SPI0_BASE                     ((volatile uint32_t *) 0x4003C000)
#define SPI1_BASE                     ((volatile uint32_t *) 0x40040000)
#define I2C0_BASE                     ((volatile uint32_t *) 0x40044000)
#define I2C1_BASE                     ((volatile uint32_t *) 0x40048000)
#define ADC_BASE                      ((volatile uint32_t *) 0x4004C000)
#define PWM_BASE                      ((volatile uint32_t *) 0x40050000)
#define TIMER_BASE                    ((volatile uint32_t *) 0x40054000)
#define WATCHDOG_BASE                 ((volatile uint32_t *) 0x40058000)
#define RTC_BASE                      ((volatile uint32_t *) 0x4005C000)
#define ROSC_BASE                     ((volatile uint32_t *) 0x40060000)
#define VREG_AND_CHIP_RESET_BASE      ((volatile uint32_t *) 0x40064000)
#define TBMAN_BASE                    ((volatile uint32_t *) 0x4006C000)

#define DMA_BASE                      ((volatile uint32_t *) 0x50000000)
#define USBCTRL_BASE                  ((volatile uint32_t *) 0x50100000)
#define USBCTRL_DPRAM_BASE            ((volatile uint32_t *) 0x50100000)
#define USBCTRL_REGS_BASE             ((volatile uint32_t *) 0x50110000)
#define PIO0_BASE                     ((volatile uint32_t *) 0x50200000)
#define PIO1_BASE                     ((volatile uint32_t *) 0x50300000)
#define XIP_AUX_BASE                  ((volatile uint32_t *) 0x50400000)

#define SIO_BASE                      ((volatile uint32_t *) 0xD0000000)
#define PPB_BASE                      ((volatile uint32_t *) 0xE0000000)

#endif // ADDRESS_MAP_H
