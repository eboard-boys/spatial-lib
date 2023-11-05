/* Licensed under the LGPL. */
#include <stdio.h>
#include <time.h>
#include "../src/accel_dummy.h"
#include "../src/vectors.h"

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
    float distance = 0;
    float arc_length = 0;

    // Append current elapsed time in seconds to array each cycle
    time_array[i_curr_time] = t;
    float delta_t = (float)time_array[i_curr_time] - time_array[i_prev_time];
    
    // Calculate and display acceleration
    vector_euler_step(get_current_acceleration(), acceleration, delta_t);
    printf("\nAcceleration: %f\n", acceleration);

    // Calculate and display velocity
    vector_euler_step(acceleration, velocity, delta_t);
    printf("Velocity: %f", velocity);

    // Calculate and display speed (magnetude of velocity)
    speed = magnitude(velocity);
    printf("Speed: %f\n", speed);

    // Calculate and display displacement
    vector_euler_step(velocity, displacement, delta_t);
    printf("Displacement: %f", displacement);

    // Calculate and display distance
    euler_step(displacement, distance, delta_t);
    printf("Distance: %f", distance);

    // Calculate and display distance/arc length (odometer) - (integrate speed in respect to time)
    euler_step(distance, arc_length, delta_t);
    printf("Arc Length: %f", arc_length);

    // Assign current time to previous time before start of new clock cycle
    time_array[i_prev_time] = t;

    return 0;
}
