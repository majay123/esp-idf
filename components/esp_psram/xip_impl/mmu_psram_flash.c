/*
 * SPDX-FileCopyrightText: 2021-2025 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Apache-2.0
 */
/**
 * @Backgrounds
 *
 * This file contains 2 parts:
 * 1. Feature: Copy Flash content to PSRAM. Related APIs are private:
 *    - mmu_config_psram_text_segment()
 *    - mmu_config_psram_rodata_segment()
 *
 * 2. Private APIs used by `flash_mmap.c` and `cache_utils.c`
 *    APIs in 2 are due to lack of MMU driver. There will be an MMU driver to maintain vaddr range.
 *    APIs in 2 will be refactored when MMU driver is ready
 */

#include <stdbool.h>
#include <sys/param.h>
#include "sdkconfig.h"
#include "esp_log.h"
#include "esp_attr.h"
#include "soc/ext_mem_defs.h"
#include "hal/cache_types.h"
#include "hal/cache_ll.h"
#include "esp_private/mmu_psram_flash.h"

#if CONFIG_IDF_TARGET_ESP32S2
#include "esp32s2/rom/cache.h"
#elif CONFIG_IDF_TARGET_ESP32S3
#include "esp32s3/rom/cache.h"
#endif

#define ALIGN_UP_BY(num, align) (((num) + ((align) - 1)) & ~((align) - 1))
#define ALIGN_DOWN_BY(num, align) ((num) & (~((align) - 1)))

/*----------------------------------------------------------------------------
                    Part 1 APIs (See @Backgrounds on top of this file)
-------------------------------------------------------------------------------*/
#if CONFIG_SPIRAM_FETCH_INSTRUCTIONS || CONFIG_SPIRAM_RODATA
//page_size - 1, where page_size on s2 and s3 is always 0x10000. To be refactored by MMU driver
#define INVALID_PHY_PAGE 0xffff
const static char *TAG = "mmu_psram";
//TODO IDF-4387
static uint32_t page0_mapped = 0;
static uint32_t page0_page = INVALID_PHY_PAGE;

/**
 * If using `int`, then for CLANG, with enabled optimization when inlined function is provided with the address of external symbol, the two least bits of the constant used inside that function get cleared.
 * Optimizer assumes that address of external symbol should be aligned to 4-bytes and therefore aligns constant value used for bitwise AND operation with that address.
 *
 * This means `extern int _instruction_reserved_start;` can be unaligned to 4 bytes, whereas using `char` can solve this issue.
 *
 * As we only use these symbol address, we declare them as `char` here
 */
extern char _instruction_reserved_start;
extern char _instruction_reserved_end;
extern char _rodata_reserved_start;
extern char _rodata_reserved_end;
#endif  //#if CONFIG_SPIRAM_FETCH_INSTRUCTIONS || CONFIG_SPIRAM_RODATA

#if CONFIG_SPIRAM_FETCH_INSTRUCTIONS
#define INSTRUCTION_ALIGNMENT_GAP_START ALIGN_UP_BY((uint32_t)&_instruction_reserved_end, 4)
#define INSTRUCTION_ALIGNMENT_GAP_END ALIGN_UP_BY((uint32_t)&_instruction_reserved_end, CONFIG_MMU_PAGE_SIZE)

size_t mmu_psram_get_text_segment_length(void)
{
    uint32_t flash_pages = 0;
#if CONFIG_IDF_TARGET_ESP32S2
    flash_pages += Cache_Count_Flash_Pages(PRO_CACHE_IBUS0, &page0_mapped);
    flash_pages += Cache_Count_Flash_Pages(PRO_CACHE_IBUS1, &page0_mapped);
#elif CONFIG_IDF_TARGET_ESP32S3
    flash_pages += Cache_Count_Flash_Pages(CACHE_IBUS, &page0_mapped);
#endif
    return MMU_PAGE_TO_BYTES(flash_pages);
}

void mmu_psram_get_instruction_alignment_gap_info(uint32_t *gap_start, uint32_t *gap_end)
{
    // As we need the memory to start with word aligned address, max virtual space that could be wasted = 3 bytes
    // Or create a new region from (uint32_t)&_instruction_reserved_end to ALIGN_UP_BY((uint32_t)&_instruction_reserved_end, 4) as only byte-accessible
    *gap_start = INSTRUCTION_ALIGNMENT_GAP_START;
    *gap_end = INSTRUCTION_ALIGNMENT_GAP_END;
}

