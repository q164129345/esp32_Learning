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

static uint32_t callback_CNT = 0;

/**
 * @brief EXIT外部中断函数
 * 
 * @param arg 
 */
static IRAM_ATTR void exit_GPIO_ISR_Handler(void *arg) {
    callback_CNT++;
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
    io_conf.intr_type = GPIO_INTR_ANYEDGE;         // 上升沿 + 下降沿触发
    io_conf.pin_bit_mask = (1ULL << EXIT_PIN_NUM); // 配置IO口
    io_conf.mode = GPIO_MODE_INPUT;                // 输入模式
    io_conf.pull_up_en = 1;                        // 启用内部上拉电阻（根据电路设计来）
    gpio_config(&io_conf);                         // 初始化GPIO

    // 启动中断
    gpio_install_isr_service(ESP_INTR_FLAG_EDGE);  // 注册中断服务
    gpio_isr_handler_add(EXIT_PIN_NUM, exit_GPIO_ISR_Handler, (void*) EXIT_PIN_NUM); // 关联中断回调函数与GPIO
}

/**
 * @brief Get the Callback CNT object
 * 
 * @return uint32_t 
 */
uint32_t get_Callback_CNT(void) {
    return callback_CNT;
}





















