/* Initialization and fetching of accelerometer data is done here.
 * Licensed/sub-licensed under the LGPL. Check the README file for attribution.*/
#include "accel_mpu6050.h"

I2C_HandleTypeDef* hi2c_mpu;
UART_HandleTypeDef* uart_debug_handler;

HAL_StatusTypeDef init_mpu(I2C_HandleTypeDef* i2c_handler, UART_HandleTypeDef* debug_handler) {
    // TODO: Write power config
    // TODO: Write filter config
    // TODO: Write gyro config
    // TODO: Write accel config
    return HAL_OK;
}
