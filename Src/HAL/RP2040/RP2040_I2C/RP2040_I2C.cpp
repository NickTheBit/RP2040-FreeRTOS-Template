/***********************************************
 * @brief  Hardware specific I2C wrapper for the RP2040.
 * @author Nikolaos Xenofon Gkloumpos.
 * @date   6/1/23
 ***********************************************/

#include <hardware/gpio.h>
#include <pico/binary_info/code.h>
#include "RP2040_I2C.h"

/**
 * @brief Initializes the necessary hardware for i2c communication.
 * @param hardwareInterface
 * @param baudrateHz
 * @param responseTimeout
 */
RP2040_I2C::RP2040_I2C(i2c_inst_t *hardwareInterface, uint8_t SDAPin, uint8_t SCLPin, bool slaveMode, uint32_t baudrateHz)
        : hardwareInterface(hardwareInterface), SCLPin(SCLPin), SDAPin(SDAPin),
        baudrateHz(baudrateHz), slaveMode(slaveMode) {

    this->baudrateHz = i2c_init(this->hardwareInterface, this->baudrateHz);
    i2c_set_slave_mode(this->hardwareInterface,false,0x33);
    gpio_set_function(this->SDAPin, GPIO_FUNC_I2C);
    gpio_set_function(this->SCLPin, GPIO_FUNC_I2C);
    gpio_pull_up(this->SDAPin);
    gpio_pull_up(this->SCLPin);
    bi_decl(bi_2pins_with_func((uint32_t)this->SDAPin, (uint32_t)this->SCLPin, GPIO_FUNC_I2C))
}

/**
 * @brief De-initializes i2c the interface.
 */
RP2040_I2C::~RP2040_I2C() {
    i2c_deinit(this->hardwareInterface);
}

/**
 * @brief Reads multiple bytes starting from the target address.
 * @param address
 * @param consecutiveBytes
 * @return
 */
void RP2040_I2C::read(uint8_t address, uint8_t consecutiveBytes, uint8_t *outputArray) {
    if (consecutiveBytes < 1) {
        return;
    }
    i2c_read_blocking(this->hardwareInterface,
                      address,
                      outputArray,
                      consecutiveBytes,
                      true);
}

void RP2040_I2C::write(uint8_t startingAddress, uint8_t *payload, uint16_t payloadSize) {
    if (payloadSize < 1)
        return;

    i2c_write_blocking(this->hardwareInterface,
                       startingAddress,
                       payload,
                       payloadSize,
                       true);
}

/**
 * @brief   Getter for the selected baud-rate (Hz).
 * @return  baudrateHz.
 */
uint16_t RP2040_I2C::getBaudrateHz() const {
    return this->baudrateHz;
}
/**
 * @brief   Getter for whether the interface is in slave mode.
 * @return  slaveMode.
 */
bool RP2040_I2C::isSlaveMode() const {
    return this->slaveMode;
}
