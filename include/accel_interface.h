#include "../src/accel_mpu6050.h"
#include "../src/vectors.h"

uint8_t init_accelerometer(I2C_HandleTypeDef* i2c_handler);

uint8_t get_acceleration(float acceleration[3]);
