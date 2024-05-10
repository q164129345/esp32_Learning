#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"
#include "driver/gpio.h"
#include "led.h"
#include "simple_timer.h"
#include "general_purpose_timer.h"
#include "wall_clock.h"

/**
 * @brief 主函数
 * 
 */
void app_main(void)
{
    static uint32_t cnt = 0;
    static bool start = 0;
    led_Init();    // 初始化LED
    // timer_Init();  // 初始化定时器
    // timer_Start(); // 启动定时器
    //init_And_Start_GPtimer1(); // 初始化并启动gptimer1
    init_Wall_Clock_Timer();
    while(1) {
        esp_log_write(ESP_LOG_INFO,"MAIN","%s(%d): Gptimer1 CNT:%lld\n",__FUNCTION__, __LINE__, get_Gptimer_CNT());
        led_Toggle();

        /* 大概在3S之后启动挂钟 */
        if (6 == cnt) {
            ESP_ERROR_CHECK(gptimer_start(*get_Wall_Clock_Handler())); // 启动挂钟
            start = true;
        }

        /* 启动挂钟之后,打印挂钟的时间 */
        if (true == start) {
            uint64_t cnt;
            gptimer_get_raw_count(*get_Wall_Clock_Handler(), &cnt); // 获取当前挂钟的时间
            esp_log_write(ESP_LOG_INFO,"MAIN","%s(%d): wall clock:%lldus\n",__FUNCTION__, __LINE__, cnt); // 打印出来
        }

        cnt++;
        vTaskDelay(500 / portTICK_PERIOD_MS);    
    }
}
