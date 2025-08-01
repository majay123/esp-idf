/*
 * SPDX-FileCopyrightText: 2024-2025 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

//TODO: [ESP32H21] IDF-11556

/** \defgroup efuse_APIs efuse APIs
  * @brief     ESP32H21 efuse read/write APIs
  * @attention
  *
  */

/** @addtogroup efuse_APIs
  * @{
  */

typedef enum {
    ETS_EFUSE_KEY_PURPOSE_USER = 0,
    ETS_EFUSE_KEY_PURPOSE_ECDSA_KEY = 1,
    ETS_EFUSE_KEY_PURPOSE_RESERVED = 2,
    ETS_EFUSE_KEY_PURPOSE_XTS_AES_128_KEY = 4,
    ETS_EFUSE_KEY_PURPOSE_HMAC_DOWN_ALL = 5,
    ETS_EFUSE_KEY_PURPOSE_HMAC_DOWN_JTAG = 6,
    ETS_EFUSE_KEY_PURPOSE_HMAC_DOWN_DIGITAL_SIGNATURE = 7,
    ETS_EFUSE_KEY_PURPOSE_HMAC_UP = 8,
    ETS_EFUSE_KEY_PURPOSE_SECURE_BOOT_DIGEST0 = 9,
    ETS_EFUSE_KEY_PURPOSE_SECURE_BOOT_DIGEST1 = 10,
    ETS_EFUSE_KEY_PURPOSE_SECURE_BOOT_DIGEST2 = 11,
    ETS_EFUSE_KEY_PURPOSE_MAX,
} ets_efuse_purpose_t;

typedef enum {
    ETS_EFUSE_BLOCK0 = 0,
    ETS_EFUSE_MAC_SPI_SYS_0 = 1,
    ETS_EFUSE_BLOCK_SYS_DATA = 2,
    ETS_EFUSE_BLOCK_USR_DATA = 3,
    ETS_EFUSE_BLOCK_KEY0 = 4,
    ETS_EFUSE_BLOCK_KEY1 = 5,
    ETS_EFUSE_BLOCK_KEY2 = 6,
    ETS_EFUSE_BLOCK_KEY3 = 7,
    ETS_EFUSE_BLOCK_KEY4 = 8,
    ETS_EFUSE_BLOCK_KEY5 = 9,
    ETS_EFUSE_BLOCK_KEY6 = 10,
    ETS_EFUSE_BLOCK_MAX,
} ets_efuse_block_t;

/**
  * @brief  Efuse read operation: copies data from physical efuses to efuse read registers.
  *
  * @param  null
  *
  * @return : 0 if success, others if apb clock is not accepted
  */
int ets_efuse_read(void);

/**
  * @brief  Efuse write operation: Copies data from efuse write registers to efuse. Operates on a single block of efuses at a time.
  *
  * @note This function does not update read efuses, call ets_efuse_read() once all programming is complete.
  *
  * @return : 0 if success, others if apb clock is not accepted
  */
int ets_efuse_program(ets_efuse_block_t block);

/**
 * @brief Set all Efuse program registers to zero.
 *
 * Call this before writing new data to the program registers.
 */
void ets_efuse_clear_program_registers(void);

/**
 * @brief Program a block of key data to an efuse block
 *
 * @param key_block Block to read purpose for. Must be in range ETS_EFUSE_BLOCK_KEY0 to ETS_EFUSE_BLOCK_KEY6. Key block must be unused (@ref ets_efuse_key_block_unused).
 * @param purpose Purpose to set for this key. Purpose must be already unset.
 * @param data Pointer to data to write.
 * @param data_len Length of data to write.
 *
 * @note This function also calls ets_efuse_program() for the specified block, and for block 0 (setting the purpose)
 */
int ets_efuse_write_key(ets_efuse_block_t key_block, ets_efuse_purpose_t purpose, const void *data, size_t data_len);


