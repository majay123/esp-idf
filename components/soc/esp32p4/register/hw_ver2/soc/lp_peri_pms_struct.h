/**
 * SPDX-FileCopyrightText: 2025 Espressif Systems (Shanghai) CO LTD
 *
 *  SPDX-License-Identifier: Apache-2.0
 */
#pragma once

#include <stdint.h>
#ifdef __cplusplus
extern "C" {
#endif

/** Group: TEE PMS DATE REG */
/** Type of pms_date register
 *  NA
 */
typedef union {
    struct {
        /** tee_date : R/W; bitpos: [31:0]; default: 2363943;
         *  NA
         */
        uint32_t tee_date:32;
    };
    uint32_t val;
} tee_pms_date_reg_t;


/** Group: TEE PMS CLK EN REG */
/** Type of pms_clk_en register
 *  NA
 */
typedef union {
    struct {
        /** reg_clk_en : R/W; bitpos: [0]; default: 1;
         *  NA
         */
        uint32_t reg_clk_en:1;
        uint32_t reserved_1:31;
    };
    uint32_t val;
} tee_pms_clk_en_reg_t;


/** Group: TEE LP MM PMS REG0 REG */
/** Type of lp_mm_pms_reg0 register
 *  NA
 */
typedef union {
    struct {
        /** reg_lp_mm_lp_sysreg_allow : R/W; bitpos: [0]; default: 1;
         *  NA
         */
        uint32_t reg_lp_mm_lp_sysreg_allow:1;
        /** reg_lp_mm_lp_aonclkrst_allow : R/W; bitpos: [1]; default: 1;
         *  NA
         */
        uint32_t reg_lp_mm_lp_aonclkrst_allow:1;
        /** reg_lp_mm_lp_timer_allow : R/W; bitpos: [2]; default: 1;
         *  NA
         */
        uint32_t reg_lp_mm_lp_timer_allow:1;
        /** reg_lp_mm_lp_anaperi_allow : R/W; bitpos: [3]; default: 1;
         *  NA
         */
        uint32_t reg_lp_mm_lp_anaperi_allow:1;
        /** reg_lp_mm_lp_pmu_allow : R/W; bitpos: [4]; default: 1;
         *  NA
         */
        uint32_t reg_lp_mm_lp_pmu_allow:1;
        /** reg_lp_mm_lp_wdt_allow : R/W; bitpos: [5]; default: 1;
         *  NA
         */
        uint32_t reg_lp_mm_lp_wdt_allow:1;
        /** reg_lp_mm_lp_mailbox_allow : R/W; bitpos: [6]; default: 1;
         *  NA
         */
        uint32_t reg_lp_mm_lp_mailbox_allow:1;
        /** reg_lp_mm_lp_rtc_allow : R/W; bitpos: [7]; default: 1;
         *  NA
         */
        uint32_t reg_lp_mm_lp_rtc_allow:1;
        /** reg_lp_mm_lp_periclkrst_allow : R/W; bitpos: [8]; default: 1;
         *  NA
         */
        uint32_t reg_lp_mm_lp_periclkrst_allow:1;
        /** reg_lp_mm_lp_uart_allow : R/W; bitpos: [9]; default: 1;
         *  NA
         */
        uint32_t reg_lp_mm_lp_uart_allow:1;
        /** reg_lp_mm_lp_i2c_allow : R/W; bitpos: [10]; default: 1;
         *  NA
         */
        uint32_t reg_lp_mm_lp_i2c_allow:1;
        /** reg_lp_mm_lp_spi_allow : R/W; bitpos: [11]; default: 1;
         *  NA
         */
        uint32_t reg_lp_mm_lp_spi_allow:1;
        /** reg_lp_mm_lp_i2cmst_allow : R/W; bitpos: [12]; default: 1;
         *  NA
         */
        uint32_t reg_lp_mm_lp_i2cmst_allow:1;
        /** reg_lp_mm_lp_i2s_allow : R/W; bitpos: [13]; default: 1;
         *  NA
         */
        uint32_t reg_lp_mm_lp_i2s_allow:1;
        /** reg_lp_mm_lp_adc_allow : R/W; bitpos: [14]; default: 1;
         *  NA
         */
        uint32_t reg_lp_mm_lp_adc_allow:1;
        /** reg_lp_mm_lp_touch_allow : R/W; bitpos: [15]; default: 1;
         *  NA
         */
        uint32_t reg_lp_mm_lp_touch_allow:1;
        /** reg_lp_mm_lp_iomux_allow : R/W; bitpos: [16]; default: 1;
         *  NA
         */
        uint32_t reg_lp_mm_lp_iomux_allow:1;
        /** reg_lp_mm_lp_intr_allow : R/W; bitpos: [17]; default: 1;
         *  NA
         */
        uint32_t reg_lp_mm_lp_intr_allow:1;
        /** reg_lp_mm_lp_efuse_allow : R/W; bitpos: [18]; default: 1;
         *  NA
         */
        uint32_t reg_lp_mm_lp_efuse_allow:1;
        /** reg_lp_mm_lp_pms_allow : R/W; bitpos: [19]; default: 1;
         *  NA
         */
        uint32_t reg_lp_mm_lp_pms_allow:1;
        /** reg_lp_mm_hp2lp_pms_allow : R/W; bitpos: [20]; default: 1;
         *  NA
         */
        uint32_t reg_lp_mm_hp2lp_pms_allow:1;
        /** reg_lp_mm_lp_tsens_allow : R/W; bitpos: [21]; default: 1;
         *  NA
         */
        uint32_t reg_lp_mm_lp_tsens_allow:1;
        /** reg_lp_mm_lp_huk_allow : R/W; bitpos: [22]; default: 1;
         *  NA
         */
        uint32_t reg_lp_mm_lp_huk_allow:1;
        /** reg_lp_mm_lp_tcm_ram_allow : R/W; bitpos: [23]; default: 1;
         *  NA
         */
        uint32_t reg_lp_mm_lp_tcm_ram_allow:1;
        /** reg_lp_mm_lp_trng_allow : R/W; bitpos: [24]; default: 1;
         *  NA
         */
        uint32_t reg_lp_mm_lp_trng_allow:1;
        uint32_t reserved_25:7;
    };
    uint32_t val;
} tee_lp_mm_pms_reg0_reg_t;


/** Group: TEE PERI REGION0 LOW REG */
/** Type of peri_region0_low register
 *  NA
 */
typedef union {
    struct {
        uint32_t reserved_0:2;
        /** reg_peri_region0_low : R/W; bitpos: [31:2]; default: 0;
         *  NA
         */
        uint32_t reg_peri_region0_low:30;
    };
    uint32_t val;
} tee_peri_region0_low_reg_t;


/** Group: TEE PERI REGION0 HIGH REG */
/** Type of peri_region0_high register
 *  NA
 */
typedef union {
    struct {
        uint32_t reserved_0:2;
        /** reg_peri_region0_high : R/W; bitpos: [31:2]; default: 1073741823;
         *  NA
         */
        uint32_t reg_peri_region0_high:30;
    };
    uint32_t val;
} tee_peri_region0_high_reg_t;


/** Group: TEE PERI REGION1 LOW REG */
/** Type of peri_region1_low register
 *  NA
 */
typedef union {
    struct {
        uint32_t reserved_0:2;
        /** reg_peri_region1_low : R/W; bitpos: [31:2]; default: 0;
         *  NA
         */
        uint32_t reg_peri_region1_low:30;
    };
    uint32_t val;
} tee_peri_region1_low_reg_t;


/** Group: TEE PERI REGION1 HIGH REG */
/** Type of peri_region1_high register
 *  NA
 */
typedef union {
    struct {
        uint32_t reserved_0:2;
        /** reg_peri_region1_high : R/W; bitpos: [31:2]; default: 1073741823;
         *  NA
         */
        uint32_t reg_peri_region1_high:30;
    };
    uint32_t val;
} tee_peri_region1_high_reg_t;


/** Group: TEE PERI REGION PMS REG */
/** Type of peri_region_pms register
 *  NA
 */
typedef union {
    struct {
        /** reg_lp_core_region_pms : R/W; bitpos: [1:0]; default: 3;
         *  NA
         */
        uint32_t reg_lp_core_region_pms:2;
        /** reg_hp_core0_um_region_pms : R/W; bitpos: [3:2]; default: 3;
         *  NA
         */
        uint32_t reg_hp_core0_um_region_pms:2;
        /** reg_hp_core0_mm_region_pms : R/W; bitpos: [5:4]; default: 3;
         *  NA
         */
        uint32_t reg_hp_core0_mm_region_pms:2;
        /** reg_hp_core1_um_region_pms : R/W; bitpos: [7:6]; default: 3;
         *  NA
         */
        uint32_t reg_hp_core1_um_region_pms:2;
        /** reg_hp_core1_mm_region_pms : R/W; bitpos: [9:8]; default: 3;
         *  NA
         */
        uint32_t reg_hp_core1_mm_region_pms:2;
        uint32_t reserved_10:22;
    };
    uint32_t val;
} tee_peri_region_pms_reg_t;


/** Group: TEE PERI REGION 2 TO 7 PMS REG */
/** Type of peri_region_2_to_7_pms register
 *  NA
 */
typedef union {
    struct {
        /** reg_lp_core_region_2_to_7_pms : R/W; bitpos: [5:0]; default: 63;
         *  NA
         */
        uint32_t reg_lp_core_region_2_to_7_pms:6;
        /** reg_hp_core0_um_region_2_to_7_pms : R/W; bitpos: [11:6]; default: 63;
         *  NA
         */
        uint32_t reg_hp_core0_um_region_2_to_7_pms:6;
        /** reg_hp_core0_mm_region_2_to_7_pms : R/W; bitpos: [17:12]; default: 63;
         *  NA
         */
        uint32_t reg_hp_core0_mm_region_2_to_7_pms:6;
        /** reg_hp_core1_um_region_2_to_7_pms : R/W; bitpos: [23:18]; default: 63;
         *  NA
         */
        uint32_t reg_hp_core1_um_region_2_to_7_pms:6;
        /** reg_hp_core1_mm_region_2_to_7_pms : R/W; bitpos: [29:24]; default: 63;
         *  NA
         */
        uint32_t reg_hp_core1_mm_region_2_to_7_pms:6;
        uint32_t reserved_30:2;
    };
    uint32_t val;
} tee_peri_region_2_to_7_pms_reg_t;


/** Group: TEE PERI REGION2 LOW REG */
/** Type of peri_region2_low register
 *  NA
 */
typedef union {
    struct {
        uint32_t reserved_0:2;
        /** reg_peri_region2_low : R/W; bitpos: [31:2]; default: 0;
         *  NA
         */
        uint32_t reg_peri_region2_low:30;
    };
    uint32_t val;
} tee_peri_region2_low_reg_t;


/** Group: TEE PERI REGION2 HIGH REG */
/** Type of peri_region2_high register
 *  NA
 */
typedef union {
    struct {
        uint32_t reserved_0:2;
        /** reg_peri_region2_high : R/W; bitpos: [31:2]; default: 1073741823;
         *  NA
         */
        uint32_t reg_peri_region2_high:30;
    };
    uint32_t val;
} tee_peri_region2_high_reg_t;


/** Group: TEE PERI REGION3 LOW REG */
/** Type of peri_region3_low register
 *  NA
 */
typedef union {
    struct {
        uint32_t reserved_0:2;
        /** reg_peri_region3_low : R/W; bitpos: [31:2]; default: 0;
         *  NA
         */
        uint32_t reg_peri_region3_low:30;
    };
    uint32_t val;
} tee_peri_region3_low_reg_t;


/** Group: TEE PERI REGION3 HIGH REG */
/** Type of peri_region3_high register
 *  NA
 */
typedef union {
    struct {
        uint32_t reserved_0:2;
        /** reg_peri_region3_high : R/W; bitpos: [31:2]; default: 1073741823;
         *  NA
         */
        uint32_t reg_peri_region3_high:30;
    };
    uint32_t val;
} tee_peri_region3_high_reg_t;


/** Group: TEE PERI REGION4 LOW REG */
/** Type of peri_region4_low register
 *  NA
 */
typedef union {
    struct {
        uint32_t reserved_0:2;
        /** reg_peri_region4_low : R/W; bitpos: [31:2]; default: 0;
         *  NA
         */
        uint32_t reg_peri_region4_low:30;
    };
    uint32_t val;
} tee_peri_region4_low_reg_t;


/** Group: TEE PERI REGION4 HIGH REG */
/** Type of peri_region4_high register
 *  NA
 */
typedef union {
    struct {
        uint32_t reserved_0:2;
        /** reg_peri_region4_high : R/W; bitpos: [31:2]; default: 1073741823;
         *  NA
         */
        uint32_t reg_peri_region4_high:30;
    };
    uint32_t val;
} tee_peri_region4_high_reg_t;


/** Group: TEE PERI REGION5 LOW REG */
/** Type of peri_region5_low register
 *  NA
 */
typedef union {
    struct {
        uint32_t reserved_0:2;
        /** reg_peri_region5_low : R/W; bitpos: [31:2]; default: 0;
         *  NA
         */
        uint32_t reg_peri_region5_low:30;
    };
    uint32_t val;
} tee_peri_region5_low_reg_t;


/** Group: TEE PERI REGION5 HIGH REG */
/** Type of peri_region5_high register
 *  NA
 */
typedef union {
    struct {
        uint32_t reserved_0:2;
        /** reg_peri_region5_high : R/W; bitpos: [31:2]; default: 1073741823;
         *  NA
         */
        uint32_t reg_peri_region5_high:30;
    };
    uint32_t val;
} tee_peri_region5_high_reg_t;


/** Group: TEE PERI REGION6 LOW REG */
/** Type of peri_region6_low register
 *  NA
 */
typedef union {
    struct {
        uint32_t reserved_0:2;
        /** reg_peri_region6_low : R/W; bitpos: [31:2]; default: 0;
         *  NA
         */
        uint32_t reg_peri_region6_low:30;
    };
    uint32_t val;
} tee_peri_region6_low_reg_t;


/** Group: TEE PERI REGION6 HIGH REG */
/** Type of peri_region6_high register
 *  NA
 */
typedef union {
    struct {
        uint32_t reserved_0:2;
        /** reg_peri_region6_high : R/W; bitpos: [31:2]; default: 1073741823;
         *  NA
         */
        uint32_t reg_peri_region6_high:30;
    };
    uint32_t val;
} tee_peri_region6_high_reg_t;


/** Group: TEE PERI REGION7 LOW REG */
/** Type of peri_region7_low register
 *  NA
 */
typedef union {
    struct {
        uint32_t reserved_0:2;
        /** reg_peri_region7_low : R/W; bitpos: [31:2]; default: 0;
         *  NA
         */
        uint32_t reg_peri_region7_low:30;
    };
    uint32_t val;
} tee_peri_region7_low_reg_t;


/** Group: TEE PERI REGION7 HIGH REG */
/** Type of peri_region7_high register
 *  NA
 */
typedef union {
    struct {
        uint32_t reserved_0:2;
        /** reg_peri_region7_high : R/W; bitpos: [31:2]; default: 1073741823;
         *  NA
         */
        uint32_t reg_peri_region7_high:30;
    };
    uint32_t val;
} tee_peri_region7_high_reg_t;


typedef struct {
    volatile tee_pms_date_reg_t pms_date;
    volatile tee_pms_clk_en_reg_t pms_clk_en;
    volatile tee_lp_mm_pms_reg0_reg_t lp_mm_pms_reg0;
    volatile tee_peri_region0_low_reg_t peri_region0_low;
    volatile tee_peri_region0_high_reg_t peri_region0_high;
    volatile tee_peri_region1_low_reg_t peri_region1_low;
    volatile tee_peri_region1_high_reg_t peri_region1_high;
    volatile tee_peri_region_pms_reg_t peri_region_pms;
    volatile tee_peri_region_2_to_7_pms_reg_t peri_region_2_to_7_pms;
    volatile tee_peri_region2_low_reg_t peri_region2_low;
    volatile tee_peri_region2_high_reg_t peri_region2_high;
    volatile tee_peri_region3_low_reg_t peri_region3_low;
    volatile tee_peri_region3_high_reg_t peri_region3_high;
    volatile tee_peri_region4_low_reg_t peri_region4_low;
    volatile tee_peri_region4_high_reg_t peri_region4_high;
    volatile tee_peri_region5_low_reg_t peri_region5_low;
    volatile tee_peri_region5_high_reg_t peri_region5_high;
    volatile tee_peri_region6_low_reg_t peri_region6_low;
    volatile tee_peri_region6_high_reg_t peri_region6_high;
    volatile tee_peri_region7_low_reg_t peri_region7_low;
    volatile tee_peri_region7_high_reg_t peri_region7_high;
} tee_dev_t;

extern tee_dev_t LP_PERI_PMS;

#ifndef __cplusplus
_Static_assert(sizeof(tee_dev_t) == 0x54, "Invalid size of tee_dev_t structure");
#endif

#ifdef __cplusplus
}
#endif
