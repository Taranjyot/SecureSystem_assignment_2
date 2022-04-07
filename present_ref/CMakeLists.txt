cmake_minimum_required(VERSION 3.13)

include(pico_sdk_import.cmake)

project(pico_present_project C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
pico_sdk_init()
add_executable(pico_present_ref
  main.c
  crypto.c
)

pico_enable_stdio_usb(pico_present_ref 1)
pico_enable_stdio_uart(pico_present_ref 1)
pico_add_extra_outputs(pico_present_ref)
target_link_libraries(pico_present_ref pico_stdlib hardware_clocks pico_time)

