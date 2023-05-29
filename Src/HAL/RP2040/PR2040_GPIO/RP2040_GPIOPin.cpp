/*********************************************
 * @brief Hardware specific driver for the
 * GPIO pins of the RP2040.
 * @author Nikolaos Xenofon Gkloumpos
 * @date 25/05/2023
 *********************************************/

#include "RP2040_GPIOPin.hh"

RP2040_GPIOPin::RP2040_GPIOPin(uint8_t GPIOPin) : pin(GPIOPin) {
    gpio_init(this->pin);
	gpio_set_dir(this->pin, GPIO_OUT);
}

HAL::GPIO_STATE RP2040_GPIOPin::read() {
	return HAL::GPIO_STATE::LOW;
}

void RP2040_GPIOPin::write(HAL::GPIO_STATE newState) {
	gpio_put(this->pin, (uint8_t)newState);
}
