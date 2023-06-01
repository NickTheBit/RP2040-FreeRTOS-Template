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
    i2c_inst_t hardwareInterface;
    uint16_t responseTimeout;
    uint16_t baudrateHz;
    bool slaveMode;

public:
    RP2040_I2C(i2c_inst &hardwareInterface, uint16_t baudrateHz, uint16_t responseTimeout, bool slaveMode);
    ~RP2040_I2C();
    uint16_t readRegister(uint8_t targetRegister, uint8_t consecutiveBytes) override;
    void writeRegister(uint8_t targetRegister, uint8_t data) override;
    uint16_t getResponseTimeout() const;
    uint16_t getBaudrateHz() const;
    bool isSlaveMode() const;
};
