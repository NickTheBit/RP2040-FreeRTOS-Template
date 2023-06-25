cmake_minimum_required(VERSION 3.25)

# Pull in SDK (must be before project)
include(cmakeScripts/pico_sdk_import.cmake)
include(cmakeScripts/pico_extras_import_optional.cmake)

project(FreeRTOS-Template
        VERSION 0.0.0)

if (PICO_SDK_VERSION_STRING VERSION_LESS "1.3.0")
    message(FATAL_ERROR "Raspberry Pi Pico SDK version 1.3.0 (or later) required. Your version is ${PICO_SDK_VERSION_STRING}")
endif()

# Inserting FreeRTOS paths
set(FREERTOS_CFG_DIRECTORY "${CMAKE_SOURCE_DIR}")
set(FREERTOS_SRC_DIRECTORY "${CMAKE_SOURCE_DIR}/Middlewares/FreeRTOS-Kernel")

# Initialize the SDK
pico_sdk_init()

# Add FreeRTOS as a library
add_library(FreeRTOS STATIC
    ${FREERTOS_SRC_DIRECTORY}/event_groups.c
    ${FREERTOS_SRC_DIRECTORY}/list.c
    ${FREERTOS_SRC_DIRECTORY}/queue.c
    ${FREERTOS_SRC_DIRECTORY}/stream_buffer.c
    ${FREERTOS_SRC_DIRECTORY}/tasks.c
    ${FREERTOS_SRC_DIRECTORY}/timers.c
    ${FREERTOS_SRC_DIRECTORY}/portable/MemMang/heap_3.c
    ${FREERTOS_SRC_DIRECTORY}/portable/GCC/ARM_CM0/port.c
)

# Build FreeRTOS
target_include_directories(FreeRTOS PUBLIC
    ${FREERTOS_CFG_DIRECTORY}/
    ${FREERTOS_SRC_DIRECTORY}/include
    ${FREERTOS_SRC_DIRECTORY}/portable/GCC/ARM_CM0
)

# Include app source code file(s)
add_executable(${PROJECT_NAME})

target_include_directories(${PROJECT_NAME} PUBLIC
        ${PROJECT_SOURCE_DIR}/Src/
        ${PROJECT_SOURCE_DIR}/Src/main/
        ${PROJECT_SOURCE_DIR}/Libs/HAL/)

file(GLOB_RECURSE PROJECT_SOURCES Src/*.cpp)

target_sources(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCES})

target_compile_options(${PROJECT_NAME} PUBLIC
    -Wall
    -Wno-format          # int != int32_t as far as the compiler is concerned because gcc has int32_t as long int
    -Wno-unused-function # we have some for the docs that aren't called
    -Wno-maybe-uninitialized
    -g
    )

# Configuring Hal Library
set(HAL_SELECTED_ARCHITECTURE "RP2040")
add_subdirectory(Libs/HAL)

# Link to built libraries
target_link_libraries(${PROJECT_NAME} LINK_PUBLIC
    pico_stdlib
    hardware_i2c
    FreeRTOS
    HAL)

# Enable/disable STDIO via USB and UART
pico_enable_stdio_usb(${PROJECT_NAME} 1)
pico_enable_stdio_uart(${PROJECT_NAME} 1)

# Enable extra build products
pico_add_extra_outputs(${PROJECT_NAME})

# Computing internal code definitions
# Getting latest commit hash (not entirely safe)
execute_process(
    COMMAND git log -1 --format=%h
    WORKING_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}
    OUTPUT_VARIABLE GIT_HASH
    OUTPUT_STRIP_TRAILING_WHITESPACE
    )

target_compile_definitions(${PROJECT_NAME} PUBLIC GIT_HASH=0x${GIT_HASH})
target_compile_definitions(${PROJECT_NAME} PUBLIC PROJECT_NAME="${PROJECT_NAME}")
target_compile_definitions(${PROJECT_NAME} PUBLIC PROJECT_VERSION_MAJOR=${PROJECT_VERSION_MAJOR})
target_compile_definitions(${PROJECT_NAME} PUBLIC PROJECT_VERSION_MINOR=${PROJECT_VERSION_MINOR})
target_compile_definitions(${PROJECT_NAME} PUBLIC PROJECT_VERSION_PATCH=${PROJECT_VERSION_PATCH})