#ifdef __cplusplus
extern "C" {
#endif

#include "../src/accel_mpu6050.h"
#include "../src/vectors.h"

extern double current_acceleration[3];
extern double current_velocity[3];
extern double current_position[3];

HAL_StatusTypeDef init_spatial(I2C_HandleTypeDef* i2c_handler, UART_HandleTypeDef* debug_handler);

HAL_StatusTypeDef update_acceleration();

#ifdef __cplusplus
}
#endif
