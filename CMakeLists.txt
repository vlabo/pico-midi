cmake_minimum_required(VERSION 3.13)

# initialize pico-sdk from GIT
# (note this can come from environment, CMake cache etc)
set(PICO_SDK_FETCH_FROM_GIT on)

# pico_sdk_import.cmake is a single file copied from this SDK
# note: this must happen before project()
include(pico_sdk_import.cmake)

project(pico-midi)

# initialize the Raspberry Pi Pico SDKe
pico_sdk_init()

# rest of your projecte
add_executable(midi src/main.c src/usb_descriptors.c)

target_include_directories(midi PRIVATE ${CMAKE_CURRENT_LIST_DIR}/src)

# Add pico_stdlib library which aggregates commonly used features
target_link_libraries(midi pico_stdlib hardware_adc tinyusb_device tinyusb_board)

# create map/bin/hex file etc.
pico_add_extra_outputs(midi)