/* Vector Math data types and operations are housed here.
 * Licensed under the LGPL. */
#include "vectors.h"
#include <math.h>

// Get the magnitude of a given vector
vector_element_t magnitude(vector_t vec) {
    return root_func((vec[x] * vec[x]) + (vec[x] * vec[x]) + (vec[x] * vec[x]));
}

// Euler's method for integration in respect to time in 3 dimensions
void update_velocity(vector_t accel_vec, vector_t velo_vec, float delta_t) {
    velo_vec[x] += accel_vec[x] * delta_t;
    velo_vec[y] += accel_vec[y] * delta_t;
    velo_vec[z] += accel_vec[z] * delta_t;
}
