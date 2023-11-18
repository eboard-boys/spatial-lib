/* Abstracted away initialization and fetching of accelerometer data is done here.
 * Licensed/sub-licensed under the LGPL. Check the mpu6050 directory for attribution.*/
#include "accel_mpu6050.h"

uint8_t mpu6050_basic_init(mpu6050_address_t addr_pin)
{
    uint8_t res;

    /* link interface function */
    DRIVER_MPU6050_LINK_INIT(&gs_handle, mpu6050_handle_t);
    DRIVER_MPU6050_LINK_IIC_INIT(&gs_handle, mpu6050_interface_iic_init);
//    DRIVER_MPU6050_LINK_IIC_DEINIT(&gs_handle, mpu6050_interface_iic_deinit);
    DRIVER_MPU6050_LINK_IIC_READ(&gs_handle, mpu6050_interface_iic_read);
    DRIVER_MPU6050_LINK_IIC_WRITE(&gs_handle, mpu6050_interface_iic_write);
    DRIVER_MPU6050_LINK_DELAY_MS(&gs_handle, mpu6050_interface_delay_ms);
    DRIVER_MPU6050_LINK_DEBUG_PRINT(&gs_handle, mpu6050_interface_debug_print);
    DRIVER_MPU6050_LINK_RECEIVE_CALLBACK(&gs_handle, mpu6050_interface_receive_callback);

    /* set the addr pin */
    res = mpu6050_set_addr_pin(&gs_handle, addr_pin);
    if (res != 0)
    {
        mpu6050_interface_debug_print("mpu6050: set addr pin failed.\n");

        return 1;
    }

    /* init */
    res = mpu6050_init(&gs_handle);
    if (res != 0)
    {
        mpu6050_interface_debug_print("mpu6050: init failed.\n");

        return 1;
    }

    /* delay 100 ms */
    mpu6050_interface_delay_ms(100);

    /* disable sleep */
    res = mpu6050_set_sleep(&gs_handle, MPU6050_BOOL_FALSE);
    if (res != 0)
    {
        mpu6050_interface_debug_print("mpu6050: set sleep failed.\n");
        (void)mpu6050_deinit(&gs_handle);

        return 1;
    }

    /* set the default clock source */
    res = mpu6050_set_clock_source(&gs_handle, ACCEL_SELECTED__CLOCK_SOURCE);
    if (res != 0)
    {
        mpu6050_interface_debug_print("mpu6050: set clock source failed.\n");
        (void)mpu6050_deinit(&gs_handle);

        return 1;
    }

    /* set the default rate */
    res = mpu6050_set_sample_rate_divider(&gs_handle, 1000 / (ACCEL_SELECTED__RATE - 1));
    if (res != 0)
    {
        mpu6050_interface_debug_print("mpu6050: set sample rate divider failed.\n");
        (void)mpu6050_deinit(&gs_handle);

        return 1;
    }

    /* set the default low pass filter */
    res = mpu6050_set_low_pass_filter(&gs_handle, ACCEL_SELECTED__LOW_PASS_FILTER);
    if (res != 0)
    {
        mpu6050_interface_debug_print("mpu6050: set low pass filter failed.\n");
        (void)mpu6050_deinit(&gs_handle);

        return 1;
    }

    /* enable temperature sensor */
    res = mpu6050_set_temperature_sensor(&gs_handle, MPU6050_BOOL_TRUE);
    if (res != 0)
    {
        mpu6050_interface_debug_print("mpu6050: set temperature sensor failed.\n");
        (void)mpu6050_deinit(&gs_handle);

        return 1;
    }

    /* set the default cycle wake up */
    res = mpu6050_set_cycle_wake_up(&gs_handle, ACCEL_SELECTED__CYCLE_WAKE_UP);
    if (res != 0)
    {
        mpu6050_interface_debug_print("mpu6050: set cycle wake up failed.\n");
        (void)mpu6050_deinit(&gs_handle);

        return 1;
    }

    /* set the default wake up frequency */
    res = mpu6050_set_wake_up_frequency(&gs_handle, ACCEL_SELECTED__WAKE_UP_FREQUENCY);
    if (res != 0)
    {
        mpu6050_interface_debug_print("mpu6050: set wake up frequency failed.\n");
        (void)mpu6050_deinit(&gs_handle);

        return 1;
    }

    /* enable acc x */
    res = mpu6050_set_standby_mode(&gs_handle, MPU6050_SOURCE_ACC_X, MPU6050_BOOL_FALSE);
    if (res != 0)
    {
        mpu6050_interface_debug_print("mpu6050: set standby mode failed.\n");
        (void)mpu6050_deinit(&gs_handle);

        return 1;
    }

    /* enable acc y */
    res = mpu6050_set_standby_mode(&gs_handle, MPU6050_SOURCE_ACC_Y, MPU6050_BOOL_FALSE);
    if (res != 0)
    {
        mpu6050_interface_debug_print("mpu6050: set standby mode failed.\n");
        (void)mpu6050_deinit(&gs_handle);

        return 1;
    }

    /* enable acc z */
    res = mpu6050_set_standby_mode(&gs_handle, MPU6050_SOURCE_ACC_Z, MPU6050_BOOL_FALSE);
    if (res != 0)
    {
        mpu6050_interface_debug_print("mpu6050: set standby mode failed.\n");
        (void)mpu6050_deinit(&gs_handle);

        return 1;
    }

    /* enable gyro x */
    res = mpu6050_set_standby_mode(&gs_handle, MPU6050_SOURCE_GYRO_X, MPU6050_BOOL_FALSE);
    if (res != 0)
    {
        mpu6050_interface_debug_print("mpu6050: set standby mode failed.\n");
        (void)mpu6050_deinit(&gs_handle);

        return 1;
    }

    /* enable gyro y */
    res = mpu6050_set_standby_mode(&gs_handle, MPU6050_SOURCE_GYRO_Y, MPU6050_BOOL_FALSE);
    if (res != 0)
    {
        mpu6050_interface_debug_print("mpu6050: set standby mode failed.\n");
        (void)mpu6050_deinit(&gs_handle);

        return 1;
    }

    /* enable gyro z */
    res = mpu6050_set_standby_mode(&gs_handle, MPU6050_SOURCE_GYRO_Z, MPU6050_BOOL_FALSE);
    if (res != 0)
    {
        mpu6050_interface_debug_print("mpu6050: set standby mode failed.\n");
        (void)mpu6050_deinit(&gs_handle);

        return 1;
    }

    /* disable gyroscope x test */
    res = mpu6050_set_gyroscope_test(&gs_handle, MPU6050_AXIS_X, MPU6050_BOOL_FALSE);
    if (res != 0)
    {
        mpu6050_interface_debug_print("mpu6050: set gyroscope test failed.\n");
        (void)mpu6050_deinit(&gs_handle);

        return 1;
    }

    /* disable gyroscope y test */
    res = mpu6050_set_gyroscope_test(&gs_handle, MPU6050_AXIS_Y, MPU6050_BOOL_FALSE);
    if (res != 0)
    {
        mpu6050_interface_debug_print("mpu6050: set gyroscope test failed.\n");
        (void)mpu6050_deinit(&gs_handle);

        return 1;
    }

    /* disable gyroscope z test */
    res = mpu6050_set_gyroscope_test(&gs_handle, MPU6050_AXIS_Z, MPU6050_BOOL_FALSE);
    if (res != 0)
    {
        mpu6050_interface_debug_print("mpu6050: set gyroscope test failed.\n");
        (void)mpu6050_deinit(&gs_handle);

        return 1;
    }

    /* disable accelerometer x test */
    res = mpu6050_set_accelerometer_test(&gs_handle, MPU6050_AXIS_X, MPU6050_BOOL_FALSE);
    if (res != 0)
    {
        mpu6050_interface_debug_print("mpu6050: set accelerometer test failed.\n");
        (void)mpu6050_deinit(&gs_handle);

        return 1;
    }

    /* disable accelerometer y test */
    res = mpu6050_set_accelerometer_test(&gs_handle, MPU6050_AXIS_Y, MPU6050_BOOL_FALSE);
    if (res != 0)
    {
        mpu6050_interface_debug_print("mpu6050: set accelerometer test failed.\n");
        (void)mpu6050_deinit(&gs_handle);

        return 1;
    }

    /* disable accelerometer z test */
    res = mpu6050_set_accelerometer_test(&gs_handle, MPU6050_AXIS_Z, MPU6050_BOOL_FALSE);
    if (res != 0)
    {
        mpu6050_interface_debug_print("mpu6050: set accelerometer test failed.\n");
        (void)mpu6050_deinit(&gs_handle);

        return 1;
    }

    /* disable fifo */
    res = mpu6050_set_fifo(&gs_handle, MPU6050_BOOL_FALSE);
    if (res != 0)
    {
        mpu6050_interface_debug_print("mpu6050: set fifo failed.\n");
        (void)mpu6050_deinit(&gs_handle);

        return 1;
    }

    /* disable temp fifo */
    res = mpu6050_set_fifo_enable(&gs_handle, MPU6050_FIFO_TEMP, MPU6050_BOOL_FALSE);
    if (res != 0)
    {
        mpu6050_interface_debug_print("mpu6050: set fifo enable failed.\n");
        (void)mpu6050_deinit(&gs_handle);

        return 1;
    }

    /* disable xg fifo */
    res = mpu6050_set_fifo_enable(&gs_handle, MPU6050_FIFO_XG, MPU6050_BOOL_FALSE);
    if (res != 0)
    {
        mpu6050_interface_debug_print("mpu6050: set fifo enable failed.\n");
        (void)mpu6050_deinit(&gs_handle);

        return 1;
    }

    /* disable yg fifo */
    res = mpu6050_set_fifo_enable(&gs_handle, MPU6050_FIFO_YG, MPU6050_BOOL_FALSE);
    if (res != 0)
    {
        mpu6050_interface_debug_print("mpu6050: set fifo enable failed.\n");
        (void)mpu6050_deinit(&gs_handle);

        return 1;
    }

    /* disable zg fifo */
    res = mpu6050_set_fifo_enable(&gs_handle, MPU6050_FIFO_ZG, MPU6050_BOOL_FALSE);
    if (res != 0)
    {
        mpu6050_interface_debug_print("mpu6050: set fifo enable failed.\n");
        (void)mpu6050_deinit(&gs_handle);

        return 1;
    }

    /* disable accel fifo */
    res = mpu6050_set_fifo_enable(&gs_handle, MPU6050_FIFO_ACCEL, MPU6050_BOOL_FALSE);
    if (res != 0)
    {
        mpu6050_interface_debug_print("mpu6050: set fifo enable failed.\n");
        (void)mpu6050_deinit(&gs_handle);

        return 1;
    }

    /* set the default interrupt level */
    res = mpu6050_set_interrupt_level(&gs_handle, ACCEL_SELECTED__INTERRUPT_PIN_LEVEL);
    if (res != 0)
    {
        mpu6050_interface_debug_print("mpu6050: set interrupt level failed.\n");
        (void)mpu6050_deinit(&gs_handle);

        return 1;
    }

    /* set the default pin type */
    res = mpu6050_set_interrupt_pin_type(&gs_handle, ACCEL_SELECTED__INTERRUPT_PIN_TYPE);
    if (res != 0)
    {
        mpu6050_interface_debug_print("mpu6050: set interrupt pin type failed.\n");
        (void)mpu6050_deinit(&gs_handle);

        return 1;
    }

    /* set the default motion interrupt */
    res = mpu6050_set_interrupt(&gs_handle, MPU6050_INTERRUPT_MOTION, ACCEL_SELECTED__INTERRUPT_MOTION);
    if (res != 0)
    {
        mpu6050_interface_debug_print("mpu6050: set interrupt failed.\n");
        (void)mpu6050_deinit(&gs_handle);

        return 1;
    }

    /* set the default fifo overflow interrupt */
    res = mpu6050_set_interrupt(&gs_handle, MPU6050_INTERRUPT_FIFO_OVERFLOW, ACCEL_SELECTED__INTERRUPT_FIFO_OVERFLOW);
    if (res != 0)
    {
        mpu6050_interface_debug_print("mpu6050: set interrupt failed.\n");
        (void)mpu6050_deinit(&gs_handle);

        return 1;
    }

    /* set the default dmp interrupt */
    res = mpu6050_set_interrupt(&gs_handle, MPU6050_INTERRUPT_DMP, ACCEL_SELECTED__INTERRUPT_DMP);
    if (res != 0)
    {
        mpu6050_interface_debug_print("mpu6050: set interrupt failed.\n");
        (void)mpu6050_deinit(&gs_handle);

        return 1;
    }

    /* set the default i2c master interrupt */
    res = mpu6050_set_interrupt(&gs_handle, MPU6050_INTERRUPT_I2C_MAST, ACCEL_SELECTED__INTERRUPT_I2C_MAST);
    if (res != 0)
    {
        mpu6050_interface_debug_print("mpu6050: set interrupt failed.\n");
        (void)mpu6050_deinit(&gs_handle);

        return 1;
    }

    /* set the default data ready interrupt */
    res = mpu6050_set_interrupt(&gs_handle, MPU6050_INTERRUPT_DATA_READY, ACCEL_SELECTED__INTERRUPT_DATA_READY);
    if (res != 0)
    {
        mpu6050_interface_debug_print("mpu6050: set interrupt failed.\n");
        (void)mpu6050_deinit(&gs_handle);

        return 1;
    }

    /* set the default interrupt latch */
    res = mpu6050_set_interrupt_latch(&gs_handle, ACCEL_SELECTED__INTERRUPT_LATCH);
    if (res != 0)
    {
        mpu6050_interface_debug_print("mpu6050: set interrupt latch failed.\n");
        (void)mpu6050_deinit(&gs_handle);

        return 1;
    }

    /* set the default interrupt read clear */
    res = mpu6050_set_interrupt_read_clear(&gs_handle, ACCEL_SELECTED__INTERRUPT_READ_CLEAR);
    if (res != 0)
    {
        mpu6050_interface_debug_print("mpu6050: set interrupt read clear failed.\n");
        (void)mpu6050_deinit(&gs_handle);

        return 1;
    }

    /* set the extern sync */
    res = mpu6050_set_extern_sync(&gs_handle, ACCEL_SELECTED__EXTERN_SYNC);
    if (res != 0)
    {
        mpu6050_interface_debug_print("mpu6050: set extern sync failed.\n");
        (void)mpu6050_deinit(&gs_handle);

        return 1;
    }

    /* set the default fsync interrupt */
    res = mpu6050_set_fsync_interrupt(&gs_handle, ACCEL_SELECTED__FSYNC_INTERRUPT);
    if (res != 0)
    {
        mpu6050_interface_debug_print("mpu6050: set fsync interrupt failed.\n");
        (void)mpu6050_deinit(&gs_handle);

        return 1;
    }

    /* set the default fsync interrupt level */
    res = mpu6050_set_fsync_interrupt_level(&gs_handle, ACCEL_SELECTED__FSYNC_INTERRUPT_LEVEL);
    if (res != 0)
    {
        mpu6050_interface_debug_print("mpu6050: set fsync interrupt level failed.\n");
        (void)mpu6050_deinit(&gs_handle);

        return 1;
    }

    /* set the default iic master */
    res = mpu6050_set_iic_master(&gs_handle, ACCEL_SELECTED__IIC_MASTER);
    if (res != 0)
    {
        mpu6050_interface_debug_print("mpu6050: set iic master failed.\n");
        (void)mpu6050_deinit(&gs_handle);

        return 1;
    }

    /* set the default iic bypass */
    res = mpu6050_set_iic_bypass(&gs_handle, ACCEL_SELECTED__IIC_BYPASS);
    if (res != 0)
    {
        mpu6050_interface_debug_print("mpu6050: set iic bypass failed.\n");
        (void)mpu6050_deinit(&gs_handle);

        return 1;
    }

    /* set the default accelerometer range */
    res = mpu6050_set_accelerometer_range(&gs_handle, ACCEL_SELECTED__ACCELEROMETER_RANGE);
    if (res != 0)
    {
        mpu6050_interface_debug_print("mpu6050: set accelerometer range failed.\n");
        (void)mpu6050_deinit(&gs_handle);

        return 1;
    }

    /* set the default gyroscope range */
    res = mpu6050_set_gyroscope_range(&gs_handle, ACCEL_SELECTED__GYROSCOPE_RANGE);
    if (res != 0)
    {
        mpu6050_interface_debug_print("mpu6050: set gyroscope range failed.\n");
        (void)mpu6050_deinit(&gs_handle);

        return 1;
    }

    return 0;
}
