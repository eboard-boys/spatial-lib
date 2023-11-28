#include "stm32l4xx_hal.h"

#define MPU_AD0_VALUE 0
#define I2C_DELAY 50

#if MPU_AD0_VALUE == 0
// Address of MPU6050 when AD0 pin in low
#define MPU_ADDRESS 0xD0
#endif
#if MPU_AD0_VALUE == 1
// Address of MPU6050 when ADO pin is high
#define MPU_ADDRESS 0xD2
#endif

// Register Addresses
#define MPU_REG_FILTER_CONFIG 0x1A
#define MPU_REG_GYRO_CONFIG 0x1B
#define MPU_REG_ACCEL_CONFIG 0x1C
#define MPU_REG_ACEL_DATA 0x3B
#define MPU_REG_GYRO_DATA 0x43
#define MPU_REG_PWR_MGMT_1 0x6B
#define MPU_REG_PWR_MGMT_2 0x6C

// Sync/Filter Configs
// Higher delays allow for intense filtering
#define MPU_FILTER_DELAY_0_MS 0
#define MPU_FILTER_DELAY_2_MS 1
#define MPU_FILTER_DELAY_3_MS 2
#define MPU_FILTER_DELAY_5_MS 3
#define MPU_FILTER_DELAY_9_MS 4
#define MPU_FILTER_DELAY_14_MS 5
#define MPU_FILTER_DELAY_19_MS 6

// Gyro Configs
#define MPU_GYRO_RANGE_250_DPS 0
#define MPU_GYRO_RANGE_500_DPS (1 << 3)
#define MPU_GYRO_RANGE_1000_DPS (2 << 3)
#define MPU_GYRO_RANGE_2000_DPS (3 << 3)

// Gyro Sensitivity Dividers
#define MPU_GYRO_RANGE_250_DPS_LSB 131
#define MPU_GYRO_RANGE_500_DPS_LSB 65.5
#define MPU_GYRO_RANGE_1000_DPS_LSB 32.8
#define MPU_GYRO_RANGE_2000_DPS_LSB 16.4

// Accelerometer Configs
#define MPU_ACCEL_RANGE_2G 0
#define MPU_ACCEL_RANGE_4G (1 << 3)
#define MPU_ACCEL_RANGE_8G (2 << 3)
#define MPU_ACCEL_RANGE_16G (3 << 3)

// Accelerometer Sensitivity Dividers
#define MPU_ACCEL_RANGE_2G_LSB 16384
#define MPU_ACCEL_RANGE_4G_LSB 8192
#define MPU_ACCEL_RANGE_8G_LSB 4096
#define MPU_ACCEL_RANGE_16G_LSB 2048


// Power Managment Configs
// Power Management 1 Register
#define MPU_PWR_MGMT_RESET (1 << 7)
#define MPU_PWR_MGMT_SLEEP (1 << 6)
#define MPU_PWR_MGMT_CYCLE (1 << 5)
#define MPU_PWR_MGMT_TEMP_DISABLE (1 << 3)
#define MPU_PWR_MGMT_CLK_INTERNAL 0
#define MPU_PWR_MGMT_CLK_PLL_X_GYRO 1
#define MPU_PWR_MGMT_CLK_PLL_Y_GYRO 2
#define MPU_PWR_MGMT_CLK_PLL_Z_GYRO 3
#define MPU_PWR_MGMT_CLK_STOP 7

#define MPU_PWR_MGMT_1_DEFAULT_CONFIG MPU_PWR_MGMT_CLK_INTERNAL

// Power Management 2 Register
#define MPU_PWR_MGMT_WAKE_1P25_HZ 0
#define MPU_PWR_MGMT_WAKE_5_HZ (1 << 6)
#define MPU_PWR_MGMT_WAKE_20_HZ (2 << 6)
#define MPU_PWR_MGMT_WAKE_40_HZ (3 << 6)
#define MPU_PWR_MGMT_STBY_ACCEL_X (1 << 5)
#define MPU_PWR_MGMT_STBY_ACCEL_Y (1 << 4)
#define MPU_PWR_MGMT_STBY_ACCEL_Z (1 << 3)
#define MPU_PWR_MGMT_STBY_GYRO_X (1 << 2)
#define MPU_PWR_MGMT_STBY_GYRO_Y (1 << 1)
#define MPU_PWR_MGMT_STBY_GYRO_Z 1

// Constants for unit conversion
#define GS_TO_MPSPS 9.8

HAL_StatusTypeDef init_mpu(I2C_HandleTypeDef* i2c_handler, UART_HandleTypeDef* debug_handler);

HAL_StatusTypeDef get_accel(double accel[3]);
