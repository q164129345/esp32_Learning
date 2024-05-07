#include <stdio.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <driver/gpio.h>

#define LED_GPIO_PIN GPIO_NUM_1  // LED连接到IO1
void led_Init(void);
void led_Toggle(void);

/**
 * @brief 主函数
 * 
 */
void app_main(void)
{
    led_Init(); // 初始化GPIO1
    while(1) {
        led_Toggle(); // 翻转LED电平
        vTaskDelay(1000 / portTICK_PERIOD_MS); // 延时1000ms
    }
}

/**
 * @brief 初始化GPIO口
 * 
 */
void led_Init(void)
{
    gpio_config_t gpio_handler = {0,};
    gpio_handler.intr_type = GPIO_INTR_DISABLE;        // 关闭引脚中断
    gpio_handler.mode = GPIO_MODE_INPUT_OUTPUT;        // 输入、输出模式（一定要输入输出模式，否则无法读取pin脚的电平
    gpio_handler.pull_up_en = GPIO_PULLUP_ENABLE;      // 使能上拉
    gpio_handler.pull_down_en = GPIO_PULLDOWN_DISABLE; // 失能下拉
    gpio_handler.pin_bit_mask = 1ULL << LED_GPIO_PIN;  // 设置引脚位掩码
    gpio_config(&gpio_handler);
}

/**
 * @brief 翻转LED的电平
 * 
 */
void led_Toggle(void)
{
    if (false == gpio_get_level(LED_GPIO_PIN)) {
        gpio_set_level(LED_GPIO_PIN,1);
    } else {
        gpio_set_level(LED_GPIO_PIN,0);
    }
}
