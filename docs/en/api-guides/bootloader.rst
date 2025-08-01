Bootloader
==========

:link_to_translation:`zh_CN:[中文]`

The ESP-IDF second stage bootloader performs the following functions:

1. Minimal initial configuration of internal modules;
2. Initialize :doc:`/security/flash-encryption` and/or :doc:`Secure Boot </security/secure-boot-v2>` features, if configured;
3. Select the application partition to boot, based on the partition table and ota_data (if any);
4. Load this image to RAM (IRAM & DRAM) and transfer management to the image that was just loaded.

ESP-IDF second stage bootloader is located at the address {IDF_TARGET_CONFIG_BOOTLOADER_OFFSET_IN_FLASH} in the flash.

For a full description of the startup process including the ESP-IDF second stage bootloader, see :doc:`startup`.

.. _bootloader-compatibility:

Bootloader Compatibility
------------------------

It is recommended to update to newer :doc:`versions of ESP-IDF </versions>`: when they are released. The OTA (over the air) update process can flash new apps in the field but cannot flash a new bootloader. For this reason, the bootloader supports booting apps built from newer versions of ESP-IDF.

The bootloader does not support booting apps from older versions of ESP-IDF. When updating ESP-IDF manually on an existing product that might need to downgrade the app to an older version, keep using the older ESP-IDF bootloader binary as well.

.. note::

    If testing an OTA update for an existing product in production, always test it using the same ESP-IDF bootloader binary that is deployed in production.

.. only:: esp32

    Before ESP-IDF V2.1
    ^^^^^^^^^^^^^^^^^^^

    Bootloaders built from very old versions of ESP-IDF (before ESP-IDF V2.1) perform less hardware configuration than newer versions. When using a bootloader from these early ESP-IDF versions and building a new app, enable the config option :ref:`CONFIG_APP_COMPATIBLE_PRE_V2_1_BOOTLOADERS`.

    Before ESP-IDF V3.1
    ^^^^^^^^^^^^^^^^^^^

    Bootloaders built from versions of ESP-IDF before V3.1 do not support MD5 checksums in the partition table binary. When using a bootloader from these ESP-IDF versions and building a new app, enable the config option :ref:`CONFIG_APP_COMPATIBLE_PRE_V3_1_BOOTLOADERS`.

    Before ESP-IDF V5.1
    ^^^^^^^^^^^^^^^^^^^

    Bootloaders built from versions of ESP-IDF prior to V5.1 do not support :ref:`CONFIG_ESP_SYSTEM_ESP32_SRAM1_REGION_AS_IRAM`. When using a bootloader from these ESP-IDF versions and building a new app, you should not use this option.


SPI Flash Configuration
^^^^^^^^^^^^^^^^^^^^^^^

Each ESP-IDF application or bootloader .bin file contains a header with :ref:`CONFIG_ESPTOOLPY_FLASHMODE`, :ref:`CONFIG_ESPTOOLPY_FLASHFREQ`, :ref:`CONFIG_ESPTOOLPY_FLASHSIZE` embedded in it. These are used to configure the SPI flash during boot.

The :ref:`first-stage-bootloader` reads the :ref:`second-stage-bootloader` header information from flash and uses this information to load the rest of the :ref:`second-stage-bootloader` from flash. However, at this time the system clock speed is lower than configured and not all flash modes are supported. When the :ref:`second-stage-bootloader` then runs, it will reconfigure the flash using values read from the currently selected app binary's header (and NOT from the :ref:`second-stage-bootloader` header). This allows an OTA update to change the SPI flash settings in use.

.. only:: esp32

    Bootloaders prior to ESP-IDF V4.0 used the bootloader's own header to configure the SPI flash, meaning these values could not be changed in an update. To maintain compatibility with older bootloaders, the app re-initializes the flash settings during app startup using the configuration found in the app header.

Log Level
---------

The default bootloader log level is "Info". By setting the :ref:`CONFIG_BOOTLOADER_LOG_LEVEL` option, it is possible to increase or decrease this level. This log level is separate from the log level used in the app (see :doc:`/api-reference/system/log`).

Reducing bootloader log verbosity can improve the overall project boot time by a small amount.

