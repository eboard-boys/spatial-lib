/* Vector Math data types and operations are housed here.
 * Licensed under the LGPL. */

// type used for vectors and their elements
#define vector_t float
#define root_func sqrtf
// type used for vector magnitude
#define magnitude_t vector_t

// elements are assigned indexes in the backing array
enum direction {x, y, z};
enum direction_polar {r, theta, phi};
enum delta {prev, curr};

magnitude_t magnitude(vector_t* vec);

void vector_euler_step(vector_t* source_vec, vector_t* target_vec, float delta_t);

void euler_step(magnitude_t source, magnitude_t* destination, float delta_t);

void set_slope(vector_t* velocities, float slope, float dt);

void cross(vector_t* source_vec1, vector_t* source_vec2, vector_t* normal_vec);

vector_t* cartesian_to_spherical(vector_t* cartesian_vec);

vector_t* spherical_to_cartesian(vector_t* spherical_vec);
