#ifdef __cplusplus
extern "C" {
#endif

#include "../src/accel_mpu6050.h"
#include "../src/vectors.h"

#define ACCEL_SAMPLES 10

extern vector_t current_acceleration[3];

extern vector_t current_velocity[3];
extern magnitude_t current_speed;

extern vector_t current_position[3];
extern magnitude_t current_distance;

HAL_StatusTypeDef init_spatial(I2C_HandleTypeDef* i2c_handler, UART_HandleTypeDef* debug_handler);

HAL_StatusTypeDef update_spatial(float delta_t);

void reset_velocity();

void reset_trip();

#ifdef __cplusplus
}
#endif
