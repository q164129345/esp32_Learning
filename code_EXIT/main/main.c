#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"
#include "driver/gpio.h"
#include "led.h"
#include "exit.h"

void app_main(void)
{
    led_Init();       // 初始化LED
    GPIO_Exit_Init(); // 初始化boot按钮中断
    while(1) {
        esp_log_write(ESP_LOG_INFO,"MAIN","%s(%d): exit callback cnt:%ld \n",__FUNCTION__, __LINE__, get_Callback_CNT());
        led_Toggle();
        vTaskDelay(500 / portTICK_PERIOD_MS);    
    }
}
