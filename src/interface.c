/* High level interface function for updating and fetching sensor values.
 * Licensed under the LGPL. */
#include "../include/accel_interface.h"
//#include "accel_mpu6050.h"
//#include "vectors.h"

uint8_t init_accelerometer(I2C_HandleTypeDef* i2c_handler) {
	if (set_iic_handler(i2c_handler))
		return 1;
	if (mpu6050_basic_init())
		return 1;
	return 0;
}

uint8_t get_acceleration(float acceleration[3]) {
	float gyro[3];
	return mpu6050_basic_read(acceleration, gyro);
}