/* @brief Return the address of a particular efuse block's first read register
 *
 * @param block Index of efuse block to look up
 *
 * @return 0 if block is invalid, otherwise a numeric read register address
 * of the first word in the block.
 */
uint32_t ets_efuse_get_read_register_address(ets_efuse_block_t block);

/**
 * @brief Return the current purpose set for an efuse key block
 *
 * @param key_block Block to read purpose for. Must be in range ETS_EFUSE_BLOCK_KEY0 to ETS_EFUSE_BLOCK_KEY6.
 */
ets_efuse_purpose_t ets_efuse_get_key_purpose(ets_efuse_block_t key_block);

/**
 * @brief Find a key block with the particular purpose set
 *
 * @param purpose Purpose to search for.
 * @param[out] key_block Pointer which will be set to the key block if found. Can be NULL, if only need to test the key block exists.
 * @return true if found, false if not found. If false, value at key_block pointer is unchanged.
 */
bool ets_efuse_find_purpose(ets_efuse_purpose_t purpose, ets_efuse_block_t *key_block);

/**
 * Return true if the key block is unused, false otherwise.
 *
 * An unused key block is all zero content, not read or write protected,
 * and has purpose 0 (ETS_EFUSE_KEY_PURPOSE_USER)
 *
 * @param key_block key block to check.
 *
 * @return true if key block is unused, false if key block or used
 * or the specified block index is not a key block.
 */
bool ets_efuse_key_block_unused(ets_efuse_block_t key_block);


/**
 * @brief Search for an unused key block and return the first one found.
 *
 * See @ref ets_efuse_key_block_unused for a description of an unused key block.
 *
 * @return First unused key block, or ETS_EFUSE_BLOCK_MAX if no unused key block is found.
 */
ets_efuse_block_t ets_efuse_find_unused_key_block(void);

/**
 * @brief Return the number of unused efuse key blocks (0-6)
 */
unsigned ets_efuse_count_unused_key_blocks(void);

/**
 * @brief Calculate Reed-Solomon Encoding values for a block of efuse data.
 *
 * @param data Pointer to data buffer (length 32 bytes)
 * @param rs_values Pointer to write encoded data to (length 12 bytes)
 */
void ets_efuse_rs_calculate(const void *data, void *rs_values);

/**
  * @brief  Read if download mode disabled from Efuse
  *
  * @return
  * - true for efuse disable download mode.
  * - false for efuse doesn't disable download mode.
  */
bool ets_efuse_download_modes_disabled(void);

/**
  * @brief  Read if uart print control value from Efuse
  *
  * @return
  * - 0 for uart force print.
  * - 1 for uart print when GPIO8 is low when digital reset.
  *   2 for uart print when GPIO8 is high when digital reset.
  *   3 for uart force silent
  */
uint32_t ets_efuse_get_uart_print_control(void);

/**
  * @brief  Read if usb download mode disabled from Efuse
  *
  * (Also returns true if security download mode is enabled, as this mode
  * disables USB download.)
  *
  * @return
  * - true for efuse disable usb download mode.
  * - false for efuse doesn't disable usb download mode.
  */
bool ets_efuse_usb_download_mode_disabled(void);

/**
  * @brief  Read if security download modes enabled from Efuse
  *
  * @return
  * - true for efuse enable security download mode.
  * - false for efuse doesn't enable security download mode.
  */
bool ets_efuse_security_download_modes_enabled(void);

/**
 * @brief Return true if secure boot is enabled in EFuse
 */
bool ets_efuse_secure_boot_enabled(void);

/**
 * @brief Return true if secure boot aggressive revoke is enabled in EFuse
 */
bool ets_efuse_secure_boot_aggressive_revoke_enabled(void);

/**
 * @brief Return true if cache encryption (flash, etc) is enabled from boot via EFuse
 */
bool ets_efuse_cache_encryption_enabled(void);

/**
 * @brief Return true if EFuse indicates to send a flash resume command.
 */
