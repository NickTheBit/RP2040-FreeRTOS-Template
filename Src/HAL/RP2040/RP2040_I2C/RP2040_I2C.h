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
    void read(uint8_t address, uint8_t consecutiveBytes, uint8_t *outputArray) override;
    void write(uint8_t startingAddress, uint8_t *payload, uint16_t payloadSize) override;
    uint16_t getBaudrateHz() const;
    bool isSlaveMode() const;
};
