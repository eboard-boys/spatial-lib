/* Licensed under the LGPL. */
#include <stdio.h>
#include <time.h>
#include "accel_dummy.h"
#include "vectors.h"

int main(void) {
    // Start timer - time in seconds
    time_t t = time(NULL);
    // Array that stores time at previous clock cycle and current time
    time_t time_array[2] = {};
    // Index values for positions of values within time_array
    int i_prev_time = 0;
    int i_curr_time = 1;

    init_accelerometer();

    // Initialize values
    float t = 0;
    vector_t acceleration[3] = {0,0,0};
    vector_t velocity[3] = {0,0,0};
    float speed = 0;
    vector_t displacement[3] = {0,0,0};
    float arc_length = 0;

    // Append current elapsed time in seconds to array each cycle
    time_array[i_curr_time] = t;
    float delta_t = (float)time_array[i_curr_time] - time_array[i_prev_time];

    // Retreieve raw acceleration vector values
    acc_vec_t get_current_acceleration();
    
    // Display acceleration
    vector_euler_step(acceleration, acceleration, delta_t);
    printf("Acceleration: %f", acceleration);

    // Display velocity
    vector_euler_step(acceleration, velocity, delta_t);
    printf("Velocity: %f", velocity);

    // Display speed (magnetude of velocity)

    // Display displacement
    vector_euler_step(velocity, displacement, delta_t);
    printf("Displacement: %f", displacement);

    // Display distance/arc length (odometer) - (integrate speed in respect to time)

    // Assign current time to previous time before start of new clock cycle
    time_array[i_prev_time] = t;

    return 0;
}
