/*
 * SPDX-FileCopyrightText: 2025 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Apache-2.0
 */
#include <stdint.h>
#include <stdlib.h>
#include <esp_types.h>
#include "sdkconfig.h"
#include "esp_attr.h"
#include "soc/soc.h"
#include "soc/pmu_struct.h"
#include "hal/pmu_hal.h"
#include "pmu_param.h"
#include "esp_private/esp_pmu.h"
#include "soc/regi2c_pmu.h"
#include "regi2c_ctrl.h"
#include "esp_private/ocode_init.h"
#include "esp_rom_sys.h"

static __attribute__((unused)) const char *TAG = "pmu_init";

typedef struct {
    const pmu_hp_system_power_param_t     *power;
    const pmu_hp_system_clock_param_t     *clock;
    const pmu_hp_system_digital_param_t   *digital;
    pmu_hp_system_analog_param_t          *analog;    //param determined at runtime
    const pmu_hp_system_retention_param_t *retent;
} pmu_hp_system_param_t;

typedef struct {
    const pmu_lp_system_power_param_t  *power;
    pmu_lp_system_analog_param_t       *analog;    //param determined at runtime
} pmu_lp_system_param_t;

pmu_context_t * __attribute__((weak)) IRAM_ATTR PMU_instance(void)
{
    /* It should be explicitly defined in the internal RAM, because this
     * instance will be used in pmu_sleep.c */
    static DRAM_ATTR pmu_hal_context_t pmu_hal = { .dev = &PMU };
    static DRAM_ATTR pmu_sleep_machine_constant_t pmu_mc = PMU_SLEEP_MC_DEFAULT();
    static DRAM_ATTR pmu_context_t pmu_context = { .hal = &pmu_hal, .mc = (void *)&pmu_mc };
    return &pmu_context;
}