Factory Reset
-------------

Sometimes it is desirable to have a way for the device to fall back to a known-good state, in case of some problem with an update.

To roll back to the original "factory" device configuration and clear any user settings, configure the config item :ref:`CONFIG_BOOTLOADER_FACTORY_RESET` in the bootloader.

The factory reset mechanism allows the device to be factory reset in two ways:

- Clear one or more data partitions. The :ref:`CONFIG_BOOTLOADER_DATA_FACTORY_RESET` option allows users to specify which data partitions will be erased when the factory reset is executed.

  Users can specify the names of partitions as a comma-delimited list with optional spaces for readability. (Like this: ``nvs, phy_init, nvs_custom``).

  Make sure that the names of partitions specified in the option are the same as those found in the partition table. Partitions of type "app" cannot be specified here.

- Boot from "factory" app partition. Enabling the :ref:`CONFIG_BOOTLOADER_OTA_DATA_ERASE` option will cause the device to boot from the default "factory" app partition after a factory reset (or if there is no factory app partition in the partition table then the default ota app partition is selected instead). This reset process involves erasing the OTA data partition which holds the currently selected OTA partition slot. The "factory" app partition slot (if it exists) is never updated via OTA, so resetting to this allows reverting to a "known good" firmware application.

Either or both of these configuration options can be enabled independently.

In addition, the following configuration options control the reset condition:

- :ref:`CONFIG_BOOTLOADER_NUM_PIN_FACTORY_RESET`- The input GPIO number used to trigger a factory reset. This GPIO must be pulled low or high (configurable) on reset to trigger this.

- :ref:`CONFIG_BOOTLOADER_HOLD_TIME_GPIO`- this is hold time of GPIO for reset/test mode (by default 5 seconds). The GPIO must be held continuously for this period of time after reset before a factory reset or test partition boot (as applicable) is performed.

- :ref:`CONFIG_BOOTLOADER_FACTORY_RESET_PIN_LEVEL` - configure whether a factory reset should trigger on a high or low level of the GPIO. If the GPIO has an internal pullup then this is enabled before the pin is sampled, consult the {IDF_TARGET_NAME} datasheet for details on pin internal pullups.

.. only:: SOC_RTC_FAST_MEM_SUPPORTED

    If an application needs to know if the factory reset has occurred, users can call the function :cpp:func:`bootloader_common_get_rtc_retain_mem_factory_reset_state`.

    - If the status is read as true, the function will return the status, indicating that the factory reset has occurred. The function then resets the status to false for subsequent factory reset judgement.
    - If the status is read as false, the function will return the status, indicating that the factory reset has not occurred, or the memory where this status is stored is invalid.

    Note that this feature reserves some RTC FAST memory (the same size as the :ref:`CONFIG_BOOTLOADER_SKIP_VALIDATE_IN_DEEP_SLEEP` feature).

.. only:: not SOC_RTC_FAST_MEM_SUPPORTED

    Sometimes an application needs to know if the factory reset has occurred. The {IDF_TARGET_NAME} chip does not have RTC FAST memory, so there is no API to detect it. Instead, there is a workaround: you need an NVS partition that will be erased by the bootloader if factory reset occurs (add this partition to :ref:`CONFIG_BOOTLOADER_DATA_FACTORY_RESET`). In this NVS partition, create a "factory_reset_state" token that will be increased in the application. If the "factory_reset_state" is 0 then the factory reset has occurred.

.. _bootloader_boot_from_test_firmware:

Boot from Test Firmware
------------------------

It is possible to write a special firmware app for testing in production, and boot this firmware when needed. The project partition table will need a dedicated app partition entry for this testing app, type ``app`` and subtype ``test`` (see :doc:`/api-guides/partition-tables`).

Implementing a dedicated test app firmware requires creating a totally separate ESP-IDF project for the test app (each project in ESP-IDF only builds one app). The test app can be developed and tested independently of the main project, and then integrated at production testing time as a pre-compiled .bin file which is flashed to the address of the main project's test app partition.

To support this functionality in the main project's bootloader, set the configuration item :ref:`CONFIG_BOOTLOADER_APP_TEST` and configure the following three items:

