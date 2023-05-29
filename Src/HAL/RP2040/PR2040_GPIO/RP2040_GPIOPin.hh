/*********************************************
 * @brief Hardware specific driver for the
 * GPIO pins of the RP2040.
 * @author Nikolaos Xenofon Gkloumpos
 * @date 25/05/2023
 *********************************************/

#include "HAL/GPIOPinInterface.hh"
#include "main.h"

class RP2040_GPIOPin : public HAL::GPIOPinInterface {
  private:
	uint8_t pin = 0;

  public:
	explicit RP2040_GPIOPin(uint8_t GPIOPin);
	~RP2040_GPIOPin() = default;
	void write(HAL::GPIO_STATE) override;
	HAL::GPIO_STATE read() override;
};
