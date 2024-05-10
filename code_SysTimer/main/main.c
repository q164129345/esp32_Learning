#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"
#include "driver/gpio.h"
#include "led.h"
#include "simple_timer.h"
#include "general_purpose_timer.h"

/**
 * @brief 主函数
 * 
 */
void app_main(void)
{
    led_Init();    // 初始化LED
    // timer_Init();  // 初始化定时器
    // timer_Start(); // 启动定时器
    init_And_Start_GPtimer1(); // 初始化并启动gptimer1

    while(1) {
        esp_log_write(ESP_LOG_INFO,"MAIN","%s(%d): Gptimer1 CNT:%lld\n",__FUNCTION__, __LINE__, get_Gptimer_CNT());
        led_Toggle();
        vTaskDelay(500 / portTICK_PERIOD_MS);    
    }
}
