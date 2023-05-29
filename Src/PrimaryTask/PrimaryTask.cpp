/*********************************************
 * @brief Entry point for user code in the Template, if tasks
 * spawn like a tree, this is the task that spawns them all.
 * @author Nikolaos Xenofon Gkloumpos
 * @date 25/05/2023
 *********************************************/

#include "PrimaryTask.hh"
#include "main/main.h"
#include "HAL/GPIOPinInterface.hh"
#include "HAL/RP2040/PR2040_GPIO/RP2040_GPIOPin.hh"

void primaryTask(void *arguments) {
	// Configure the Pico's on-board LED as a heartbeat indicator.
	auto heartbeatPin = RP2040_GPIOPin(PICO_DEFAULT_LED_PIN);

	while (true) {
        // Starting a heartbeat to indicate proper initialization.
		heartbeatPin.write(HAL::GPIO_STATE::LOW);
		vTaskDelay(1000);
		heartbeatPin.write(HAL::GPIO_STATE::HIGH);
		vTaskDelay(50);
	}
}