bool mmu_psram_check_ptr_addr_in_xip_psram_instruction_region(const void *p)
{
    if ((intptr_t)p >= ALIGN_DOWN_BY((uint32_t)&_instruction_reserved_start, CONFIG_MMU_PAGE_SIZE) && (intptr_t)p < ALIGN_UP_BY((uint32_t)&_instruction_reserved_end, CONFIG_MMU_PAGE_SIZE)) {
        return true;
    }

    return false;
}

esp_err_t mmu_config_psram_text_segment(uint32_t start_page, uint32_t psram_size, uint32_t *out_page)
{
    uint32_t page_id = start_page;

    uint32_t flash_bytes = mmu_psram_get_text_segment_length();
    if ((flash_bytes + MMU_PAGE_TO_BYTES(page_id)) > psram_size) {
        ESP_EARLY_LOGE(TAG, "PSRAM space not enough for the Flash instructions, need %" PRIu32 " B, from %" PRIu32 " B to %" PRIu32 " B",
                       flash_bytes, MMU_PAGE_TO_BYTES(start_page), flash_bytes + MMU_PAGE_TO_BYTES(page_id));
        return ESP_FAIL;
    }

    //Enable the most high bus, which is used for copying FLASH .text to PSRAM
    cache_bus_mask_t bus_mask = cache_ll_l1_get_bus(0, SOC_EXTRAM_DATA_HIGH, 0);
    cache_ll_l1_enable_bus(0, bus_mask);
#if !CONFIG_ESP_SYSTEM_SINGLE_CORE_MODE
    bus_mask = cache_ll_l1_get_bus(1, SOC_EXTRAM_DATA_HIGH, 0);
    cache_ll_l1_enable_bus(1, bus_mask);
#endif

    instruction_flash_page_info_init(page_id);

#if CONFIG_IDF_TARGET_ESP32S2
    page_id = Cache_Flash_To_SPIRAM_Copy(PRO_CACHE_IBUS0, SOC_IRAM0_ADDRESS_LOW, page_id, &page0_page);
    page_id = Cache_Flash_To_SPIRAM_Copy(PRO_CACHE_IBUS1, SOC_IRAM1_ADDRESS_LOW, page_id, &page0_page);
#elif CONFIG_IDF_TARGET_ESP32S3
    page_id = Cache_Flash_To_SPIRAM_Copy(CACHE_IBUS, SOC_IRAM0_CACHE_ADDRESS_LOW, page_id, &page0_page);
#endif
    ESP_EARLY_LOGV(TAG, "after copy instruction, page_id is %" PRIu32, page_id);
    ESP_EARLY_LOGI(TAG, "Instructions copied and mapped to SPIRAM");

    *out_page = page_id - start_page;

    return ESP_OK;
}
#endif  //#if CONFIG_SPIRAM_FETCH_INSTRUCTIONS

#if CONFIG_SPIRAM_RODATA
#define RODATA_ALIGNMENT_GAP_START ALIGN_UP_BY((uint32_t)&_rodata_reserved_end, 4)
#define RODATA_ALIGNMENT_GAP_END ALIGN_UP_BY((uint32_t)&_rodata_reserved_end, CONFIG_MMU_PAGE_SIZE)

size_t mmu_psram_get_rodata_segment_length(void)
{
    uint32_t flash_pages = 0;
#if CONFIG_IDF_TARGET_ESP32S2
    flash_pages += Cache_Count_Flash_Pages(PRO_CACHE_IBUS2, &page0_mapped);
    flash_pages += Cache_Count_Flash_Pages(PRO_CACHE_DBUS0, &page0_mapped);
    flash_pages += Cache_Count_Flash_Pages(PRO_CACHE_DBUS1, &page0_mapped);
    flash_pages += Cache_Count_Flash_Pages(PRO_CACHE_DBUS2, &page0_mapped);
#elif CONFIG_IDF_TARGET_ESP32S3
    flash_pages += Cache_Count_Flash_Pages(CACHE_DBUS, &page0_mapped);
#endif
    return MMU_PAGE_TO_BYTES(flash_pages);
}

void mmu_psram_get_rodata_alignment_gap_info(uint32_t *gap_start, uint32_t *gap_end)
{
    // As we need the memory to start with word aligned address, max virtual space that could be wasted = 3 bytes
    // Or create a new region from (uint32_t)&_rodata_reserved_end to ALIGN_UP_BY((uint32_t)&_rodata_reserved_end, 4) as only byte-accessible
    *gap_start = RODATA_ALIGNMENT_GAP_START;
    *gap_end = RODATA_ALIGNMENT_GAP_END;
}

