/*
 * SPDX-FileCopyrightText: 2024 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Apache-2.0
 */

PROVIDE ( UART0               = 0x60000000 );
PROVIDE ( UART1               = 0x60001000 );
PROVIDE ( SPIMEM0             = 0x60002000 );
PROVIDE ( SPIMEM1             = 0x60003000 );
PROVIDE ( I2C0                = 0x60004000 );
PROVIDE ( I2C1                = 0x60005000 );
PROVIDE ( UHCI0               = 0x60006000 );
PROVIDE ( RMT                 = 0x60007000 );
PROVIDE ( RMTMEM              = 0x60007400 );
PROVIDE ( LEDC                = 0x60008000 );
PROVIDE ( TIMERG0             = 0x60009000 );
PROVIDE ( TIMERG1             = 0x6000A000 );
PROVIDE ( SYSTIMER            = 0x6000B000 );
PROVIDE ( TWAI                = 0x6000C000 );
PROVIDE ( I2S0                = 0x6000D000 );
PROVIDE ( APB_SARADC          = 0x6000E000 );
PROVIDE ( USB_SERIAL_JTAG     = 0x6000F000 );
PROVIDE ( INTMTX              = 0x60010000 );
PROVIDE ( PCNT                = 0x60012000 );
PROVIDE ( SOC_ETM             = 0x60013000 );
PROVIDE ( MCPWM0              = 0x60014000 );
PROVIDE ( PARL_IO             = 0x60015000 );
PROVIDE ( PVT                 = 0x60019000 );
PROVIDE ( GDMA                = 0x60080000 );
PROVIDE ( GPSPI2              = 0x60081000 );
PROVIDE ( AES                 = 0x60088000 );
PROVIDE ( SHA                 = 0x60089000 );
PROVIDE ( RSA                 = 0x6008A000 );
PROVIDE ( ECC                 = 0x6008B000 );
PROVIDE ( DS                  = 0x6008C000 );
PROVIDE ( HMAC                = 0x6008D000 );
PROVIDE ( ECDSA               = 0x6008E000 );
PROVIDE ( IO_MUX              = 0x60090000 );
PROVIDE ( GPIO                = 0x60091000 );
PROVIDE ( GPIO_EXT            = 0x60091E00 );
PROVIDE ( MEM_MONITOR         = 0x60092000 );
PROVIDE ( PAU                 = 0x60093000 );
PROVIDE ( HP_SYSTEM           = 0x60095000 );
PROVIDE ( PCR                 = 0x60096000 );
PROVIDE ( TEE                 = 0x60098000 );
PROVIDE ( HP_APM              = 0x60099000 );
PROVIDE ( LP_APM0             = 0x60099800 );
PROVIDE ( MODEM_SYSCON        = 0x600A5400 );
PROVIDE ( MODEM_LPCON         = 0x600AD000 );
PROVIDE ( PMU                 = 0x600B0000 );
PROVIDE ( LP_CLKRST           = 0x600B0400 );
PROVIDE ( LP_TIMER            = 0x600B0C00 );
PROVIDE ( LP_AON              = 0x600B1000 );
PROVIDE ( LP_WDT              = 0x600B1C00 );
PROVIDE ( LPPERI              = 0x600B2800 );
PROVIDE ( LP_ANA_PERI         = 0x600B2C00 );
PROVIDE ( LP_APM              = 0x600B3800 );
PROVIDE ( EFUSE               = 0x600B4000 );
PROVIDE ( TRACE               = 0x600C0000 );
PROVIDE ( ASSIST_DEBUG        = 0x600C2000 );
PROVIDE ( INTPRI              = 0x600C5000 );
PROVIDE ( CACHE               = 0x600C8000 );
