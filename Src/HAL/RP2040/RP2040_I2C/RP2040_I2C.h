/***********************************************
 * @brief  Hardware specific I2C wrapper for the RP2040.
 * @author Nikolaos Xenofon Gkloumpos.
 * @date   6/1/23
 ***********************************************/

#pragma once

#include "HAL/I2CInterface.hh"
#include "hardware/i2c.h"

class RP2040_I2C : public I2CInterface {
private:
    i2c_inst_t * hardwareInterface;
    uint8_t SCLPin;
    uint8_t SDAPin;
    uint16_t baudrateHz;
    bool slaveMode;

public:
    RP2040_I2C(i2c_inst_t *hardwareInterface, uint8_t SDAPin, uint8_t SCLPin, bool slaveMode, uint32_t baudrateHz);
    ~RP2040_I2C();
    void readBytes(uint8_t startingAddress, uint8_t consecutiveBytes, uint8_t *outputArray) override;
    uint8_t readByte(uint8_t address) override;
    void writeBytes(uint8_t startingAddress, uint16_t numberOfBytes, uint8_t *dataToWrite) override;
    void writeByte(uint16_t targetAddress, uint8_t data) override;
    uint16_t getBaudrateHz() const;
    bool isSlaveMode() const;
};
