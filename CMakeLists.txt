# Generated Cmake Pico project file

cmake_minimum_required(VERSION 3.13)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Initialise pico_sdk from installed location
# (note this can come from environment, CMake cache etc)

# == DO NOT EDIT THE FOLLOWING LINES for the Raspberry Pi Pico VS Code Extension to work ==
if(WIN32)
    set(USERHOME $ENV{USERPROFILE})
else()
    set(USERHOME $ENV{HOME})
endif()
set(sdkVersion 2.2.0)
set(toolchainVersion 13_2_Rel1)
set(picotoolVersion 2.2.0-a4)
set(picoVscode ${USERHOME}/.pico-sdk/cmake/pico-vscode.cmake)
if (EXISTS ${picoVscode})
    include(${picoVscode})
endif()
# ====================================================================================
set(PICO_BOARD pico2 CACHE STRING "Board type")

# Pull in Raspberry Pi Pico SDK (must be before project)
include(pico_sdk_import.cmake)
include(pico_extras_import.cmake)

add_subdirectory(pico-tflmicro) # add pico-tflmicro subdirectory

project(NanoGPT C CXX ASM)

# Initialise the Raspberry Pi Pico SDK
pico_sdk_init()

# Add executable. Default name is the project name, version 0.1
add_executable(NanoGPT NanoGPT.cpp )

pico_set_program_name(NanoGPT "NanoGPT")
pico_set_program_version(NanoGPT "0.1")

# Modify the below lines to enable/disable output over UART/USB
pico_enable_stdio_uart(NanoGPT 0)
pico_enable_stdio_usb(NanoGPT 1)

# Add the standard library to the build
target_link_libraries(NanoGPT
        pico_stdlib
        pico-tflmicro # link libpico-tflmicro.a library
        )

# Add the standard include files to the build
target_include_directories(NanoGPT PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}
        ${CMAKE_CURRENT_LIST_DIR}/pico-tflmicro/src # include pico_tflmicro headers
)

pico_add_extra_outputs(NanoGPT)

