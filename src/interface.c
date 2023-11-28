/* High level interface function for updating and fetching sensor values.
 * Licensed under the LGPL. */
#include "../include/interface.h"
#include "accel_mpu6050.h"
#include "vectors.h"

vector_t current_acceleration[3] = {0, 0, 0};
vector_t current_velocity[3] = {0, 0, 0};
vector_t current_position[3] = {0, 0, 0};

HAL_StatusTypeDef init_spatial(I2C_HandleTypeDef* i2c_handler, UART_HandleTypeDef* debug_handler) {
	HAL_StatusTypeDef ret;
	ret = init_mpu(i2c_handler, debug_handler);
	if (ret) {
		DEBUG_PRINT("Failed hardware initialization");
		return ret;
	}
	return HAL_OK;
}


