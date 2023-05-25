/*********************************************
 * @brief Entry point for user code in the Template, if tasks
 * spawn like a tree, this is the task that spawns them all.
 * @author Nikolaos Xenofon Gkloumpos
 * @date 25/05/2023
 *********************************************/

#include "PrimaryTask.hh"
#include "main/main.h"

void primaryTask(void *arguments) {
	// Configure the Pico's on-board LED as a heartbeat indicator.
	gpio_init(PICO_DEFAULT_LED_PIN);
	gpio_set_dir(PICO_DEFAULT_LED_PIN, GPIO_OUT);

	while (true) {
        // Starting a heartbeat to indicate proper initialization.
		gpio_put(PICO_DEFAULT_LED_PIN, 0);
		vTaskDelay(1000);
		gpio_put(PICO_DEFAULT_LED_PIN, 1);
		vTaskDelay(50);
	}
}