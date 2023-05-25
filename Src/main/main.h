#pragma once

#ifndef GIT_HASH
#define GIT_HASH 0x000000
#endif

#ifndef PROJECT_NAME
#define PROJECT_NAME "PROJECT_NAME_UNDEFINED"
#endif

#ifndef PROJECT_VERSION_MAJOR
#define PROJECT_VERSION_MAJOR 0x0
#endif

#ifndef PROJECT_VERSION_MINOR
#define PROJECT_VERSION_MINOR 0x0
#endif

#ifndef PROJECT_VERSION_PATCH
#define PROJECT_VERSION_PATCH 0x0
#endif

// FreeRTOS
#include <FreeRTOS.h>
#include <queue.h>
#include <task.h>
// C
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
// Pico SDK
#include "pico/binary_info.h"
#include "pico/stdlib.h" // Includes `hardware_gpio.h`

#ifdef __cplusplus
extern "C" {
#endif

/**
 * CONSTANTS
 */
#define RED_LED_PIN 20

/**
 * PROTOTYPES
 */
void led_task_pico(void *unused_arg);
void led_task_gpio(void *unused_arg);
void log_debug(const char *msg);
void log_device_info(void);

#ifdef __cplusplus
} // extern "C"
#endif
