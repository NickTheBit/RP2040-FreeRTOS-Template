/*********************************************
 * @brief Entry point for kernel code in the Template,
 * do not modify this file, only rtos functions and the
 * primary task should be initialized here.
 * @author Nikolaos Xenofon Gkloumpos
 * @date  25/05/2023
 *********************************************/

#include "main.h"
#include "PrimaryTask/PrimaryTask.hh"

// Creating task handles.
TaskHandle_t primaryTaskHandle = nullptr;

/*
 * RUNTIME START
 */
int main() {
    // Enable STDIO
    stdio_init_all();

	// Setting up primary Task.
	BaseType_t pico_status = xTaskCreate(primaryTask, "primaryTask", 128, nullptr,
										 1, &primaryTaskHandle);

    // Reporting Firmware info on UART
    printf("*************************************\n\t%s\n-------------------------------------\nVersion: %d.%d.%d\nCommit hash: %x\n*************************************\n",
           PROJECT_NAME,
           PROJECT_VERSION_MAJOR,
           PROJECT_VERSION_MINOR,
           PROJECT_VERSION_PATCH,
           GIT_HASH);

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
