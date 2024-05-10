#include <stdio.h>
#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"
#include "driver/gpio.h"
#include "led.h"
#include "simple_timer.h"


/**
 * @brief 主函数
 * 
 */
void app_main(void)
{
    led_Init();    // 初始化LED
    timer_Init();  // 初始化、启动定时器
    while(1) {
        esp_log_write(ESP_LOG_INFO,"MAIN","%s(%d): SysTImer \n",__FUNCTION__, __LINE__);
        led_Toggle();
        vTaskDelay(500 / portTICK_PERIOD_MS);    
    }
}
