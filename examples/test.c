/* Licensed under the LGPL. */
#include <stdio.h>
#include <time.h>
#include "../src/accel_dummy.h"
#include "../src/vectors.h"

// Index values for positions of values within time_array
#define i_prev_time 0
#define i_curr_time 1

int main(void) {
    // Start timer - time in seconds
    time_t t = time(NULL);
    // Array that stores time at previous clock cycle and current time
    time_t time_array[2] = {0,0};

    init_accelerometer();

    // Initialize values
    // float t = 0;
    acc_vec_t raw_acceleration;
    vector_t acceleration[3] = {0,0,0};
    vector_t velocity[3] = {0,0,0};
    float speed = 0;
    vector_t displacement[3] = {0,0,0};
    float distance = 0;
    float arc_length = 0;

    // Append current elapsed time in seconds to array each cycle
    time_array[i_curr_time] = t;
    float delta_t = (float)time_array[i_curr_time] - time_array[i_prev_time];
    
    raw_acceleration = get_current_acceleration();
    acceleration[x] = raw_acceleration.x;
    acceleration[y] = raw_acceleration.y;
    acceleration[z] = raw_acceleration.z;

    // Calculate and display acceleration
    printf("\nAcceleration: %f %f %f\n", acceleration[x], acceleration[y], acceleration[z]);

    // Print the time delta that is used for Euler's
    printf("dt: %f\n", delta_t);

    // Calculate and display velocity
    vector_euler_step(acceleration, velocity, delta_t);
    printf("Velocity: %f %f %f\n", velocity[x], velocity[y], velocity[z]);

    // Calculate and display speed (magnitude of velocity)
    speed = magnitude(velocity);
    printf("Speed: %f\n", speed);

    // Calculate and display displacement
    vector_euler_step(velocity, displacement, delta_t);
    printf("Displacement: %f %f %f\n", displacement[x], displacement[y], displacement[z]);

    // What are you trying to do here???
    // Calculate and display distance
    // euler_step(displacement, distance, delta_t);
    // printf("Distance: %f\n", distance);

    // Calculate and display distance/arc length (odometer) - (integrate speed in respect to time)
    euler_step(magnitude(velocity), &arc_length, delta_t);
    printf("Arc Length: %f\n", arc_length);

    // Assign current time to previous time before start of new clock cycle
    time_array[i_prev_time] = t;

    return 0;
}
