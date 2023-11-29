/* High level interface function for updating and fetching sensor values.
 * Licensed under the LGPL. */
#include "../include/interface.h"

double current_acceleration[3] = {0.0, 0.0, 0.0};
double current_velocity[3] = {0.0, 0.0, 0.0};
double current_position[3] = {0.0, 0.0, 0.0};

HAL_StatusTypeDef init_spatial(I2C_HandleTypeDef* i2c_handler, UART_HandleTypeDef* debug_handler) {
	HAL_StatusTypeDef ret;
	ret = init_mpu(i2c_handler, debug_handler);
	if (ret) {
//		DEBUG_PRINT("Failed hardware initialization");
		return ret;
	}
	return HAL_OK;
}

HAL_StatusTypeDef update_acceleration() {
	HAL_StatusTypeDef ret;
	ret = get_accel(current_acceleration);
	if (ret) {
//		DEBUG_PRINT("Failed to update acceleration");
		return ret;
	}
	return HAL_OK;
}