- :ref:`CONFIG_BOOTLOADER_NUM_PIN_APP_TEST` - GPIO number to boot test partition. The selected GPIO will be configured as an input with internal pull-up enabled. This GPIO must be pulled low or high (configurable) on reset to trigger this.

  Once the GPIO input is released and the device has been rebooted, the default boot sequence will be enabled again to boot the factory partition or any OTA app partition slot.

- :ref:`CONFIG_BOOTLOADER_HOLD_TIME_GPIO` - this is the hold time of GPIO for reset/test mode (by default 5 seconds). The GPIO must be held continuously for this period of time after reset before a factory reset or test partition boot (as applicable) is performed.

- :ref:`CONFIG_BOOTLOADER_APP_TEST_PIN_LEVEL` - configure whether a test partition boot should trigger on a high or low level of the GPIO. If the GPIO has an internal pull-up, then this is enabled before the pin is sampled. Consult the {IDF_TARGET_NAME} datasheet for details on pin internal pull-ups.

Rollback
--------

Rollback and anti-rollback features must be configured in the bootloader as well.

Consult the :ref:`app_rollback` and :ref:`anti-rollback` sections in the :doc:`OTA API reference document </api-reference/system/ota>`.

.. _bootloader-watchdog:

Watchdog
--------

The chips come equipped with two groups of watchdog timers: Main System Watchdog Timer (MWDT_WDT) and RTC Watchdog Timer (RTC_WDT). Both watchdog timer groups are enabled when the chip is powered up. However, in the bootloader, they will both be disabled. If :ref:`CONFIG_BOOTLOADER_WDT_ENABLE` is set (which is the default behavior), RTC_WDT is re-enabled. It tracks the time from the bootloader is enabled until the user's main function is called. In this scenario, RTC_WDT remains operational and will automatically reset the chip if no application successfully starts within 9 seconds. This functionality is particularly useful in preventing lockups caused by an unstable power source during startup.

- The timeout period can be adjusted by setting :ref:`CONFIG_BOOTLOADER_WDT_TIME_MS` and recompiling the bootloader.
- The RTC Watchdog can be disabled in the bootloader by disabling the :ref:`CONFIG_BOOTLOADER_WDT_ENABLE` setting and recompiling the bootloader. This is not recommended.
- See :ref:`app-hardware-watchdog-timers` to learn how RTC_WDT is used in the application.

.. _bootloader-size:

Bootloader Size
---------------

{IDF_TARGET_MAX_BOOTLOADER_SIZE:default = "80 KB (0x14000 bytes)", esp32 = "48 KB (0xC000 bytes)", esp32s2, esp32s3, esp32c2, esp32c3, esp32c6, esp32h2, esp32h21, esp32p4 = "64 KB (0x10000 bytes)"}
{IDF_TARGET_MAX_PARTITION_TABLE_OFFSET:default = "0x11000", esp32 = "0xE000", esp32c5, esp32h4 = "0x17000", esp32c61 = "0x15000", esp32p4 = "0x13000"}
.. Above is calculated as:
    0x1000 at start of flash + IDF_TARGET_MAX_BOOTLOADER_SIZE + 0x1000 signature sector // for esp32
    0x0 at start of flash + IDF_TARGET_MAX_BOOTLOADER_SIZE + 0x1000 signature sector // for esp32s2, esp32s3, esp32c2, esp32c3, esp32c6, esp32c61, esp32h2, esp32h21
    0x2000 at start of flash + IDF_TARGET_MAX_BOOTLOADER_SIZE + 0x1000 signature sector // for Key Manager supported targets: esp32c5, esp32h4, esp32p4

When enabling additional bootloader functions, including :doc:`/security/flash-encryption` or Secure Boot, and especially if setting a high :ref:`CONFIG_BOOTLOADER_LOG_LEVEL` level, then it is important to monitor the bootloader .bin file's size.

When using the default :ref:`CONFIG_PARTITION_TABLE_OFFSET` value 0x8000, the size limit is {IDF_TARGET_CONFIG_PARTITION_TABLE_OFFSET} bytes.

