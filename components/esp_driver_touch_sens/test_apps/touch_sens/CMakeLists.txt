# For more information about build system see
# https://docs.espressif.com/projects/esp-idf/en/latest/api-guides/build-system.html
# The following five lines of boilerplate have to be in your project's
# CMakeLists in this exact order for cmake to work correctly
cmake_minimum_required(VERSION 3.16)

set(COMPONENTS main)
include($ENV{IDF_PATH}/tools/cmake/project.cmake)
project(touch_sens)

idf_build_get_property(elf EXECUTABLE)
if(CONFIG_COMPILER_DUMP_RTL_FILES)
    add_custom_target(check_test_app_sections ALL
                      COMMAND ${PYTHON} $ENV{IDF_PATH}/tools/ci/check_callgraph.py
                      --rtl-dirs ${CMAKE_BINARY_DIR}/esp-idf/esp_driver_touch_sens/,${CMAKE_BINARY_DIR}/esp-idf/hal/
                      --elf-file ${CMAKE_BINARY_DIR}/touch_sens.elf
                      find-refs
                      --from-sections=.iram0.text
                      --to-sections=.flash.text,.flash.rodata
                      --exit-code
                      DEPENDS ${elf}
                      )
endif()

message(STATUS "Checking touch sensor registers are not read-write by half-word")
include($ENV{IDF_PATH}/tools/ci/check_register_rw_half_word.cmake)
check_register_rw_half_word(SOC_MODULES "rtc_cntl" "sens" "rtc_io" "lp_analog_peri"
                                        "lp_clkrst" "lp_system" "lpperi" "touch" "pmu"
                            HAL_MODULES "touch_sensor")
