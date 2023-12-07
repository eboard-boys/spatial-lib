/* Initialization and fetching of accelerometer data is done here.
 * Licensed/sub-licensed under the LGPL. Check the README file for attribution.*/
#include "accel_mpu6050.h"
#include "string.h"

I2C_HandleTypeDef* hi2c_mpu;
UART_HandleTypeDef* uart_debug_handler;

// Define a macro for debug prints
#define DEBUG_PRINT(message) \
    HAL_UART_Transmit(uart_debug_handler, (uint8_t*)message, strlen(message), I2C_DELAY)

magnitude_t accel_bias_x = 0;
magnitude_t accel_bias_y = 0;
magnitude_t accel_bias_z = 0;

vector_t gravitational_acceleration[3] = {0, 0, 0};

float unit_conversion = NO_CONVERSION;


HAL_StatusTypeDef init_mpu(I2C_HandleTypeDef* i2c_handler, UART_HandleTypeDef* debug_handler) {
	hi2c_mpu = i2c_handler;
	uart_debug_handler = debug_handler;
	HAL_StatusTypeDef ret;
    // Write power management configuration
	uint8_t data = MPU_PWR_MGMT_1_DEFAULT_CONFIG;
	ret = HAL_I2C_Mem_Write(hi2c_mpu, MPU_ADDRESS, MPU_REG_PWR_MGMT_1, I2C_MEMADD_SIZE_8BIT, &data, 1, I2C_DELAY);
	if (ret) {
		DEBUG_PRINT("Failed to initialize power management configuration\r\n");
		return ret;
	}
    // Write filter configuration
	data = MPU_FILTER_DELAY_5_MS;
	ret = HAL_I2C_Mem_Write(hi2c_mpu, MPU_ADDRESS, MPU_REG_FILTER_CONFIG, I2C_MEMADD_SIZE_8BIT, &data, 1, I2C_DELAY);
	if (ret) {
		DEBUG_PRINT("Failed to initialize DLPF configuration\r\n");
		return ret;
	}
    // Write gyroscope configuration
	data = MPU_GYRO_RANGE_500_DPS;
	ret = HAL_I2C_Mem_Write(hi2c_mpu, MPU_ADDRESS, MPU_REG_GYRO_CONFIG, I2C_MEMADD_SIZE_8BIT, &data, 1, I2C_DELAY);
	if (ret) {
		DEBUG_PRINT("Failed to initialize gyroscope configuration\r\n");
		return ret;
	}
    // Write accelerometer configuration
	data = MPU_ACCEL_RANGE_8G;
	ret = HAL_I2C_Mem_Write(hi2c_mpu, MPU_ADDRESS, MPU_REG_ACCEL_CONFIG, I2C_MEMADD_SIZE_8BIT, &data, 1, I2C_DELAY);
	if (ret) {
		DEBUG_PRINT("Failed to initialize accelerometer configuration\r\n");
		return ret;
	}
    return HAL_OK;
}

HAL_StatusTypeDef calibrate_mpu() {
	HAL_StatusTypeDef ret;
	vector_t target_vector[3] = {1, 0, 0};
	vector_t measured_accel[3];
	vector_t preliminary_bias[3];
	for (int i = 0; i < CALIBRATION_ITERATIONS; i++) {
		ret = get_accel(measured_accel);
		if (ret) {
			char fail_message[80];
			sprintf(fail_message, "Failed to calibrate accelerometer (1) call %d\r\n", i);
			DEBUG_PRINT(fail_message);
			return ret;
		}
		for (int j = 0; j < 3; j++) {
			preliminary_bias[j] += measured_accel[j];
		}
	}
	accel_bias_x = target_vector[0] - (preliminary_bias[0] / CALIBRATION_ITERATIONS);
	accel_bias_y = target_vector[1] - (preliminary_bias[1] / CALIBRATION_ITERATIONS);
	accel_bias_z = target_vector[2] - (preliminary_bias[2] / CALIBRATION_ITERATIONS);
	ret = get_accel(gravitational_acceleration);
	if (ret) {
		DEBUG_PRINT("Failed to calibrate accelerometer (2)\r\n");
		return ret;
	}
	unit_conversion = GS_TO_MPSPS;
	return HAL_OK;
}

HAL_StatusTypeDef get_accel(vector_t accel[3]) {
	HAL_StatusTypeDef ret;
	uint8_t accel_buf[6];
	ret = HAL_I2C_Mem_Read(hi2c_mpu, MPU_ADDRESS, MPU_REG_ACEL_DATA, I2C_MEMADD_SIZE_8BIT, accel_buf, 6, 100);
	if (ret) {
		DEBUG_PRINT("Failed to fetch accelerometer value\r\n");
		return ret;
	}
	int16_t accel_raw_x = (accel_buf[0] << 8) | accel_buf[1];
	int16_t accel_raw_y = (accel_buf[2] << 8) | accel_buf[3];
	int16_t accel_raw_z = (accel_buf[4] << 8) | accel_buf[5];

	accel[0] = (vector_t)accel_raw_x / MPU_ACCEL_RANGE_8G_LSB + accel_bias_x - gravitational_acceleration[0];
	accel[1] = (vector_t)accel_raw_y / MPU_ACCEL_RANGE_8G_LSB + accel_bias_y - gravitational_acceleration[1];
	accel[2] = (vector_t)accel_raw_z / MPU_ACCEL_RANGE_8G_LSB + accel_bias_z - gravitational_acceleration[2];

	accel[0] = (vector_t)(int)(accel[0] * 10) / 10 * unit_conversion;
	accel[1] = (vector_t)(int)(accel[1] * 10) / 10 * unit_conversion;
	accel[2] = (vector_t)(int)(accel[2] * 10) / 10 * unit_conversion;
	return HAL_OK;
}
