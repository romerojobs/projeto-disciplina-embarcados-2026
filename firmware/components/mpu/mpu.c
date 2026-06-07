#include "mpu.h"

void mpu6050_init(void)
{
    i2c_config_t conf = {
        .mode             = I2C_MODE_MASTER,
        .sda_io_num       = I2C_SDA_GPIO,
        .scl_io_num       = I2C_SCL_GPIO,
        .sda_pullup_en    = GPIO_PULLUP_ENABLE,
        .scl_pullup_en    = GPIO_PULLUP_ENABLE,
        .master.clk_speed = I2C_FREQ_HZ,
    };
    i2c_param_config(MPU6050_I2C_PORT, &conf);
    i2c_driver_install(MPU6050_I2C_PORT, I2C_MODE_MASTER, 0, 0, 0);

    /* Acorda o MPU6050: escreve 0x00 em PWR_MGMT_1 (0x6B) */
    uint8_t wake_cmd[] = { 0x6B, 0x00 };
    i2c_master_write_to_device(
        MPU6050_I2C_PORT, MPU6050_ADDR,
        wake_cmd, sizeof(wake_cmd),
        pdMS_TO_TICKS(100)
    );
}

void mpu6050_read(mpu6050_raw_t *data)
{
    uint8_t reg = MPU6050_REG_DATA;
    uint8_t buf[14];

    i2c_master_write_to_device(
        MPU6050_I2C_PORT, MPU6050_ADDR,
        &reg, 1, pdMS_TO_TICKS(1000)
    );
    i2c_master_read_from_device(
        MPU6050_I2C_PORT, MPU6050_ADDR,
        buf, 14, pdMS_TO_TICKS(1000)
    );

    data->ax   = (buf[0]  << 8) | buf[1];
    data->ay   = (buf[2]  << 8) | buf[3];
    data->az   = (buf[4]  << 8) | buf[5];
    data->temp = (buf[6]  << 8) | buf[7];
    data->gx   = (buf[8]  << 8) | buf[9];
    data->gy   = (buf[10] << 8) | buf[11];
    data->gz   = (buf[12] << 8) | buf[13];
}
