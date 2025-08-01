/*
 * SPDX-FileCopyrightText: 2024-2025 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Apache-2.0
 */
#pragma once

#ifdef __cplusplus
extern "C" {
#endif

/*
 ************************* ESP32H21 Root Clock Source ****************************
 * 1) Internal 20MHz RC Oscillator: RC_FAST (usually referred as FOSC in TRM and reg. description)
 *
 *    This RC oscillator generates a ~20MHz clock signal output as the RC_FAST_CLK.
 *
 *    The exact frequency of RC_FAST_CLK can be computed in runtime through calibration.
 *
 * 2) External 32MHz Crystal Clock: XTAL
 *
 * 3) Internal 600kHz RC Oscillator: RC_SLOW (usually referred as SOSC in TRM or reg. description)
 *
 *    This RC oscillator generates a ~600kHz clock signal output as the RC_SLOW_CLK. The exact frequency of this clock
 *    can be computed in runtime through calibration.
 *
 * 4) External 32kHz Crystal Clock (optional): XTAL32K
 *
 *    The clock source for this XTAL32K_CLK should be a 32kHz crystal connecting to the XTAL_32K_P and XTAL_32K_N
 *    pins.
 *
 *    XTAL32K_CLK can also be calibrated to get its exact frequency.
 *
 * 5) External Slow Clock (optional): OSC_SLOW
 *
 *    A slow clock signal generated by an external circuit can be connected to GPIO11 to be the clock source for the
 *    RTC_SLOW_CLK.
 *
 *    OSC_SLOW_CLK can also be calibrated to get its exact frequency.
 */

/* The pin number to connect the external slow clock (OSC_SLOW_CLK), XTAL_32K_P */
#define SOC_EXT_OSC_SLOW_GPIO_NUM           11

/* With the default value of CK8M_DFREQ = 860, RC_FAST clock frequency is 20 MHz +/- 7% */
#define SOC_CLK_RC_FAST_FREQ_APPROX         20000000                            /*!< Approximate RC_FAST_CLK frequency in Hz */
#define SOC_CLK_RC_SLOW_FREQ_APPROX         600000                              /*!< Approximate RC_SLOW_CLK frequency in Hz */
#define SOC_CLK_XTAL32K_FREQ_APPROX         32768                               /*!< Approximate XTAL32K_CLK frequency in Hz */
#define SOC_CLK_OSC_SLOW_FREQ_APPROX        32768                               /*!< Approximate OSC_SLOW_CLK (external slow clock) frequency in Hz */

// Naming convention: SOC_ROOT_CLK_{loc}_{type}_[attr]
// {loc}: EXT, INT
// {type}: XTAL, RC
// [attr] - optional: [frequency], FAST, SLOW
/**
 * @brief Root clock
 */
typedef enum {
    SOC_ROOT_CLK_INT_RC_FAST,          /*!< Internal 20MHz RC oscillator */
    SOC_ROOT_CLK_INT_RC_SLOW,          /*!< Internal 600kHz RC oscillator */
    SOC_ROOT_CLK_EXT_XTAL,             /*!< External 32MHz crystal */
    SOC_ROOT_CLK_EXT_XTAL32K,          /*!< External 32kHz crystal/clock signal */
    SOC_ROOT_CLK_EXT_OSC_SLOW,         /*!< External slow clock signal at pin11 */
} soc_root_clk_t;

/**
 * @brief ROOT clock circuit, which requires explicitly enabling the targeting circuit to use
 */
typedef enum {
    SOC_ROOT_CIRCUIT_CLK_BBPLL,        /*!< BBPLL_CLK is the output of the PLL generator circuit */
    // SOC_ROOT_CIRCUIT_CLK_XTAL_X2,      /*!< XTAL_X2_CLK is the output of the XTAL_X2 generator circuit */
} soc_root_clk_circuit_t;

/**
 * @brief CPU_CLK mux inputs, which are the supported clock sources for the CPU_CLK
 * @note Enum values are matched with the register field values on purpose
 */
typedef enum {
    SOC_CPU_CLK_SRC_XTAL = 0,              /*!< Select XTAL_CLK as CPU_CLK source */
    SOC_CPU_CLK_SRC_PLL = 1,               /*!< Select PLL_CLK as CPU_CLK source (PLL_CLK is one of the outputs of 32MHz crystal oscillator frequency multiplier, 96MHz) */
    SOC_CPU_CLK_SRC_RC_FAST = 2,           /*!< Select RC_FAST_CLK as CPU_CLK source */
    // SOC_CPU_CLK_SRC_XTAL_X2 = 3,           /*!< Select XTAL_X2_CLK as CPU_CLK source (XTAL_X2_CLK is the other output of 32MHz crystal oscillator frequency multiplier, 64MHz) */
    SOC_CPU_CLK_SRC_INVALID,               /*!< Invalid CPU_CLK source */
} soc_cpu_clk_src_t;

/**
 * @brief RTC_SLOW_CLK mux inputs, which are the supported clock sources for the RTC_SLOW_CLK
 * @note Enum values are matched with the register field values on purpose
 */
typedef enum {
    SOC_RTC_SLOW_CLK_SRC_RC_SLOW_D4 = 0,   /*!< Select RC_SLOW_D4_CLK as RTC_SLOW_CLK source */
    SOC_RTC_SLOW_CLK_SRC_XTAL32K = 1,      /*!< Select XTAL32K_CLK as RTC_SLOW_CLK source */
    SOC_RTC_SLOW_CLK_SRC_OSC_SLOW = 3,     /*!< Select OSC_SLOW_CLK (external slow clock) as RTC_SLOW_CLK source */
    SOC_RTC_SLOW_CLK_SRC_INVALID,          /*!< Invalid RTC_SLOW_CLK source */

    SOC_RTC_SLOW_CLK_SRC_DEFAULT = SOC_RTC_SLOW_CLK_SRC_RC_SLOW_D4, /*!< RC_SLOW_CLK is the default clock source for RTC_SLOW_CLK */
} soc_rtc_slow_clk_src_t;

/**
 * @brief RTC_FAST_CLK mux inputs, which are the supported clock sources for the RTC_FAST_CLK
 * @note Enum values are matched with the register field values on purpose
 */
typedef enum {
    SOC_RTC_FAST_CLK_SRC_RC_FAST = 0,      /*!< Select RC_FAST_CLK as RTC_FAST_CLK source */
    SOC_RTC_FAST_CLK_SRC_XTAL_D2 = 1,      /*!< Select XTAL_D2_CLK (may referred as XTAL_CLK_DIV_2) as RTC_FAST_CLK source */
    SOC_RTC_FAST_CLK_SRC_INVALID,          /*!< Invalid RTC_FAST_CLK source */

    SOC_RTC_FAST_CLK_SRC_DEFAULT = SOC_RTC_FAST_CLK_SRC_XTAL_D2, /*!< XTAL_D2_CLK is the default clock source for RTC_FAST_CLK */
} soc_rtc_fast_clk_src_t;

/**
 * @brief Possible main XTAL frequency options on the target
 * @note Enum values equal to the frequency value in MHz
 * @note Not all frequency values listed here are supported in IDF. Please check SOC_XTAL_SUPPORT_XXX in soc_caps.h for
 *       the supported ones.
 */
typedef enum {
    SOC_XTAL_FREQ_32M = 32,                /*!< 32MHz XTAL */
} soc_xtal_freq_t;

// Naming convention: SOC_MOD_CLK_{[upstream]clock_name}_[attr]
// {[upstream]clock_name}: XTAL, (BB)PLL, etc.
// [attr] - optional: FAST, SLOW, D<divider>, F<freq>
/**
 * @brief Supported clock sources for modules (CPU, peripherals, RTC, etc.)
 *
 * @note enum starts from 1, to save 0 for special purpose
 */
typedef enum {
    // For CPU domain
    SOC_MOD_CLK_CPU = 1,                       /*!< CPU_CLK can be sourced from XTAL, PLL, RC_FAST, or FLASH_PLL by configuring soc_cpu_clk_src_t */
    // For RTC domain
    SOC_MOD_CLK_RTC_FAST,                      /*!< RTC_FAST_CLK can be sourced from XTAL_D2, RC_FAST, or LP_PLL by configuring soc_rtc_fast_clk_src_t */
    SOC_MOD_CLK_RTC_SLOW,                      /*!< RTC_SLOW_CLK can be sourced from RC_SLOW, XTAL32K, OSC_SLOW, or RC32K by configuring soc_rtc_slow_clk_src_t */
    // For digital domain: peripherals, BLE
    SOC_MOD_CLK_PLL_F48M,                      /*!< PLL_F48M_CLK is derived from PLL (clock gating + fixed divider of 2), it has a fixed frequency of 48MHz */
    // SOC_MOD_CLK_XTAL_X2_F64M,                  /*!< XTAL_X2_F64M_CLK is derived from XTAL_X2 (clock gating), it has a fixed frequency of 64MHz */
    SOC_MOD_CLK_PLL_F96M,                      /*!< PLL_F96M_CLK is derived from PLL (clock gating), it has a fixed frequency of 96MHz */
    SOC_MOD_CLK_XTAL32K,                       /*!< XTAL32K_CLK comes from the external 32kHz crystal, passing a clock gating to the peripherals */
    SOC_MOD_CLK_RC_FAST,                       /*!< RC_FAST_CLK comes from the internal 20MHz rc oscillator, passing a clock gating to the peripherals */
    SOC_MOD_CLK_XTAL,                          /*!< XTAL_CLK comes from the external 32MHz crystal */
    SOC_MOD_CLK_INVALID,                       /*!< Indication of the end of the available module clock sources */
} soc_module_clk_t;

//////////////////////////////////////////////////SYSTIMER///////////////////////////////////////////////////////////////

/**
 * @brief Type of SYSTIMER clock source
 */
typedef enum {
    SYSTIMER_CLK_SRC_XTAL = SOC_MOD_CLK_XTAL,       /*!< SYSTIMER source clock is XTAL */
    SYSTIMER_CLK_SRC_RC_FAST = SOC_MOD_CLK_RC_FAST, /*!< SYSTIMER source clock is RC_FAST */
    SYSTIMER_CLK_SRC_DEFAULT = SOC_MOD_CLK_XTAL,    /*!< SYSTIMER source clock default choice is XTAL */
} soc_periph_systimer_clk_src_t;

//////////////////////////////////////////////////GPTimer///////////////////////////////////////////////////////////////

/**
 * @brief Array initializer for all supported clock sources of GPTimer
 *
 * The following code can be used to iterate all possible clocks:
 * @code{c}
 * soc_periph_gptimer_clk_src_t gptimer_clks[] = (soc_periph_gptimer_clk_src_t)SOC_GPTIMER_CLKS;
 * for (size_t i = 0; i< sizeof(gptimer_clks) / sizeof(gptimer_clks[0]); i++) {
 *     soc_periph_gptimer_clk_src_t clk = gptimer_clks[i];
 *     // Test GPTimer with the clock `clk`
 * }
 * @endcode
 */
#if SOC_CLK_TREE_SUPPORTED
#define SOC_GPTIMER_CLKS {SOC_MOD_CLK_PLL_F48M, SOC_MOD_CLK_RC_FAST, SOC_MOD_CLK_XTAL}
#else
#define SOC_GPTIMER_CLKS {SOC_MOD_CLK_XTAL}
#endif

/**
 * @brief Type of GPTimer clock source
 */
typedef enum {
    GPTIMER_CLK_SRC_PLL_F48M = SOC_MOD_CLK_PLL_F48M, /*!< Select PLL_F48M as the source clock */
    GPTIMER_CLK_SRC_RC_FAST = SOC_MOD_CLK_RC_FAST,   /*!< Select RC_FAST as the source clock */
    GPTIMER_CLK_SRC_XTAL = SOC_MOD_CLK_XTAL,         /*!< Select XTAL as the source clock */
#if SOC_CLK_TREE_SUPPORTED
    GPTIMER_CLK_SRC_DEFAULT = SOC_MOD_CLK_PLL_F48M,  /*!< Select PLL_F48M as the default choice */
#else
    GPTIMER_CLK_SRC_DEFAULT = SOC_MOD_CLK_XTAL,      /*!< Select XTAL as the default choice if no clk_tree */
#endif
} soc_periph_gptimer_clk_src_t;

/**
 * @brief Type of Timer Group clock source, reserved for the legacy timer group driver
 */
typedef enum {
    TIMER_SRC_CLK_PLL_F48M = SOC_MOD_CLK_PLL_F48M,     /*!< Timer group clock source is PLL_F48M */
    TIMER_SRC_CLK_XTAL = SOC_MOD_CLK_XTAL,             /*!< Timer group clock source is XTAL */
#if SOC_CLK_TREE_SUPPORTED
    TIMER_SRC_CLK_DEFAULT = SOC_MOD_CLK_PLL_F48M,      /*!< Select PLL_F48M as the default choice */
#else
    TIMER_SRC_CLK_DEFAULT = SOC_MOD_CLK_XTAL,          /*!< Select XTAL as the default choice if no clk_tree */
#endif
} soc_periph_tg_clk_src_legacy_t;

//////////////////////////////////////////////////RMT///////////////////////////////////////////////////////////////////

/**
 * @brief Array initializer for all supported clock sources of RMT
 */
#define SOC_RMT_CLKS {SOC_MOD_CLK_XTAL, SOC_MOD_CLK_RC_FAST}

/**
 * @brief Type of RMT clock source
 */
typedef enum {
    RMT_CLK_SRC_RC_FAST = SOC_MOD_CLK_RC_FAST,   /*!< Select RC_FAST as the source clock */
    RMT_CLK_SRC_XTAL = SOC_MOD_CLK_XTAL,         /*!< Select XTAL as the source clock */
    RMT_CLK_SRC_DEFAULT = SOC_MOD_CLK_XTAL,      /*!< Select XTAL as the default choice */
} soc_periph_rmt_clk_src_t;

/**
 * @brief Type of RMT clock source, reserved for the legacy RMT driver
 */
typedef enum {
    RMT_BASECLK_XTAL = SOC_MOD_CLK_XTAL,    /*!< RMT source clock is XTAL */
    RMT_BASECLK_DEFAULT = SOC_MOD_CLK_XTAL, /*!< RMT source clock default choice is XTAL */
} soc_periph_rmt_clk_src_legacy_t;

///////////////////////////////////////////////////UART/////////////////////////////////////////////////////////////////

/**
 * @brief Array initializer for all supported clock sources of UART
 */
#if SOC_CLK_TREE_SUPPORTED
#define SOC_UART_CLKS {SOC_MOD_CLK_PLL_F48M, SOC_MOD_CLK_XTAL, SOC_MOD_CLK_RC_FAST}
#else
#define SOC_UART_CLKS {SOC_MOD_CLK_XTAL}
#endif

/**
 * @brief Type of UART clock source, reserved for the legacy UART driver
 */
typedef enum {
    UART_SCLK_PLL_F48M = SOC_MOD_CLK_PLL_F48M,     /*!< UART source clock is PLL_F48M */
    UART_SCLK_RTC = SOC_MOD_CLK_RC_FAST,           /*!< UART source clock is RC_FAST */
    UART_SCLK_XTAL = SOC_MOD_CLK_XTAL,             /*!< UART source clock is XTAL */
#if SOC_CLK_TREE_SUPPORTED
    UART_SCLK_DEFAULT = SOC_MOD_CLK_PLL_F48M,      /*!< Select PLL_F48M as the default choice */
#else
    UART_SCLK_DEFAULT = SOC_MOD_CLK_XTAL,          /*!< Select XTAL as the default choice if no clk_tree */
#endif
} soc_periph_uart_clk_src_legacy_t;

/////////////////////////////////////////////////I2C////////////////////////////////////////////////////////////////////

/**
 * @brief Array initializer for all supported clock sources of I2C
 */
#define SOC_I2C_CLKS {SOC_MOD_CLK_XTAL, SOC_MOD_CLK_RC_FAST}

/**
 * @brief Type of I2C clock source.
 */
typedef enum {
    I2C_CLK_SRC_XTAL = SOC_MOD_CLK_XTAL,                        /*!< Select XTAL as the source clock */
    I2C_CLK_SRC_RC_FAST = SOC_MOD_CLK_RC_FAST,                  /*!< Select RC_FAST as the source clock */
    I2C_CLK_SRC_DEFAULT = SOC_MOD_CLK_XTAL,                     /*!< Select XTAL as the default source clock */
} soc_periph_i2c_clk_src_t;

/////////////////////////////////////////////////SPI////////////////////////////////////////////////////////////////////

/**
 * @brief Array initializer for all supported clock sources of SPI
 */
#if SOC_CLK_TREE_SUPPORTED
#define SOC_SPI_CLKS {SOC_MOD_CLK_RC_FAST, SOC_MOD_CLK_PLL_F48M, SOC_MOD_CLK_XTAL}
#else
#define SOC_SPI_CLKS {SOC_MOD_CLK_XTAL}
#endif

/**
 * @brief Type of SPI clock source.
 */
typedef enum {
#if SOC_CLK_TREE_SUPPORTED
    SPI_CLK_SRC_DEFAULT = SOC_MOD_CLK_PLL_F48M,     /*!< Select PLL_48M as SPI source clock */
#else
    SPI_CLK_SRC_DEFAULT = SOC_MOD_CLK_XTAL,         /*!< Select XTAL as SPI source clock */
#endif
    SPI_CLK_SRC_PLL_F48M = SOC_MOD_CLK_PLL_F48M,    /*!< Select PLL_48M as SPI source clock */
    SPI_CLK_SRC_XTAL = SOC_MOD_CLK_XTAL,            /*!< Select XTAL as SPI source clock */
    SPI_CLK_SRC_RC_FAST = SOC_MOD_CLK_RC_FAST,      /*!< Select RC_FAST as SPI source clock */
} soc_periph_spi_clk_src_t;

//////////////////////////////////////////////////MWDT/////////////////////////////////////////////////////////////////

/**
 * @brief Array initializer for all supported clock sources of MWDT
 */
#define SOC_MWDT_CLKS {SOC_MOD_CLK_XTAL, SOC_MOD_CLK_PLL_F48M, SOC_MOD_CLK_RC_FAST}

/**
 * @brief MWDT clock source
 */
typedef enum {
    MWDT_CLK_SRC_XTAL = SOC_MOD_CLK_XTAL,           /*!< Select XTAL as the source clock */
    MWDT_CLK_SRC_PLL_F48M = SOC_MOD_CLK_PLL_F48M,   /*!< Select PLL fixed 48 MHz as the source clock */
    MWDT_CLK_SRC_RC_FAST = SOC_MOD_CLK_RC_FAST,     /*!< Select RTC fast as the source clock */
    MWDT_CLK_SRC_DEFAULT = SOC_MOD_CLK_XTAL,        /*!< Select PLL as the default clock choice */
} soc_periph_mwdt_clk_src_t;

//////////////////////////////////////////////CLOCK OUTPUT///////////////////////////////////////////////////////////
typedef enum {
    CLKOUT_SIG_XTAL    = 5,     /*!< Main crystal oscillator clock */
    CLKOUT_SIG_CPU     = 16,    /*!< CPU clock */
    CLKOUT_SIG_AHB     = 17,    /*!< AHB clock */
    CLKOUT_SIG_APB     = 18,    /*!< APB clock */
    CLKOUT_SIG_XTAL32K = 21,    /*!< External 32kHz crystal clock */
    CLKOUT_SIG_EXT32K  = 22,    /*!< External slow clock input through XTAL_32K_P */
    CLKOUT_SIG_RC_FAST = 23,    /*!< RC fast clock, about 17.5MHz */
    CLKOUT_SIG_RC_32K  = 24,    /*!< Internal slow RC oscillator */
    CLKOUT_SIG_RC_SLOW = 25,    /*!< RC slow clock, depends on the RTC_CLK_SRC configuration */
    CLKOUT_SIG_INVALID = 0xFF,
} soc_clkout_sig_id_t;

//////////////////////////////////////////////////FLASH///////////////////////////////////////////////////////////////////
/**
 * @brief Array initializer for all supported clock sources of FLASH MSPI controller
 */
#define SOC_FLASH_CLKS {SOC_MOD_CLK_XTAL, SOC_MOD_CLK_RC_FAST, SOC_MOD_CLK_PLL_F48M}
/**
 * @brief FLASH MSPI controller clock source
 */
typedef enum {
    FLASH_CLK_SRC_XTAL = SOC_MOD_CLK_XTAL,              /*!< Select XTAL as the source clock */
    FLASH_CLK_SRC_RC_FAST = SOC_MOD_CLK_RC_FAST,        /*!< Select RC_FAST as the source clock */
    // FLASH_CLK_SRC_PLL_F64M = SOC_MOD_CLK_XTAL_X2_F64M,  /*!< Select PLL_F64M as the source clock */
    FLASH_CLK_SRC_PLL_F48M = SOC_MOD_CLK_PLL_F48M,      /*!< Select PLL_F48M as the source clock */
    FLASH_CLK_SRC_DEFAULT = SOC_MOD_CLK_PLL_F48M,       /*!< Select PLL_F48M as the default clock choice */
    FLASH_CLK_SRC_ROM_DEFAULT = SOC_MOD_CLK_XTAL,       /*!< Select XTAL as ROM default clock source */
} soc_periph_flash_clk_src_t;

////////////////////////////////////////////RTC CALIBRATION///////////////////////////////////////////////////////////
/**
 * @brief Clock frequency calibration source selection
 */
typedef enum {
    CLK_CAL_RC_SLOW = 0,                             /*!< Select to calibrate RC_SLOW_CLK */
    CLK_CAL_32K_XTAL,                                /*!< Select to calibrate XTAL32K_CLK */
    CLK_CAL_32K_OSC_SLOW,                            /*!< Select to calibrate OSC_SLOW_CLK (external slow clock) */
    CLK_CAL_RC_FAST,                                 /*!< Select to calibrate RC_FAST_CLK */
} soc_clk_calibration_clk_src_t;

#ifdef __cplusplus
}
#endif
