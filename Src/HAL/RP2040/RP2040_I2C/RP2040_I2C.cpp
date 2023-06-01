/***********************************************
 * @brief  Hardware specific I2C wrapper for the RP2040.
 * @author Nikolaos Xenofon Gkloumpos.
 * @date   6/1/23
 ***********************************************/

#include "RP2040_I2C.h"

/**
 * @brief Initializes the necessary hardware for i2c communication.
 * @param hardwareInterface
 * @param baudrateHz
 * @param responseTimeout
 */
RP2040_I2C::RP2040_I2C(i2c_inst &hardwareInterface, uint16_t baudrateHz = 1000, uint16_t responseTimeout = 100,
                       bool slaveMode = false)
        : hardwareInterface(hardwareInterface), responseTimeout(responseTimeout), baudrateHz(baudrateHz),
          slaveMode(slaveMode) {
    // todo: variable baud rate needs to be supported, this is 1KHz.
    i2c_init(&this->hardwareInterface, this->baudrateHz);
}

/**
 * @brief De-initializes i2c the interface.
 */
RP2040_I2C::~RP2040_I2C() {
    i2c_deinit(&this->hardwareInterface);
}

/**
 * @brief Reads one or more registers from the target register.
 * @param targetRegister
 * @param consecutiveBytes
 * @return
 */
uint16_t RP2040_I2C::readRegister(uint8_t targetRegister, uint8_t consecutiveBytes) {
    uint16_t returnValue = 0;

    i2c_read_timeout_us(&this->hardwareInterface,
                        targetRegister,
                        reinterpret_cast<uint8_t *>(&returnValue),
                        consecutiveBytes,
                        consecutiveBytes > 1,
                        this->responseTimeout);
    return returnValue;
}

/**
 * @brief Writes one or more bytes of data to a specific register.
 * @param targetRegister
 * @param data
 */
void RP2040_I2C::writeRegister(uint8_t targetRegister, uint8_t data) {
    i2c_write_timeout_us(&this->hardwareInterface,
                         targetRegister,
                         &data,
                         sizeof(data),
                         sizeof(data) > 1,
                         this->responseTimeout);
}

/**
 * @brief   Getter for response timeout.
 * @return  responseTimeout.
 */
uint16_t RP2040_I2C::getResponseTimeout() const {
    return this->responseTimeout;
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
