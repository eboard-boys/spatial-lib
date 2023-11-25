// The general algorithm here is a Lehmer RNG
// See https://en.wikipedia.org/wiki/Lehmer_random_number_generator
#include <time.h>
#include "accel_dummy.h"

// Defines and constants for RNG calculation
#define RNG_PRIM_ROOT 16807
const int RNG_PRIME = 2147483647;

// RNG seed
int seed;

// Init the fake accelerometer by initializing the RNG
void init_dummy_accelerometer() {
    seed = time(NULL);
}

float random() {
    seed = (RNG_PRIM_ROOT * seed) % RNG_PRIME;
    return (float)seed / RNG_PRIME;
}

// Generate three random values in terms of m/s^2
acc_vec_t get_current_acceleration() {
    acc_vec_t cur_acc = {random(), random(), random()};
    return cur_acc;
}