void pmu_hp_system_init(pmu_context_t *ctx, pmu_hp_mode_t mode, const pmu_hp_system_param_t *param)
{
    const pmu_hp_system_power_param_t *power = param->power;
    const pmu_hp_system_clock_param_t *clock = param->clock;
    const pmu_hp_system_digital_param_t *dig = param->digital;
    const pmu_hp_system_analog_param_t *anlg = param->analog;
    const pmu_hp_system_retention_param_t *ret = param->retent;

    assert(ctx->hal);
    /* Default configuration of hp-system power in active, modem and sleep modes */
    pmu_ll_hp_set_dig_power(ctx->hal->dev, mode, power->dig_power.val);
    pmu_ll_hp_set_clk_power(ctx->hal->dev, mode, power->clk_power.val);
    pmu_ll_hp_set_xtal_xpd (ctx->hal->dev, mode, power->xtal.xpd_xtal);

    /* Default configuration of hp-system clock in active, modem and sleep modes */
    pmu_ll_hp_set_icg_func          (ctx->hal->dev, mode, clock->icg_func);
    pmu_ll_hp_set_icg_apb           (ctx->hal->dev, mode, clock->icg_apb);
    pmu_ll_hp_set_icg_modem         (ctx->hal->dev, mode, clock->icg_modem.code);
    pmu_ll_hp_set_sysclk_nodiv      (ctx->hal->dev, mode, clock->sysclk.dig_sysclk_nodiv);
    pmu_ll_hp_set_icg_sysclk_enable (ctx->hal->dev, mode, clock->sysclk.icg_sysclk_en);
    pmu_ll_hp_set_sysclk_slp_sel    (ctx->hal->dev, mode, clock->sysclk.sysclk_slp_sel);
    pmu_ll_hp_set_icg_sysclk_slp_sel(ctx->hal->dev, mode, clock->sysclk.icg_slp_sel);
    pmu_ll_hp_set_dig_sysclk        (ctx->hal->dev, mode, clock->sysclk.dig_sysclk_sel);

    /* Default configuration of hp-system digital sub-system in active, modem
     * and sleep modes */
    pmu_ll_hp_set_uart_wakeup_enable(ctx->hal->dev, mode, dig->syscntl.uart_wakeup_en);
    pmu_ll_hp_set_hold_all_lp_pad   (ctx->hal->dev, mode, dig->syscntl.lp_pad_hold_all);
    pmu_ll_hp_set_hold_all_hp_pad   (ctx->hal->dev, mode, dig->syscntl.hp_pad_hold_all);
    pmu_ll_hp_set_dig_pad_slp_sel   (ctx->hal->dev, mode, dig->syscntl.dig_pad_slp_sel);
    pmu_ll_hp_set_pause_watchdog    (ctx->hal->dev, mode, dig->syscntl.dig_pause_wdt);
    pmu_ll_hp_set_cpu_stall         (ctx->hal->dev, mode, dig->syscntl.dig_cpu_stall);

    /* Default configuration of hp-system analog sub-system in active, modem and
     * sleep modes */
    pmu_ll_hp_set_dcdc_ccm_enable              (ctx->hal->dev, mode, anlg->bias.dcdc_ccm_enb);
    pmu_ll_hp_set_dig_reg_dpcur_bias           (ctx->hal->dev, mode, anlg->bias.dig_reg_dpcur_bias);
    pmu_ll_hp_set_dig_reg_dsfmos               (ctx->hal->dev, mode, anlg->bias.dig_reg_dsfmos);
    pmu_ll_hp_set_dcm_vset                     (ctx->hal->dev, mode, anlg->bias.dcm_vset);
    pmu_ll_hp_set_dcm_mode                     (ctx->hal->dev, mode, anlg->bias.dcm_mode);
    pmu_ll_hp_set_bias_xpd                     (ctx->hal->dev, mode, anlg->bias.xpd_bias);
    pmu_ll_hp_set_trx_xpd                      (ctx->hal->dev, mode, anlg->bias.xpd_trx);
    pmu_ll_hp_set_current_power_off            (ctx->hal->dev, mode, anlg->bias.pd_cur);
    pmu_ll_hp_set_bias_sleep_enable            (ctx->hal->dev, mode, anlg->bias.bias_sleep);
    if (mode == PMU_MODE_HP_ACTIVE) {
        pmu_ll_hp_set_regulator_lp_dbias_voltage(ctx->hal->dev, mode, anlg->regulator0.lp_dbias_vol);
        pmu_ll_hp_set_regulator_hp_dbias_voltage(ctx->hal->dev, mode, anlg->regulator0.hp_dbias_vol);
        pmu_ll_hp_set_regulator_dbias_select    (ctx->hal->dev, mode, anlg->regulator0.dbias_sel);
        pmu_ll_hp_set_regulator_dbias_init      (ctx->hal->dev, mode, anlg->regulator0.dbias_init);
    }
    pmu_ll_hp_set_regulator_power_detect_bypass(ctx->hal->dev, mode, anlg->regulator0.power_det_bypass);
    pmu_ll_hp_set_regulator_sleep_memory_xpd   (ctx->hal->dev, mode, anlg->regulator0.slp_mem_xpd);
    pmu_ll_hp_set_regulator_sleep_logic_xpd    (ctx->hal->dev, mode, anlg->regulator0.slp_logic_xpd);
    pmu_ll_hp_set_regulator_xpd                (ctx->hal->dev, mode, anlg->regulator0.xpd);
    pmu_ll_hp_set_regulator_sleep_memory_dbias (ctx->hal->dev, mode, anlg->regulator0.slp_mem_dbias);
    pmu_ll_hp_set_regulator_sleep_logic_dbias  (ctx->hal->dev, mode, anlg->regulator0.slp_logic_dbias);
    pmu_ll_hp_set_regulator_dbias              (ctx->hal->dev, mode, anlg->regulator0.dbias);
    pmu_ll_hp_set_regulator_driver_bar         (ctx->hal->dev, mode, anlg->regulator1.drv_b);

    /* Default configuration of hp-system retention sub-system in active, modem
     * and sleep modes */
    pmu_ll_hp_set_retention_param(ctx->hal->dev, mode, ret->retention.val);
    pmu_ll_hp_set_backup_icg_func(ctx->hal->dev, mode, ret->backup_clk);

    /* Some PMU initial parameter configuration */
    pmu_ll_imm_update_dig_icg_modem_code(ctx->hal->dev, true);
    pmu_ll_imm_update_dig_icg_switch(ctx->hal->dev, true);

    pmu_ll_hp_set_sleep_protect_mode(ctx->hal->dev, PMU_SLEEP_PROTECT_HP_LP_SLEEP);
}

