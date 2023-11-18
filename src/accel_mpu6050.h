#include "../lib/mpu6050/interface/driver_mpu6050_interface.h"

#ifdef __cplusplus
extern "C"{
#endif

#define ACCEL_SELECTED__CLOCK_SOURCE                   MPU6050_CLOCK_SOURCE_PLL_X_GYRO           /**< gyro pll x */
#define ACCEL_SELECTED__RATE                           50                                        /**< 50Hz */
#define ACCEL_SELECTED__LOW_PASS_FILTER                MPU6050_LOW_PASS_FILTER_3                 /**< low pass filter 3 */
#define ACCEL_SELECTED__CYCLE_WAKE_UP                  MPU6050_BOOL_FALSE                        /**< disable cycle wake up */
#define ACCEL_SELECTED__WAKE_UP_FREQUENCY              MPU6050_WAKE_UP_FREQUENCY_1P25_HZ         /**< 1.25Hz */
#define ACCEL_SELECTED__INTERRUPT_PIN_LEVEL            MPU6050_PIN_LEVEL_LOW                     /**< low level */
#define ACCEL_SELECTED__INTERRUPT_PIN_TYPE             MPU6050_PIN_TYPE_PUSH_PULL                /**< push pull */
#define ACCEL_SELECTED__ACCELEROMETER_RANGE            MPU6050_ACCELEROMETER_RANGE_2G            /**< 2g */
#define ACCEL_SELECTED__GYROSCOPE_RANGE                MPU6050_GYROSCOPE_RANGE_2000DPS           /**< 2000dps */
#define ACCEL_SELECTED__INTERRUPT_MOTION               MPU6050_BOOL_FALSE                        /**< disable motion */
#define ACCEL_SELECTED__INTERRUPT_FIFO_OVERFLOW        MPU6050_BOOL_FALSE                        /**< disable fifo overflow */
#define ACCEL_SELECTED__INTERRUPT_DMP                  MPU6050_BOOL_FALSE                        /**< disable dmp */
#define ACCEL_SELECTED__INTERRUPT_I2C_MAST             MPU6050_BOOL_FALSE                        /**< disable i2c master */
#define ACCEL_SELECTED__INTERRUPT_DATA_READY           MPU6050_BOOL_FALSE                        /**< disable data ready */
#define ACCEL_SELECTED__INTERRUPT_LATCH                MPU6050_BOOL_TRUE                         /**< enable latch */
#define ACCEL_SELECTED__INTERRUPT_READ_CLEAR           MPU6050_BOOL_TRUE                         /**< enable interrupt read clear */
#define ACCEL_SELECTED__EXTERN_SYNC                    MPU6050_EXTERN_SYNC_INPUT_DISABLED        /**< extern sync input disable */
#define ACCEL_SELECTED__FSYNC_INTERRUPT                MPU6050_BOOL_FALSE                        /**< disable fsync interrupt */
#define ACCEL_SELECTED__FSYNC_INTERRUPT_LEVEL          MPU6050_PIN_LEVEL_LOW                     /**< low level */
#define ACCEL_SELECTED__IIC_MASTER                     MPU6050_BOOL_FALSE                        /**< disable iic master */
#define ACCEL_SELECTED__IIC_BYPASS                     MPU6050_BOOL_FALSE                        /**< disable iic bypass */

#ifdef __cplusplus
}
#endif
