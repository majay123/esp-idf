set(srcs "test_app_main.c"
         "test_i2s.c"
         "test_i2s_iram.c")

if(CONFIG_SOC_I2S_SUPPORTS_ETM AND CONFIG_SOC_GPIO_SUPPORT_ETM)
    set(srcs ${srcs} "test_i2s_etm.c")
endif()

if(CONFIG_SOC_LIGHT_SLEEP_SUPPORTED)
    list(APPEND srcs "test_i2s_sleep.c")
endif()

idf_component_register(SRCS ${srcs}
                       PRIV_REQUIRES unity esp_driver_pcnt spi_flash
                                     esp_driver_gpio esp_driver_i2s esp_driver_uart esp_psram
                       WHOLE_ARCHIVE)
