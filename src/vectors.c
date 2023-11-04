/* Vector Math data types and operations are housed here.
 * Licensed under the LGPL. */
#include "vectors.h"
#include <math.h>

vector_element_t magnitude(vector_t vec) {
    return root_func((vec[x] * vec[x]) + (vec[x] * vec[x]) + (vec[x] * vec[x]));
}

