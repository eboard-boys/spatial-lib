/* Vector Math data types and operations are housed here.
 * Licensed under the LGPL. */
#include "vectors.h"
#include <math.h>
#include <stdlib.h>

// Get the magnitude of a given vector
magnitude_t magnitude(vector_t* vec) {
    return root_func((vec[x] * vec[x]) + (vec[y] * vec[y]) + (vec[z] * vec[z]));
}

// Eulers method for integration in respect to time in 3 dimensions.
// Example: pass acceleration vector to source and velocity to target to integrate acceleration
void vector_euler_step(vector_t* source_vec, vector_t* target_vec, float delta_t) {
    target_vec[x] += source_vec[x] * delta_t;
    target_vec[y] += source_vec[y] * delta_t;
    target_vec[z] += source_vec[z] * delta_t;
}

// Eulers method for integration in respect to time for scalars.
// This is used for calculating arc length.
void euler_step(magnitude_t source, magnitude_t* destination, float delta_t) {
    *destination += source * delta_t;
}

vector_t* cartesian_to_spherical(vector_t* cartesian_vec) {
    vector_t* spherical_vec = malloc(sizeof(vector_t) * 3);
    spherical_vec[r] = magnitude(cartesian_vec);
    spherical_vec[theta] = acos(cartesian_vec[z]/spherical_vec[r]);
    float sgn = signbit(cartesian_vec[y]) ? -1 : 1;
    spherical_vec[phi] = sgn * acos(cartesian_vec[x]/root_func(cartesian_vec[x]*cartesian_vec[x] + cartesian_vec[y]*cartesian_vec[y]));
    return spherical_vec;
}
