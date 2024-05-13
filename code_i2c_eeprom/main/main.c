#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"
#include "driver/gpio.h"
#include "led.h"
#include "esp_timer.h"
#include "xl9555.h"

static esp_timer_handle_t timer1; // 定时器句柄
static uint8_t keyStatus = 0;
static i2c_obj_t i2c0_master;

static void timer1_Callback(void); // 定时器1回调函数

/**
 * @brief 主函数
 * 
 */
void app_main(void)
{
    /* 定时器1参数*/
    const esp_timer_create_args_t timer1_Args = {
        .callback = timer1_Callback, // 指定定时器回调函数
        .arg      = NULL,
        .name     = "timer1",
    };
    led_Init();    // 初始化LED
    i2c0_master = iic_init(I2C_NUM_0); // 初始化I2C0
    xl9555_init(i2c0_master); // 初始化xl9555
    esp_log_write(ESP_LOG_INFO,"MAIN","%s(%d): system tick:%ldHz\n",__FUNCTION__, __LINE__, 1000U / portTICK_PERIOD_MS);
    ESP_ERROR_CHECK(esp_timer_create(&timer1_Args, &timer1)); // 创建定时器1
    ESP_ERROR_CHECK(esp_timer_start_periodic(timer1,10));     // 启动定时器1，周期10ms
    while(1) {
        esp_log_write(ESP_LOG_INFO,"MAIN","%s(%d): i2c example eeprom,keyStatus:%d\n",__FUNCTION__, __LINE__, keyStatus);
        led_Toggle();
        vTaskDelay(500 / portTICK_PERIOD_MS);    
    }
}

/**
 * @brief Construct a new timer1 Callback object
 * 
 */
static void timer1_Callback(void) {
    keyStatus = xl9555_key_scan(1U); // 连续扫描
}