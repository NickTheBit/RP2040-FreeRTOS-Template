/**
 * RP2040 FreeRTOS Template
 *
 * @copyright 2022, Tony Smith (@smittytone)
 * @version   1.4.1
 * @license   MIT
 *
 */
#pragma once

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
