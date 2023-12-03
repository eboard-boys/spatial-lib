/* High level interface function for updating and fetching sensor values.
 * Licensed under the LGPL. */
#include "../include/interface.h"

// Externally accessible via the interface header
double current_acceleration[3] = {0.0, 0.0, 0.0};

double current_velocity[3] = {0.0, 0.0, 0.0};
double current_speed = 0;

double current_position[3] = {0.0, 0.0, 0.0};
double current_distance = 0;

// Internal globals
double accleration_sample_array[ACCEL_SAMPLES][3];
uint8_t accel_sample_index = 0;

HAL_StatusTypeDef init_spatial(I2C_HandleTypeDef* i2c_handler, UART_HandleTypeDef* debug_handler) {
	HAL_StatusTypeDef ret;
	ret = init_mpu(i2c_handler, debug_handler);
	if (ret) {
//		DEBUG_PRINT("Failed hardware initialization");
		return ret;
	}
	ret = calibrate_mpu();
	if (ret) {
		return ret;
	}
	for (int i = 0; i < ACCEL_SAMPLES; i++) {
		get_accel(accleration_sample_array[i]);
	}
	return HAL_OK;
}

void reset_velocity() {
	current_velocity[0] = 0;
	current_velocity[1] = 0;
	current_velocity[2] = 0;

	current_speed = 0;
}

void reset_trip() {
	current_position[0] = 0;
	current_position[1] = 0;
	current_position[2] = 0;

	current_distance = 0;
}

HAL_StatusTypeDef update_acceleration_averages() {
	for (int i = 0; i < 5; i++) {
		HAL_StatusTypeDef ret;
		ret = get_accel(accleration_sample_array[accel_sample_index]);
		if (ret)
			return ret;
		accel_sample_index = (accel_sample_index + 1) % ACCEL_SAMPLES;
	}
	for (int i = 0; i < ACCEL_SAMPLES; i++) {
		current_acceleration[0] += accleration_sample_array[i][0];
		current_acceleration[1] += accleration_sample_array[i][1];
		current_acceleration[2] += accleration_sample_array[i][2];
	}
	current_acceleration[0] /= ACCEL_SAMPLES;
	current_acceleration[1] /= ACCEL_SAMPLES;
	current_acceleration[2] /= ACCEL_SAMPLES;
	return HAL_OK;
}

HAL_StatusTypeDef update_spatial(float delta_t) {
	HAL_StatusTypeDef ret;
	vector_euler_step(current_acceleration, current_velocity, delta_t);
	vector_euler_step(current_velocity, current_position, delta_t);
	current_speed = magnitude(current_velocity);
	euler_step(current_speed, &current_distance, delta_t);
	ret = update_acceleration_averages();
	if (ret) {
//		DEBUG_PRINT("Failed to update acceleration");
		return ret;
	}
	return HAL_OK;
}