bool mmu_psram_check_ptr_addr_in_xip_psram_rodata_region(const void *p)
{
    if ((intptr_t)p >= ALIGN_DOWN_BY((uint32_t)&_rodata_reserved_start, CONFIG_MMU_PAGE_SIZE) && (intptr_t)p < ALIGN_UP_BY((uint32_t)&_rodata_reserved_end, CONFIG_MMU_PAGE_SIZE)) {
        return true;
    }

    return false;
}

esp_err_t mmu_config_psram_rodata_segment(uint32_t start_page, uint32_t psram_size, uint32_t *out_page)
{
    uint32_t page_id = start_page;

    uint32_t flash_bytes = mmu_psram_get_rodata_segment_length();

    if ((flash_bytes + MMU_PAGE_TO_BYTES(page_id)) > psram_size) {
        ESP_EARLY_LOGE(TAG, "SPI RAM space not enough for the instructions, need to copy to %" PRIu32 " B.", flash_bytes + MMU_PAGE_TO_BYTES(page_id));
        return ESP_FAIL;
    }

    //Enable the most high bus, which is used for copying FLASH .text to PSRAM
    cache_bus_mask_t bus_mask = cache_ll_l1_get_bus(0, SOC_EXTRAM_DATA_HIGH, 0);
    cache_ll_l1_enable_bus(0, bus_mask);
#if !CONFIG_ESP_SYSTEM_SINGLE_CORE_MODE
    bus_mask = cache_ll_l1_get_bus(1, SOC_EXTRAM_DATA_HIGH, 0);
    cache_ll_l1_enable_bus(1, bus_mask);
#endif

    rodata_flash_page_info_init(page_id);

#if CONFIG_IDF_TARGET_ESP32S2
    page_id = Cache_Flash_To_SPIRAM_Copy(PRO_CACHE_IBUS2, SOC_DROM0_ADDRESS_LOW, page_id, &page0_page);
    page_id = Cache_Flash_To_SPIRAM_Copy(PRO_CACHE_DBUS0, SOC_DRAM0_ADDRESS_LOW, page_id, &page0_page);
    page_id = Cache_Flash_To_SPIRAM_Copy(PRO_CACHE_DBUS1, SOC_DRAM1_ADDRESS_LOW, page_id, &page0_page);
    page_id = Cache_Flash_To_SPIRAM_Copy(PRO_CACHE_DBUS2, SOC_DPORT_ADDRESS_LOW, page_id, &page0_page);
#elif CONFIG_IDF_TARGET_ESP32S3
    page_id = Cache_Flash_To_SPIRAM_Copy(CACHE_DBUS, SOC_DRAM0_CACHE_ADDRESS_LOW, page_id, &page0_page);
#endif

    ESP_EARLY_LOGV(TAG, "after copy rodata, page_id is %" PRIu32, page_id);
    ESP_EARLY_LOGI(TAG, "Read only data copied and mapped to SPIRAM");

    *out_page = page_id - start_page;

    return ESP_OK;
}
#endif  //#if CONFIG_SPIRAM_RODATA

/*----------------------------------------------------------------------------
                    Part 2 APIs (See @Backgrounds on top of this file)
-------------------------------------------------------------------------------*/
//------------------------------------Copy Flash .text to PSRAM-------------------------------------//
#if CONFIG_SPIRAM_FETCH_INSTRUCTIONS
static uint32_t instruction_in_spiram;
static uint32_t instr_start_page;
static uint32_t instr_end_page;
static int instr_flash2spiram_offs;

/**
 * - These logics are abstracted from the PSRAM driver
 * - These functions are only required by `flash_mmap.c` for converting paddr to vaddr, and vice versa
 * - The `flash_mmpa.c` will be rewritten into MMU driver
 *
 * Therefore, keep the APIs here for now
 */
