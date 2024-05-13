#ifndef _I2C_DRIVE_H_
#define _I2C_DRIVE_H_

#include "stdbool.h"
#include "stdio.h"
#include "string.h"
#include "driver/i2c.h"

/* IIC 控制块 */
typedef struct _i2c_obj_t {
    i2c_port_t port;
    gpio_num_t scl;
    gpio_num_t sda;
    esp_err_t init_flag;
} i2c_obj_t;

/* 读写数据结构体 */
typedef struct _i2c_buf_t {
    size_t len;
    uint8_t *buf;
} i2c_buf_t;

extern i2c_obj_t iic_master[I2C_NUM_MAX];

/* 读写标志位 */
#define I2C_FLAG_READ (0x01)           // 读标志
#define I2C_FLAG_STOP (0x02)           // 停止标志
#define I2C_FLAG_WRITE (0x04)          // 写标志

/* 正点原子esp32s3开发板的引脚与相关参数定义 */
#define IIC0_SDA_GPIO_PIN GPIO_NUM_41  // IIC0_SDA 引脚
#define IIC0_SCL_GPIO_PIN GPIO_NUM_42  // IIC0_SCL 引脚
#define IIC1_SDA_GPIO_PIN GPIO_NUM_5   // IIC1_SDA 引脚
#define IIC1_SCL_GPIO_PIN GPIO_NUM_4   // IIC1_SCL 引脚
#define IIC_FREQ 400000                // IIC 通信频率
#define I2C_MASTER_TX_BUF_DISABLE 0    // I2C 主机不需要缓冲区
#define I2C_MASTER_RX_BUF_DISABLE 0    // I2C 主机不需要缓冲区
#define ACK_CHECK_EN 0x1               // I2C master 将从 slave 检查 ACK 







#endif


