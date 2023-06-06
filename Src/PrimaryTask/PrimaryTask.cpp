/*********************************************
 * @brief Entry point for user code in the Template, if tasks
 * spawn like a tree, this is the task that spawns them all.
 * @author Nikolaos Xenofon Gkloumpos
 * @date 25/05/2023
 *********************************************/

#include "PrimaryTask.hh"
#include "main/main.h"
#include "HAL/RP2040/PR2040_GPIO/RP2040_GPIOPin.hh"
#include "HAL/RP2040/RP2040_I2C/RP2040_I2C.h"

int reg_read(i2c_inst_t *i2c,
             const uint addr,
             const uint8_t reg,
             uint8_t *buf,
             const uint8_t nbytes) {

    int num_bytes_read = 0;

    // Check to make sure caller is asking for 1 or more bytes
    if (nbytes < 1) {
        return 0;
    }

    // Read data from register(s) over I2C
    i2c_write_blocking(i2c, addr, &reg, 1, true);
    num_bytes_read = i2c_read_blocking(i2c, addr, buf, nbytes, false);

    return num_bytes_read;
}

void primaryTask(void *arguments) {
    // Configure the Pico's on-board LED as a heartbeat indicator.

    auto heartbeatPin = RP2040_GPIOPin(PICO_DEFAULT_LED_PIN);
    auto i2cBus1 = RP2040_I2C(i2c1, 2, 3, false, 1000 * 100);


    while (true) {
        // Starting a heartbeat to indicate proper initialization.
        heartbeatPin.write(HAL::GPIO_STATE::LOW);
        vTaskDelay(1000);
        heartbeatPin.write(HAL::GPIO_STATE::HIGH);
        vTaskDelay(50);
    }
}