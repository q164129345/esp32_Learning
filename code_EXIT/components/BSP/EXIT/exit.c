#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <inttypes.h>
#include "exit.h"
#include "driver/gpio.h"
#include "driver/gpio_filter.h"
#include "esp_log.h"
#include "esp_attr.h"

#define EXIT_PIN_NUM GPIO_NUM_0 // 开发板上IO0与Boot按钮

/**
 * @brief EXIT外部中断函数
 * 
 * @param arg 
 */
static IRAM_ATTR void exit_GPIO_ISR_Handler(void *arg) {
    esp_log_write(ESP_LOG_INFO,"EXIT","%s(%d):Pin Level:%d\n",__FUNCTION__, __LINE__, gpio_get_level(EXIT_PIN_NUM));
}

/**
 * @brief 配置毛刺过滤器，提高GPIO口的抗干扰能力
 * 
 */
static void setup_GPIO_Glitch_Filter(void) {
    // 配置 GPIO 毛刺过滤器
    gpio_pin_glitch_filter_config_t config = {
        .gpio_num = EXIT_PIN_NUM  // 选择GPIO0
    };
    // 毛刺过滤器句柄
    gpio_glitch_filter_handle_t filter_handle;
    // 创建毛刺过滤器句柄
    esp_err_t ret = gpio_new_pin_glitch_filter(&config, &filter_handle);
    if (ret != ESP_OK) {
        // 错误处理
        esp_log_write(ESP_LOG_INFO,"EXIT","%s(%d):Failed to create glitch filter:%d\n",__FUNCTION__, __LINE__, ret);
        return;
    }
    // 启用毛刺过滤器
    gpio_glitch_filter_enable(filter_handle);
}

/**
 * @brief 初始化GPIO的外部中断
 * 
 */
void GPIO_Exit_Init(void) {
    setup_GPIO_Glitch_Filter(); // 配置毛刺过滤器，提高GPIO口的抗干扰能力

    // 配置 GPIO 输入模式等其他相关设置
    gpio_config_t io_conf = {0,};
    io_conf.intr_type = GPIO_INTR_ANYEDGE;           // 上升沿 + 下降沿触发
    io_conf.pin_bit_mask = (1ULL << EXIT_PIN_NUM);   // 配置IO口
    io_conf.mode = GPIO_MODE_INPUT;
    io_conf.pull_up_en = 1;  // 启用内部上拉电阻
    gpio_config(&io_conf);

    //配置中断
    gpio_install_isr_service(ESP_INTR_FLAG_EDGE | ESP_INTR_FLAG_IRAM); // 边沿触发
    //gpio_isr_handler_add();

}























