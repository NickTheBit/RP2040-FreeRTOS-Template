/**********************************************
 * @brief  Bare-bone driver for the BME280 sensor.
 * @author Nikolaos Xenofon Gkloumpos
 * @date   6/1/23
 **********************************************/

#include "BME280Driver.h"

/**
 * @brief Initializes the BME280 class with i2c style communication with the chip.
 * @param i2cBus
 * @param address
 */
BME280Driver::BME280Driver(I2CInterface &i2cBus, uint8_t address) : i2cBus(i2cBus), address(address) {
}

void BME280Driver::readRegister(uint8_t registerAddress, uint8_t *returnedData, uint32_t length) {
    this->i2cBus.read(registerAddress, length, returnedData);
}

void BME280Driver::writeRegister(uint8_t registerAddress, uint8_t *dataToWrite, uint32_t length) {
    this->i2cBus.write(registerAddress, dataToWrite, length);
}

/**
 * @brief Probes the sensor to get latest environmental data.
 */
void BME280Driver::getSensorData() {
    uint8_t rawData[BME280::LEN_P_T_H_DATA] = { 0 };
    readRegister(BME280::REG_DATA, rawData,BME280::LEN_P_T_H_DATA);

    /* Variables to store the raw sensor data */
    struct rawMeasurements uncomp_data {};
    uint32_t data_xlsb;
    uint32_t data_lsb;
    uint32_t data_msb;

    /* Store the parsed register values for pressure data */
    data_msb = (uint32_t)rawData[0] << 12;
    data_lsb = (uint32_t)rawData[1] << 4;
    data_xlsb = (uint32_t)rawData[2] >> 4;
    uncomp_data.pressure = data_msb | data_lsb | data_xlsb;

    /* Store the parsed register values for temperature data */
    data_msb = (uint32_t)rawData[3] << 12;
    data_lsb = (uint32_t)rawData[4] << 4;
    data_xlsb = (uint32_t)rawData[5] >> 4;
    uncomp_data.temperature = data_msb | data_lsb | data_xlsb;

    /* Store the parsed register values for humidity data */
    data_msb = (uint32_t)rawData[6] << 8;
    data_lsb = (uint32_t)rawData[7];
    uncomp_data.humidity = data_msb | data_lsb;


}

double BME280Driver::getTemperature() {
    return this->currentMeasurements.temperature;
}

double BME280Driver::getHumidity() {
    return this->currentMeasurements.humidity;
}

double BME280Driver::getPressure() {
    return this->currentMeasurements.pressure;
}

