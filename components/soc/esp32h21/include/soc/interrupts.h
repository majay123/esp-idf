/*
 * SPDX-FileCopyrightText: 2024 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#pragma once

#include <stdint.h>

#ifdef __cplusplus
extern "C"
{
#endif

//Interrupt hardware source table
//This table is decided by hardware, don't touch this.
typedef enum {
    ETS_PMU_INTR_SOURCE,
    ETS_EFUSE_INTR_SOURCE,
    ETS_LP_RTC_TIMER_INTR_SOURCE,
    ETS_LP_BLE_TIMER_INTR_SOURCE,
    ETS_LP_WDT_INTR_SOURCE,
    ETS_LP_PERI_TIMEOUT_INTR_SOURCE,
    ETS_LP_APM_M0_INTR_SOURCE,
    ETS_CPU_INTR_FROM_CPU_0_SOURCE,
    ETS_CPU_INTR_FROM_CPU_1_SOURCE,
    ETS_CPU_INTR_FROM_CPU_2_SOURCE,
    ETS_CPU_INTR_FROM_CPU_3_SOURCE,
    ETS_ASSIST_DEBUG_INTR_SOURCE,
    ETS_TRACE_INTR_SOURCE,
    ETS_CACHE_INTR_SOURCE,
    ETS_CPU_PERI_TIMEOUT_INTR_SOURCE,
    ETS_BT_MAC_INTR_SOURCE,
    ETS_BT_BB_INTR_SOURCE,
    ETS_BT_BB_NMI_SOURCE,
    ETS_COEX_INTR_SOURCE,
    ETS_BLE_TIMER_INTR_SOURCE,
    ETS_BLE_SEC_INTR_SOURCE,
    ETS_ZB_MAC_INTR_SOURCE,
    ETS_GPIO_INTERRUPT_PRO_SOURCE,
    ETS_GPIO_INTERRUPT_PRO_NMI_SOURCE,
    ETS_PAU_INTR_SOURCE,
    ETS_HP_PERI_TIMEOUT_INTR_SOURCE,
    ETS_HP_APM_M0_INTR_SOURCE,
    ETS_HP_APM_M1_INTR_SOURCE,
    ETS_HP_APM_M2_INTR_SOURCE,
    ETS_HP_APM_M3_INTR_SOURCE,
    ETS_MSPI_INTR_SOURCE,
    ETS_I2S1_INTR_SOURCE,
    ETS_UHCI0_INTR_SOURCE,
    ETS_UART0_INTR_SOURCE,
    ETS_UART1_INTR_SOURCE,
    ETS_LEDC_INTR_SOURCE,
    ETS_TWAI0_INTR_SOURCE,
    ETS_USB_SERIAL_JTAG_INTR_SOURCE,
    ETS_RMT_INTR_SOURCE,
    ETS_I2C_EXT0_INTR_SOURCE,
    ETS_I2C_EXT1_INTR_SOURCE,
    ETS_TG0_T0_INTR_SOURCE,
    ETS_TG0_WDT_INTR_SOURCE,
    ETS_TG1_T0_INTR_SOURCE,
    ETS_TG1_WDT_INTR_SOURCE,
    ETS_SYSTIMER_TARGET0_INTR_SOURCE,
    ETS_SYSTIMER_TARGET1_INTR_SOURCE,
    ETS_SYSTIMER_TARGET2_INTR_SOURCE,
    ETS_APB_ADC_INTR_SOURCE,
    ETS_PWM_INTR_SOURCE,
    ETS_PCNT_INTR_SOURCE,
    ETS_PARL_IO_TX_INTR_SOURCE,
    ETS_PARL_IO_RX_INTR_SOURCE,
    ETS_DMA_IN_CH0_INTR_SOURCE,
    ETS_DMA_IN_CH1_INTR_SOURCE,
    ETS_DMA_IN_CH2_INTR_SOURCE,
    ETS_DMA_OUT_CH0_INTR_SOURCE,
    ETS_DMA_OUT_CH1_INTR_SOURCE,
    ETS_DMA_OUT_CH2_INTR_SOURCE,
    ETS_GPSPI2_INTR_SOURCE,
    ETS_AES_INTR_SOURCE,
    ETS_SHA_INTR_SOURCE,
    ETS_RSA_INTR_SOURCE,
    ETS_ECC_INTR_SOURCE,
    ETS_ECDSA_INTR_SOURCE,
    ETS_MAX_INTR_SOURCE,
} periph_interrupt_t;

extern const char * const esp_isr_names[ETS_MAX_INTR_SOURCE];

#ifdef __cplusplus
}
#endif
