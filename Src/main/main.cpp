/*********************************************
 * @brief Entry point for kernel code in the Template,
 * do not modify this file, only rtos functions and the
 * primary task should be initialized here.
 * @author Nikolaos Xenofon Gkloumpos
 * @date 25/05/2023
 *********************************************/

#include "main.h"
#include "PrimaryTask/PrimaryTask.hh"


// Creating task handles.
TaskHandle_t primaryTaskHandle = nullptr;

/**
 * @brief Show basic device info.
 */
void log_device_info(void) {
	return;
}

/*
 * RUNTIME START
 */
int main() {
// Enable STDIO
#ifdef DEBUG
	stdio_usb_init();
#endif

	// Setting up primary Task.
	BaseType_t pico_status = xTaskCreate(primaryTask, "primaryTask", 128, nullptr,
										 1, &primaryTaskHandle);

	// Log app info
	log_device_info();

	// Start the FreeRTOS scheduler
	// Only proceed with valid tasks
	if (pico_status == pdPASS) {
		vTaskStartScheduler();
	}

	// If the scheduler doesn't take over, it should be handled here.
	while (true) {
		// NOP
	};
}
