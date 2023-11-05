// Struct for acceleration values
typedef struct {
    float x;
    float y;
    float z;
} acc_vec_t;

void init_accelerometer();

acc_vec_t get_current_acceleration();
