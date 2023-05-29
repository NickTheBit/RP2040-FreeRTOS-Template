/*********************************************
 * @brief Interface allowing a universal driver for
 * standard pin functions along multiple architectures.
 * @author Nikolaos Xenofon Gkloumpos
 * @date 25/05/2023
 *********************************************/

#pragma once

namespace HAL {

typedef enum {
    HIGH = 1,
    LOW = 0
} GPIO_STATE;

class GPIOPinInterface {
  public:
	virtual void write(GPIO_STATE newState) = 0;
    virtual GPIO_STATE read() = 0;
};

} // namespace HAL
