/*********************************************
 * @brief Interface allowing a universal driver I2C
 *        across architectures
 * @author Nikolaos Xenofon Gkloumpos
 * @date 25/05/2023
 *********************************************/

#pragma once

#include <cstdint>

class I2CInterface {
    virtual uint16_t readRegister(uint8_t targetRegister, uint8_t consecutiveBytes = 1) = 0;
    virtual void writeRegister(uint8_t targetRegister, uint8_t data) = 0;
};