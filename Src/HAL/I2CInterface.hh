/*********************************************
 * @brief Interface allowing a universal driver I2C
 *        across architectures
 * @author Nikolaos Xenofon Gkloumpos
 * @date 25/05/2023
 *********************************************/

#pragma once

#include <cstdint>

class I2CInterface {
    virtual void readBytes(uint8_t startingAddress, uint8_t consecutiveBytes, uint8_t *outputArray) = 0;
    virtual void writeByte(uint16_t targetAddress, uint8_t data) = 0;
    virtual uint8_t readByte(uint8_t address) = 0;
    virtual void writeBytes(uint8_t startingAddress, uint16_t numberOfBytes, uint8_t *dataToWrite) = 0;
};