void pmu_lp_system_init(pmu_context_t *ctx, pmu_lp_mode_t mode, const pmu_lp_system_param_t *param)
{
    const pmu_lp_system_power_param_t *power = param->power;
    const pmu_lp_system_analog_param_t *anlg = param->analog;

    assert(ctx->hal);
    /* Default configuration of lp-system power in active and sleep modes */
    pmu_ll_lp_set_dig_power(ctx->hal->dev, mode, power->dig_power.val);
    pmu_ll_lp_set_clk_power(ctx->hal->dev, mode, power->clk_power.val);
    pmu_ll_lp_set_xtal_xpd (ctx->hal->dev, PMU_MODE_LP_SLEEP, power->xtal.xpd_xtal);

    /* Default configuration of lp-system analog sub-system in active and
     * sleep modes */
    if (mode == PMU_MODE_LP_SLEEP) {
        pmu_ll_lp_set_dcdc_ccm_enable   (ctx->hal->dev, mode, anlg->bias.dcdc_ccm_enb);
        pmu_ll_lp_set_dig_reg_dpcur_bias(ctx->hal->dev, mode, anlg->bias.dig_reg_dpcur_bias);
        pmu_ll_lp_set_dig_reg_dsfmos    (ctx->hal->dev, mode, anlg->bias.dig_reg_dsfmos);
        pmu_ll_lp_set_dcm_vset          (ctx->hal->dev, mode, anlg->bias.dcm_vset);
        pmu_ll_lp_set_dcm_mode          (ctx->hal->dev, mode, anlg->bias.dcm_mode);
        pmu_ll_lp_set_bias_xpd          (ctx->hal->dev, mode, anlg->bias.xpd_bias);
        pmu_ll_lp_set_current_power_off (ctx->hal->dev, mode, anlg->bias.pd_cur);
        pmu_ll_lp_set_bias_sleep_enable (ctx->hal->dev, mode, anlg->bias.bias_sleep);
    }
    pmu_ll_lp_set_regulator_slp_xpd    (ctx->hal->dev, mode, anlg->regulator0.slp_xpd);
    pmu_ll_lp_set_regulator_xpd        (ctx->hal->dev, mode, anlg->regulator0.xpd);
    pmu_ll_lp_set_regulator_sleep_dbias(ctx->hal->dev, mode, anlg->regulator0.slp_dbias);
    pmu_ll_lp_set_regulator_dbias      (ctx->hal->dev, mode, anlg->regulator0.dbias);
    pmu_ll_lp_set_regulator_driver_bar (ctx->hal->dev, mode, anlg->regulator1.drv_b);
}

static inline void pmu_power_domain_force_default(pmu_context_t *ctx)
{
    assert(ctx);
    // for bypass reserved power domain
    const pmu_hp_power_domain_t pmu_hp_domains[] = {
        PMU_HP_PD_TOP,
        PMU_HP_PD_CPU,
        PMU_HP_PD_WIFI
    };

    for (uint8_t idx = 0; idx < (sizeof(pmu_hp_domains) / sizeof(pmu_hp_power_domain_t)); idx++) {
        pmu_ll_hp_set_power_force_power_up  (ctx->hal->dev, pmu_hp_domains[idx], false);
        pmu_ll_hp_set_power_force_no_reset  (ctx->hal->dev, pmu_hp_domains[idx], false);
        pmu_ll_hp_set_power_force_no_isolate(ctx->hal->dev, pmu_hp_domains[idx], false);
        pmu_ll_hp_set_power_force_power_down(ctx->hal->dev, pmu_hp_domains[idx], false);
        pmu_ll_hp_set_power_force_isolate   (ctx->hal->dev, pmu_hp_domains[idx], false);
        pmu_ll_hp_set_power_force_reset     (ctx->hal->dev, pmu_hp_domains[idx], false);
    }

    /* Isolate all memory banks while sleeping, avoid memory leakage current */
    pmu_ll_hp_set_memory_no_isolate     (ctx->hal->dev, 0);

    pmu_ll_lp_set_power_force_power_up  (ctx->hal->dev, false);
    pmu_ll_lp_set_power_force_no_reset  (ctx->hal->dev, false);
    pmu_ll_lp_set_power_force_no_isolate(ctx->hal->dev, false);
    pmu_ll_lp_set_power_force_power_down(ctx->hal->dev, false);
    pmu_ll_lp_set_power_force_isolate   (ctx->hal->dev, false);
    pmu_ll_lp_set_power_force_reset     (ctx->hal->dev, false);
}

