/* Initialization and fetching of accelerometer data is done here.
 * Licensed/sub-licensed under the LGPL. Check the README file for attribution.*/
#include "accel_mpu6050.h"
#include "string.h"

I2C_HandleTypeDef* hi2c_mpu;
UART_HandleTypeDef* uart_debug_handler;

// Define a macro for debug prints
#define DEBUG_PRINT(message) \
    HAL_UART_Transmit(uart_debug_handler, (uint8_t*)message, strlen(message), I2C_DELAY)


HAL_StatusTypeDef init_mpu(I2C_HandleTypeDef* i2c_handler, UART_HandleTypeDef* debug_handler) {
	hi2c_mpu = i2c_handler;
	uart_debug_handler = debug_handler;
	HAL_StatusTypeDef ret;
    // Write power management configuration
	uint8_t data = MPU_PWR_MGMT_1_DEFAULT_CONFIG;
	ret = HAL_I2C_Mem_Write(hi2c_mpu, MPU_ADDRESS, MPU_REG_PWR_MGMT_1, I2C_MEMADD_SIZE_8BIT, &data, 1, I2C_DELAY);
	if (ret) {
		DEBUG_PRINT("Failed to initialize power management configuration");
		return ret;
	}
    // Write filter configuration
	data = MPU_FILTER_DELAY_19_MS;
	ret = HAL_I2C_Mem_Write(hi2c_mpu, MPU_ADDRESS, MPU_REG_FILTER_CONFIG, I2C_MEMADD_SIZE_8BIT, &data, 1, I2C_DELAY);
	if (ret) {
		DEBUG_PRINT("Failed to initialize DLPF configuration");
		return ret;
	}
    // Write gyroscope configuration
	data = MPU_GYRO_RANGE_500_DPS;
	ret = HAL_I2C_Mem_Write(hi2c_mpu, MPU_ADDRESS, MPU_REG_GYRO_CONFIG, I2C_MEMADD_SIZE_8BIT, &data, 1, I2C_DELAY);
	if (ret) {
		DEBUG_PRINT("Failed to initialize gyroscope configuration");
		return ret;
	}
    // Write accelerometer configuration
	data = MPU_ACCEL_RANGE_4G;
	ret = HAL_I2C_Mem_Write(hi2c_mpu, MPU_ADDRESS, MPU_REG_ACCEL_CONFIG, I2C_MEMADD_SIZE_8BIT, &data, 1, I2C_DELAY);
	if (ret) {
		DEBUG_PRINT("Failed to initialize accelerometer configuration");
		return ret;
	}
    return HAL_OK;
}

HAL_StatusTypeDef get_accel(double accel[3]) {
	HAL_StatusTypeDef ret;
	uint8_t accel_buf[6];
	ret = HAL_I2C_Mem_Read(hi2c_mpu, MPU_ADDRESS, MPU_REG_ACEL_DATA, I2C_MEMADD_SIZE_8BIT, accel_buf, 6, I2C_DELAY);
	if (ret) {
		DEBUG_PRINT("Failed to fetch accelerometer value");
		return ret;
	}
	int16_t accel_raw_x = (accel_buf[0] << 8) | accel_buf[1];
	int16_t accel_raw_y = (accel_buf[2] << 8) | accel_buf[3];
	int16_t accel_raw_z = (accel_buf[4] << 8) | accel_buf[5];

	accel[0] = (double)accel_raw_x / MPU_ACCEL_RANGE_4G_LSB;
	accel[1] = (double)accel_raw_y / MPU_ACCEL_RANGE_4G_LSB;
	accel[2] = (double)accel_raw_z / MPU_ACCEL_RANGE_4G_LSB;
	return HAL_OK;
}
