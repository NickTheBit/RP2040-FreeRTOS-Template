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
 * @brief Reads multiple bytes starting from the target address.
 * @param startingAddress
 * @param consecutiveBytes
 * @return
 */
void RP2040_I2C::readBytes(uint8_t startingAddress, uint8_t consecutiveBytes, uint8_t *outputArray) {
    i2c_read_timeout_us(&this->hardwareInterface,
                        startingAddress,
                        outputArray,
                        consecutiveBytes,
                        consecutiveBytes > 1,
                        this->responseTimeout);
}

/**
 * @brief Reads a single byte from the specified address.
 * @param address
 * @return read value.
 */
uint8_t RP2040_I2C::readByte(uint8_t address) {
    uint8_t returnValue;
    i2c_read_timeout_us(&this->hardwareInterface,
                       address,
                       &returnValue,
                       1,
                       false,
                       this->responseTimeout);
    return returnValue;
}

void RP2040_I2C::writeBytes(uint8_t startingAddress, uint16_t numberOfBytes, uint8_t *dataToWrite) {
    i2c_write_timeout_us(&this->hardwareInterface,
                         startingAddress,
                         dataToWrite,
                         sizeof(numberOfBytes),
                         sizeof(numberOfBytes) > 1,
                         this->responseTimeout);
}

/**
 * @brief Writes one or more bytes of data to a specific register.
 * @param targetAddress
 * @param data
 */
void RP2040_I2C::writeByte(uint8_t targetAddress, uint8_t data) {
    i2c_write_timeout_us(&this->hardwareInterface,
                         targetAddress,
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
