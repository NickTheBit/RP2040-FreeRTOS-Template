/********************************************
 * @brief  Freertos hooks and function implementations,
 * @author Nikolaos Xenofon Gkloumpos
 ********************************************/

#include "FreeRTOS.h"
#include "main.h"
#include "task.h"

static StaticTask_t xIdleTaskTCBBuffer;
static StackType_t __attribute__((section(".ccmram"))) xIdleStack[configMINIMAL_STACK_SIZE];

/**
 * @brief Implementation required for static memory allocation.
 * @param ppxIdleTaskTCBBuffer Variable containing Task Information
 * @param ppxIdleTaskStackBuffer Buffer for the tasks heap to live in
 * @param pulIdleTaskStackSize Buffer size (words)
 */
void vApplicationGetIdleTaskMemory(StaticTask_t **ppxIdleTaskTCBBuffer, StackType_t **ppxIdleTaskStackBuffer,
								   uint32_t *pulIdleTaskStackSize) {
	*ppxIdleTaskTCBBuffer = &xIdleTaskTCBBuffer;
	*ppxIdleTaskStackBuffer = &xIdleStack[0];
	*pulIdleTaskStackSize = configMINIMAL_STACK_SIZE;
}

static StaticTask_t xTimerTaskTCBBuffer;
static StackType_t __attribute__((section(".ccmram"))) xTimerStack[configMINIMAL_STACK_SIZE];

/**
 * @brief Implementation of function required by freertos.
 * @param ppxTimerTaskTCBBuffer   A handle to a statically allocated TCB buffer
 * @param ppxTimerTaskStackBuffer A handle to a statically allocated Stack buffer for the idle task
 * @param pulTimerTaskStackSize   A pointer to the number of elements that will fit in the allocated stack buffer
 */
void vApplicationGetTimerTaskMemory(StaticTask_t **ppxTimerTaskTCBBuffer, StackType_t **ppxTimerTaskStackBuffer,
									uint32_t *pulTimerTaskStackSize) {
	*ppxTimerTaskTCBBuffer = &xTimerTaskTCBBuffer;
	*ppxTimerTaskStackBuffer = &xTimerStack[0];
	*pulTimerTaskStackSize = configMINIMAL_STACK_SIZE;
}