#include "stm32l4xx_hal.h"

#define MPU_AD0_VALUE 0

#if MPU_AD0_VALUE == 0
// Address of MPU6050 when AD0 pin in low
#define MPU_ADDRESS 0xD0
#endif
#if MPU_AD0_VALUE == 1
// Address of MPU6050 when ADO pin is high
#define MPU_ADDRESS 0xD2
#endif

#define MPU_REG_GYRO_CONFIG 0x1B
#define MPU_REG_ACCEL_CONFIG 0x1C
#define MPU_REG_ACEL_DATA 0x3B
#define MPU_REG_GYRO_DATA 0x43

HAL_StatusTypeDef init_mpu(I2C_HandleTypeDef* i2c_handler);