If the bootloader binary is too large, then the bootloader build will fail with an error "Bootloader binary size [..] is too large for partition table offset". If the bootloader binary is flashed anyhow then the {IDF_TARGET_NAME} will fail to boot - errors will be logged about either invalid partition table or invalid bootloader checksum.

Options to work around this are:

- Set :ref:`bootloader compiler optimization <CONFIG_BOOTLOADER_COMPILER_OPTIMIZATION>` back to "Size" if it has been changed from this default value.
- Reduce :ref:`bootloader log level <CONFIG_BOOTLOADER_LOG_LEVEL>`. Setting log level to Warning, Error or None all significantly reduce the final binary size (but may make it harder to debug).
- Set :ref:`CONFIG_PARTITION_TABLE_OFFSET` to a higher value than 0x8000, to place the partition table later in the flash. This increases the space available for the bootloader. If the :doc:`partition table </api-guides/partition-tables>` CSV file contains explicit partition offsets, they will need changing so no partition has an offset lower than ``CONFIG_PARTITION_TABLE_OFFSET + 0x1000``. (This includes the default partition CSV files supplied with ESP-IDF.)

When Secure Boot V2 is enabled, there is also an absolute binary size limit of {IDF_TARGET_MAX_BOOTLOADER_SIZE} (excluding the 4 KB signature), because the bootloader is first loaded into a fixed size buffer for verification.

Fast Boot from Deep-Sleep
-------------------------

The bootloader has the :ref:`CONFIG_BOOTLOADER_SKIP_VALIDATE_IN_DEEP_SLEEP` option which allows the wake-up time from Deep-sleep to be reduced (useful for reducing power consumption). This option is available when the :ref:`CONFIG_SECURE_BOOT` option is disabled or :ref:`CONFIG_SECURE_BOOT_INSECURE` is enabled along with Secure Boot. The reduction in time is achieved by ignoring image verification.

.. only:: SOC_RTC_FAST_MEM_SUPPORTED

    During the first boot, the bootloader stores the address of the application being launched in the RTC FAST memory. After waking up from deep sleep, this address is used to boot the application again without any checks, resulting in a significantly faster load.

.. only:: not SOC_RTC_FAST_MEM_SUPPORTED

    The {IDF_TARGET_NAME} does not have RTC memory, so a running partition cannot be saved there; instead, the entire partition table is read to select the correct application. During wake-up, the selected application is loaded without any checks, resulting in a significantly faster load.

Custom Bootloader
-----------------

The current bootloader implementation allows a project to extend it or modify it. There are two ways of doing it: by implementing hooks or by overriding it. Both ways are presented in :example:`custom_bootloader` folder in ESP-IDF examples:

* :example:`custom_bootloader/bootloader_hooks` presents how to connect some hooks to the bootloader initialization
* :example:`custom_bootloader/bootloader_override` presents how to override the bootloader implementation

In the bootloader space, you cannot use the drivers and functions from other components unless they explicitly support run in bootloader. If necessary, then the required functionality should be placed in the project's `bootloader_components` directory (note that this will increase its size). Examples of components that can be used in the bootloader are:

* :example:`storage/nvs/nvs_bootloader`

If the bootloader grows too large then it can collide with the partition table, which is flashed at offset 0x8000 by default. Increase the :ref:`partition table offset <CONFIG_PARTITION_TABLE_OFFSET>` value to place the partition table later in the flash. This increases the space available for the bootloader.

