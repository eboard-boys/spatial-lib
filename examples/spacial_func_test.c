/* Licensed under the LGPL. */
#include <stdio.h>
#include <time.h>
#include "../src/accel_dummy.h"
#include "../src/vectors.h"

int main(void) {
    clock_t prev_time, curr_time;
    double delta_t;

    prev_time = clock();
    curr_time = clock();

    init_accelerometer();

    // Initialize values
    acc_vec_t raw_acceleration;
    vector_t acceleration[3] = {0,0,0};
    vector_t velocity[3] = {0,0,0};
    float speed = 0;
    vector_t position[3] = {0,0,0};
    float arc_length = 0;
    
    // Type ctrl + c to end program
    while(1) {
        curr_time = clock();
        printf("\n----Starting of data, prev_time = %ld cycles----", prev_time);
        delta_t = (double)(curr_time - prev_time) / CLOCKS_PER_SEC; // Number seconds since last clock cycle recorded
        
        raw_acceleration = get_current_acceleration();
        acceleration[x] = raw_acceleration.x;
        acceleration[y] = raw_acceleration.y;
        acceleration[z] = raw_acceleration.z;

        // Calculate and display acceleration
        printf("\nAcceleration: <%f, %f, %f>\n", acceleration[x], acceleration[y], acceleration[z]);

        // Print the time delta that is used for Euler's
        printf("dt: %f\n", delta_t);

        // Calculate and display velocity
        vector_euler_step(acceleration, velocity, delta_t);
        printf("Velocity: <%f, %f, %f>\n", velocity[x], velocity[y], velocity[z]);

        // Calculate and display speed (magnitude of velocity)
        speed = magnitude(velocity);
        printf("Speed: %f\n", speed);

        // Calculate and display position
        vector_euler_step(velocity, position, delta_t);
        printf("Position: <%f, %f, %f>\n", position[x], position[y], position[z]);

        // Calculate and display distance/arc length (odometer) - (integrate speed in respect to time)
        euler_step(magnitude(velocity), &arc_length, delta_t);
        printf("Arc Length: %f\n", arc_length);
        
        prev_time = curr_time;
        printf("End of data, curr_time = %ld\n", curr_time);
    }

    return 0;
}