static inline void pmu_hp_system_param_default(pmu_hp_mode_t mode, pmu_hp_system_param_t *param)
{
    assert (param->analog);

    param->power = pmu_hp_system_power_param_default(mode);
    param->clock = pmu_hp_system_clock_param_default(mode);
    param->digital = pmu_hp_system_digital_param_default(mode);
    *param->analog = *pmu_hp_system_analog_param_default(mode); //copy default value
    param->retent = pmu_hp_system_retention_param_default(mode);

    if (mode == PMU_MODE_HP_ACTIVE || mode == PMU_MODE_HP_MODEM) {
        param->analog->regulator0.dbias = get_act_hp_dbias();
    }
}

static void pmu_hp_system_init_default(pmu_context_t *ctx)
{
    assert(ctx);
    for (pmu_hp_mode_t mode = PMU_MODE_HP_ACTIVE; mode < PMU_MODE_HP_MAX; mode++) {
        pmu_hp_system_analog_param_t analog = {};
        pmu_hp_system_param_t param = {.analog = &analog};

        pmu_hp_system_param_default(mode, &param);
        pmu_hp_system_init(ctx, mode, &param);
    }
}

static inline void pmu_lp_system_param_default(pmu_lp_mode_t mode, pmu_lp_system_param_t *param)
{
    assert (param->analog);

    param->power = pmu_lp_system_power_param_default(mode);
    *param->analog = *pmu_lp_system_analog_param_default(mode); //copy default value

    if (mode == PMU_MODE_LP_ACTIVE) {
        param->analog->regulator0.dbias = get_act_lp_dbias();
    }
}

static void pmu_lp_system_init_default(pmu_context_t *ctx)
{
    assert(ctx);
    for (pmu_lp_mode_t mode = PMU_MODE_LP_ACTIVE; mode < PMU_MODE_LP_MAX; mode++) {
        pmu_lp_system_analog_param_t analog = {};
        pmu_lp_system_param_t param = {.analog = &analog};

        pmu_lp_system_param_default(mode, &param);
        pmu_lp_system_init(ctx, mode, &param);
    }
}

void pmu_init()
{
    /* No peripheral reg i2c power up required on the target */

    REGI2C_WRITE_MASK(I2C_PMU, I2C_PMU_EN_I2C_RTC_DREG, 0);
    REGI2C_WRITE_MASK(I2C_PMU, I2C_PMU_EN_I2C_DIG_DREG, 0);
    REGI2C_WRITE_MASK(I2C_PMU, I2C_PMU_EN_I2C_RTC_DREG_SLP, 0);
    REGI2C_WRITE_MASK(I2C_PMU, I2C_PMU_EN_I2C_DIG_DREG_SLP, 0);
    REGI2C_WRITE_MASK(I2C_PMU, I2C_PMU_OR_XPD_RTC_REG, 0);
    REGI2C_WRITE_MASK(I2C_PMU, I2C_PMU_OR_XPD_DIG_REG, 0);
    REGI2C_WRITE_MASK(I2C_PMU, I2C_PMU_OR_XPD_TRX, 0);

    WRITE_PERI_REG(PMU_POWER_PD_TOP_CNTL_REG, 0);
    WRITE_PERI_REG(PMU_POWER_PD_HPAON_CNTL_REG, 0);
    WRITE_PERI_REG(PMU_POWER_PD_HPCPU_CNTL_REG, 0);
    WRITE_PERI_REG(PMU_POWER_PD_HPPERI_RESERVE_REG, 0);
    WRITE_PERI_REG(PMU_POWER_PD_HPWIFI_CNTL_REG, 0);
    WRITE_PERI_REG(PMU_POWER_PD_LPPERI_CNTL_REG, 0);

    pmu_hp_system_init_default(PMU_instance());
    pmu_lp_system_init_default(PMU_instance());

    pmu_power_domain_force_default(PMU_instance());

    // default ccm mode
    REG_SET_FIELD(PMU_DCM_CTRL_REG, PMU_DCDC_CCM_SW_EN, 1);
    REG_SET_FIELD(PMU_HP_ACTIVE_BIAS_REG, PMU_HP_ACTIVE_DCDC_CCM_ENB, 0);

#if !CONFIG_IDF_ENV_FPGA
    // TODO: IDF-11548
    // if (esp_rom_get_reset_reason(0) == RESET_REASON_CHIP_POWER_ON) {
    //     esp_ocode_calib_init();
    // }
#endif
}
