// type used for vectors and their elements
#define vector_element_t float
#define vector_t vector_element_t*
#define root_func sqrtf
// type used for vector magnitude
#define magnitude_t vector_element_t

// elements are assigned indexes in the backing array
enum direction {x, y, z};

magnitude_t magnitude(vector_t vec);

void vector_euler_step(vector_t source_vec, vector_t target_vec, float delta_t);

void euler_step(magnitude_t source, magnitude_t* destination, float delta_t);