.. only:: SOC_RECOVERY_BOOTLOADER_SUPPORTED

    Recovery Bootloader
    -------------------

    The {IDF_TARGET_NAME} introduces Recovery Bootloader and Anti-rollback Bootloader features, implemented in the ROM bootloader to enhance device security and reliability during OTA updates.

    The recovery bootloader feature enables safe OTA updates of the bootloader itself. When the eFuse field ``ESP_EFUSE_RECOVERY_BOOTLOADER_FLASH_SECTOR`` is set, it specifies the flash address (in sectors) of the recovery bootloader. If the primary bootloader at {IDF_TARGET_CONFIG_BOOTLOADER_OFFSET_IN_FLASH} fails to load, the ROM bootloader attempts to load the recovery bootloader from this address.

    - The eFuse can be programmed using ``espefuse.py`` or via the user application using :cpp:func:`esp_efuse_set_recovery_bootloader_offset()`.
    - The address can be set via the ``CONFIG_BOOTLOADER_RECOVERY_OFFSET``, it must be a multiple of the flash sector size (0x1000 bytes). This Kconfig option helps ensure the recovery bootloader does not overlap with existing partitions.
    - Note that the eFuse field stores the offset in sectors. Setting it to the maximum value ``0xFFF`` disables the feature.
    - The recovery bootloader image at the ``CONFIG_BOOTLOADER_RECOVERY_OFFSET`` is not flashed by default. It can be written as part of the OTA update process.

    The example below shows the bootloader log when the primary bootloader fails to load and the recovery bootloader is loaded instead.

    .. code-block:: none

        ESP-ROM:esp32c5-eco2-20250121
        Build:Jan 21 2025
        rst:0x1 (POWERON),boot:0x18 (SPI_FAST_FLASH_BOOT)
        invalid header: 0xffffffff
        invalid header: 0xffffffff
        invalid header: 0xffffffff
        PRIMARY - FAIL
        Loading RECOVERY Bootloader...
        SPI mode:DIO, clock div:1
        load:0x408556b0,len:0x17cc
        load:0x4084bba0,len:0xdac
        load:0x4084e5a0,len:0x3140
        entry 0x4084bbaa

        I (46) boot: ESP-IDF v6.0-dev-172-g12c5d730097-dirty 2nd stage bootloader
        I (46) boot: compile time May 22 2025 12:41:59
        I (47) boot: chip revision: v1.0
        I (48) boot: efuse block revision: v0.1
        I (52) boot.esp32c5: SPI Speed      : 80MHz
        I (55) boot.esp32c5: SPI Mode       : DIO
        I (59) boot.esp32c5: SPI Flash Size : 4MB
        I (63) boot: Enabling RNG early entropy source...
        I (67) boot: Partition Table:
        ...

    Anti-Rollback Feature
    ^^^^^^^^^^^^^^^^^^^^^

    The anti-rollback feature prevents downgrading to an older, potentially vulnerable bootloader version. The bootloader header includes a security version, defined by ``CONFIG_BOOTLOADER_SECURE_VERSION``. When ``EFUSE_BOOTLOADER_ANTI_ROLLBACK_EN`` is set, the ROM bootloader checks this version against the value stored in ``EFUSE_BOOTLOADER_ANTI_ROLLBACK_SECURE_VERSION``. Only bootloaders with a version greater than or equal to the eFuse value are allowed to boot.

    - The ROM bootloader can update the secure version in eFuse if ``EFUSE_BOOTLOADER_ANTI_ROLLBACK_SECURE_VERSION_UPDATE_IN_ROM`` is set.
    - The secure version value is incremented as new bootloader versions are deployed, and cannot be decreased.
    - If the secure version in eFuse is not updated in the ROM bootloader, then the application can update it using the :cpp:func:`esp_efuse_write_field_blob` function.

    Relevant eFuses
    ^^^^^^^^^^^^^^^

    - ``EFUSE_RECOVERY_BOOTLOADER_FLASH_SECTOR`` (12 bits): Flash sector address for the recovery bootloader. Default value is 0 (disabled), set any other value to enable, 0xFFF to permanently disable.
    - ``EFUSE_BOOTLOADER_ANTI_ROLLBACK_EN`` (1 bit): Enables anti-rollback check in the ROM bootloader.
    - ``EFUSE_BOOTLOADER_ANTI_ROLLBACK_SECURE_VERSION`` (4 bits): Secure version for anti-rollback protection. The value increases as bits are set - 0x0, 0x1, 0x3, 0x7, 0xF.
    - ``EFUSE_BOOTLOADER_ANTI_ROLLBACK_SECURE_VERSION_UPDATE_IN_ROM`` (1 bit): Allows the ROM bootloader to update the secure version in eFuse.

    .. note::

        Use these features to improve device security and reliability during OTA updates. Carefully plan eFuse programming, as these settings are permanent and may affect future update strategies.
