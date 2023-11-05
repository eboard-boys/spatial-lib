// Struct for acceleration values - acceleration vector type
typedef struct {
    float x;
    float y;
    float z;
} acc_vec_t;

// Initialize MPU 6050 accelerometer
void init_accelerometer();

// Return acceleration vector value
acc_vec_t get_current_acceleration();