bool ets_efuse_force_send_resume(void);

/**
  * @brief  return the time in us ROM boot need wait flash to power on from Efuse
  *
  * @return
  * - uint32_t the time in us.
  */
uint32_t ets_efuse_get_flash_delay_us(void);

#define EFUSE_SPICONFIG_SPI_DEFAULTS 0
#define EFUSE_SPICONFIG_HSPI_DEFAULTS 1

#define EFUSE_SPICONFIG_RET_SPICLK_MASK         0x3f
#define EFUSE_SPICONFIG_RET_SPICLK_SHIFT        0
#define EFUSE_SPICONFIG_RET_SPICLK(ret)         (((ret) >> EFUSE_SPICONFIG_RET_SPICLK_SHIFT) & EFUSE_SPICONFIG_RET_SPICLK_MASK)

#define EFUSE_SPICONFIG_RET_SPIQ_MASK           0x3f
#define EFUSE_SPICONFIG_RET_SPIQ_SHIFT          6
#define EFUSE_SPICONFIG_RET_SPIQ(ret)           (((ret) >> EFUSE_SPICONFIG_RET_SPIQ_SHIFT) & EFUSE_SPICONFIG_RET_SPIQ_MASK)

#define EFUSE_SPICONFIG_RET_SPID_MASK           0x3f
#define EFUSE_SPICONFIG_RET_SPID_SHIFT          12
#define EFUSE_SPICONFIG_RET_SPID(ret)           (((ret) >> EFUSE_SPICONFIG_RET_SPID_SHIFT) & EFUSE_SPICONFIG_RET_SPID_MASK)

#define EFUSE_SPICONFIG_RET_SPICS0_MASK         0x3f
#define EFUSE_SPICONFIG_RET_SPICS0_SHIFT        18
#define EFUSE_SPICONFIG_RET_SPICS0(ret)         (((ret) >> EFUSE_SPICONFIG_RET_SPICS0_SHIFT) & EFUSE_SPICONFIG_RET_SPICS0_MASK)


#define EFUSE_SPICONFIG_RET_SPIHD_MASK          0x3f
#define EFUSE_SPICONFIG_RET_SPIHD_SHIFT         24
#define EFUSE_SPICONFIG_RET_SPIHD(ret)          (((ret) >> EFUSE_SPICONFIG_RET_SPIHD_SHIFT) & EFUSE_SPICONFIG_RET_SPIHD_MASK)

/**
 * @brief Enable JTAG temporarily by writing a JTAG HMAC "key" into
 * the JTAG_CTRL registers.
 *
 * Works if JTAG has been "soft" disabled by burning the EFUSE_SOFT_DIS_JTAG efuse.
 *
 * Will enable the HMAC module to generate a "downstream" HMAC value from a key already saved in efuse, and then write the JTAG HMAC "key" which will enable JTAG if the two keys match.
 *
 * @param jtag_hmac_key Pointer to a 32 byte array containing a valid key. Supplied by user.
 * @param key_block Index of a key block containing the source for this key.
 *
 * @return ETS_FAILED if HMAC operation fails or invalid parameter, ETS_OK otherwise. ETS_OK doesn't necessarily mean that JTAG was enabled.
 */
int ets_jtag_enable_temporarily(const uint8_t *jtag_hmac_key, ets_efuse_block_t key_block);

/**
  * @brief  A crc8 algorithm used for MAC addresses in efuse
  *
  * @param  unsigned char const *p : Pointer to original data.
  *
  * @param  unsigned int len : Data length in byte.
  *
  * @return unsigned char: Crc value.
  */
unsigned char esp_crc8(unsigned char const *p, unsigned int len);

/**
  * @brief  Read if usb print in ROM disabled by efuse
  *
  *
  * @return
  * - 0 for enable.
  * - 1 for disable.
  */
uint32_t ets_efuse_usb_print_is_disabled(void);

/**
  * @}
  */

#ifdef __cplusplus
}
#endif
