/***********************************************
 * @brief  Hardware specific I2C wrapper for the RP2040.
 * @author Nikolaos Xenofon Gkloumpos.
 * @date   6/1/23
 ***********************************************/

#include <hardware/gpio.h>
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
    i2c_set_slave_mode(this->hardwareInterface,false,0x033);
    gpio_set_function(this->SDAPin, GPIO_FUNC_I2C);
    gpio_set_function(this->SCLPin, GPIO_FUNC_I2C);
    gpio_pull_up(this->SDAPin);
    gpio_pull_up(this->SCLPin);
}

/**
 * @brief De-initializes i2c the interface.
 */
RP2040_I2C::~RP2040_I2C() {
    i2c_deinit(this->hardwareInterface);
}

/**
 * @brief Reads multiple bytes starting from the target address.
 * @param startingAddress
 * @param consecutiveBytes
 * @return
 */
void RP2040_I2C::readBytes(uint8_t startingAddress, uint8_t consecutiveBytes, uint8_t *outputArray) {
    if (consecutiveBytes < 1) {
        return;
    }

    i2c_read_blocking(this->hardwareInterface,
                        startingAddress,
                        outputArray,
                        consecutiveBytes,
                        false);
}

/**
 * @brief Reads a single byte from the specified address.
 * @param address
 * @return read value.
 */
uint8_t RP2040_I2C::readByte(uint8_t address) {
    uint8_t returnValue;
    i2c_read_blocking(this->hardwareInterface,
                       address,
                       &returnValue,
                       1,
                       false);
    return returnValue;
}

void RP2040_I2C::writeBytes(uint8_t startingAddress, uint16_t numberOfBytes, uint8_t *dataToWrite) {
    if (numberOfBytes < 1)
        return;

    i2c_write_blocking(this->hardwareInterface,
                         startingAddress,
                         dataToWrite,
                         numberOfBytes,
                         false);
}

/**
 * @brief Writes one or more bytes of data to a specific register.
 * @param targetAddress
 * @param data
 */
void RP2040_I2C::writeByte(uint16_t targetAddress, uint8_t data) {
    i2c_write_timeout_us(this->hardwareInterface,
                         targetAddress,
                         &data,
                         1,
                         true
                         ,1000);
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
