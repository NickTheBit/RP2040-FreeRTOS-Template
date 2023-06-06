/*********************************************
 * @brief Interface allowing a universal driver I2C
 *        across architectures
 * @author Nikolaos Xenofon Gkloumpos
 * @date 25/05/2023
 *********************************************/

#pragma once

#include <cstdint>

class I2CInterface {
    virtual void read(uint8_t address, uint8_t consecutiveBytes, uint8_t *outputArray) = 0;
    virtual void write(uint8_t startingAddress, uint8_t *payload, uint16_t payloadSize) = 0;
};