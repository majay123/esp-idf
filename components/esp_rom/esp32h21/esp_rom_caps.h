/*
 * SPDX-FileCopyrightText: 2024 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#pragma once

#define ESP_ROM_HAS_CRC_LE                  (1) // ROM CRC library supports Little Endian
#define ESP_ROM_HAS_CRC_BE                  (1) // ROM CRC library supports Big Endian
#define ESP_ROM_UART_CLK_IS_XTAL            (1) // UART clock source is selected to XTAL in ROM
#define ESP_ROM_USB_SERIAL_DEVICE_NUM       (3) // UART uses USB_SERIAL_JTAG port in ROM.
#define ESP_ROM_HAS_RETARGETABLE_LOCKING    (1) // ROM was built with retargetable locking
#define ESP_ROM_GET_CLK_FREQ                (1) // Get clk frequency with rom function `ets_get_cpu_frequency`
#define ESP_ROM_HAS_HAL_WDT                 (1) // ROM has the implementation of Watchdog HAL driver
#define ESP_ROM_HAS_HAL_SYSTIMER            (1) // ROM has the implementation of Systimer HAL driver
#define ESP_ROM_SYSTIMER_INIT_PATCH         (1) // ROM version initializes SYSTIMER without ETM
#define ESP_ROM_HAS_HEAP_TLSF               (1) // ROM has the implementation of the tlsf and multi-heap library
#define ESP_ROM_MULTI_HEAP_WALK_PATCH       (1) // ROM does not contain the patch of multi_heap_walk()
#define ESP_ROM_HAS_LAYOUT_TABLE            (1) // ROM has the layout table
#define ESP_ROM_HAS_SPI_FLASH               (1) // ROM has the implementation of SPI Flash driver
#define ESP_ROM_HAS_SPI_FLASH_MMAP          (1) // ROM has the implementation of SPI Flash mmap driver
#define ESP_ROM_WITHOUT_REGI2C              (1) // ROM has no regi2c APIs
#define ESP_ROM_HAS_NEWLIB                  (1) // ROM has newlib (at least parts of it) functions included
#define ESP_ROM_HAS_NEWLIB_NANO_FORMAT      (1) // ROM has the newlib nano versions of formatting functions
#define ESP_ROM_WDT_INIT_PATCH              (1) // ROM version does not configure the clock
#define ESP_ROM_RAM_APP_NEEDS_MMU_INIT      (1) // ROM doesn't init cache MMU when it's a RAM APP, needs MMU hal to init
#define ESP_ROM_HAS_SW_FLOAT                (1) // ROM has libgcc software floating point emulation functions
#define ESP_ROM_USB_OTG_NUM                 (-1) // No USB_OTG CDC in the ROM, set -1 for Kconfig usage.
#define ESP_ROM_HAS_VERSION                 (1) // ROM has version/eco information
// #define ESP_ROM_SUPPORT_DEEP_SLEEP_WAKEUP_STUB  (1) // ROM supports the HP core to jump to the RTC memory to execute stub code after waking up from deepsleep. //TODO: [ESP32H21] IDF-11515
#define ESP_ROM_HAS_OUTPUT_PUTC_FUNC        (1) // ROM has esp_rom_output_putc (or ets_write_char_uart)
#define ESP_ROM_HAS_SUBOPTIMAL_NEWLIB_ON_MISALIGNED_MEMORY  (1) // ROM mem/str functions are not optimized well for misaligned memory access.
#define ESP_ROM_NO_USB_SERIAL_OUTPUT_API    (1) // ROM does not export the usb-serial-jtag write char function