void instruction_flash_page_info_init(uint32_t psram_start_physical_page)
{
#if CONFIG_IDF_TARGET_ESP32S2
    uint32_t instr_page_cnt = ((uint32_t)&_instruction_reserved_end - (uint32_t)&_instruction_reserved_start + MMU_PAGE_SIZE - 1) / MMU_PAGE_SIZE;
    uint32_t instr_mmu_offset = ((uint32_t)&_instruction_reserved_start & SOC_MMU_VADDR_MASK) / MMU_PAGE_SIZE;
    instr_start_page = ((volatile uint32_t *)(DR_REG_MMU_TABLE + PRO_CACHE_IBUS0_MMU_START))[instr_mmu_offset];
#elif CONFIG_IDF_TARGET_ESP32S3
    uint32_t instr_page_cnt = ((uint32_t)&_instruction_reserved_end - SOC_IROM_LOW + MMU_PAGE_SIZE - 1) / MMU_PAGE_SIZE;
    instr_start_page = *((volatile uint32_t *)(DR_REG_MMU_TABLE + CACHE_IROM_MMU_START));
#endif
    instr_start_page &= SOC_MMU_VALID_VAL_MASK;
    instr_end_page = instr_start_page + instr_page_cnt - 1;
    instr_flash2spiram_offs = instr_start_page - psram_start_physical_page;
    instruction_in_spiram = 1;
    ESP_DRAM_LOGV("mmu_psram", "Instructions from flash page%d copy to SPIRAM page%d, Offset: %d", instr_start_page, psram_start_physical_page, instr_flash2spiram_offs);
}

uint32_t esp_spiram_instruction_access_enabled(void)
{
    return instruction_in_spiram;
}

int instruction_flash2spiram_offset(void)
{
    return instr_flash2spiram_offs;
}

uint32_t instruction_flash_start_page_get(void)
{
    return instr_start_page;
}

uint32_t instruction_flash_end_page_get(void)
{
    return instr_end_page;
}
#endif  //CONFIG_SPIRAM_FETCH_INSTRUCTIONS

#if CONFIG_SPIRAM_RODATA
//------------------------------------Copy Flash .rodata to PSRAM-------------------------------------//
static uint32_t rodata_in_spiram;
static int rodata_flash2spiram_offs;
static uint32_t rodata_start_page;
static uint32_t rodata_end_page;

/**
 * - These logics are abstracted from the PSRAM driver
 * - These functions are only required by `flash_mmap.c` for converting paddr to vaddr, and vice versa
 * - The `flash_mmpa.c` will be rewritten into MMU driver
 *
 * Therefore, keep the APIs here for now
 */
void rodata_flash_page_info_init(uint32_t psram_start_physical_page)
{
#if CONFIG_IDF_TARGET_ESP32S2
    uint32_t rodata_page_cnt = ((uint32_t)&_rodata_reserved_end - (uint32_t)&_rodata_reserved_start + MMU_PAGE_SIZE - 1) / MMU_PAGE_SIZE;
    uint32_t rodata_mmu_offset = ((uint32_t)&_rodata_reserved_start & SOC_MMU_VADDR_MASK) / MMU_PAGE_SIZE;
    rodata_start_page = ((volatile uint32_t *)(DR_REG_MMU_TABLE + PRO_CACHE_IBUS2_MMU_START))[rodata_mmu_offset];
#elif CONFIG_IDF_TARGET_ESP32S3
    uint32_t rodata_page_cnt = ((uint32_t)&_rodata_reserved_end - ((uint32_t)&_rodata_reserved_start & ~(MMU_PAGE_SIZE - 1)) + MMU_PAGE_SIZE - 1) / MMU_PAGE_SIZE;
    rodata_start_page = *(volatile uint32_t *)(DR_REG_MMU_TABLE + CACHE_DROM_MMU_START);
#endif
    rodata_start_page &= SOC_MMU_VALID_VAL_MASK;
    rodata_end_page = rodata_start_page + rodata_page_cnt - 1;
    rodata_flash2spiram_offs = rodata_start_page - psram_start_physical_page;
    rodata_in_spiram = 1;
    ESP_DRAM_LOGV("mmu_psram", "Rodata from flash page%d copy to SPIRAM page%d, Offset: %d", rodata_start_page, psram_start_physical_page, rodata_flash2spiram_offs);
}

uint32_t esp_spiram_rodata_access_enabled(void)
{
    return rodata_in_spiram;
}

int rodata_flash2spiram_offset(void)
{
    return rodata_flash2spiram_offs;
}

uint32_t rodata_flash_start_page_get(void)
{
    return rodata_start_page;
}

uint32_t rodata_flash_end_page_get(void)
{
    return rodata_end_page;
}
#endif  //#if CONFIG_SPIRAM_RODATA
