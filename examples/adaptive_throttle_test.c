/* Licensed under the LGPL. */
#include <stdio.h>
#include <time.h>
#include <math.h>
#include "../src/accel_dummy.h"
#include "../src/vectors.h"

int main(void) {
    // Start measuring time
    struct timespec begin, end; 
    clock_gettime(CLOCK_REALTIME, &begin);
    long seconds;
    long nanoseconds;
    double elapsed_time;

    // Math func of path in xy direction - path traveled
    float A = 1.75;
    float B = 1;
    float a = 0.1;
    float xy_path;
    // Math func of path in z direction - elevation path
    float f = 0.75; // changes frequency
    float z_path;

    while (1) {
        // Stop measuring time and calculate the elapsed time
        clock_gettime(CLOCK_REALTIME, &end);
        seconds = end.tv_sec - begin.tv_sec;
        nanoseconds = end.tv_nsec - begin.tv_nsec;
        elapsed_time = seconds + nanoseconds*1e-9;

        printf("Time measured: %.3f seconds.\n", elapsed_time);

        xy_path = A * sin(B*elapsed_time) + (a * pow(elapsed_time,2)); // Path function
        z_path = sin(f * elapsed_time); // Elevation function

        printf("Position: (%lf.3f,%f.3f,%f.3f)\n", elapsed_time, xy_path, z_path);
    }
    
    return 0;
}