#include <stdio.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <esp_log.h>
#include <driver/gpio.h>
#include "led.h"

void app_main(void)
{
    led_Init();
    while(1) {
        esp_log_write(ESP_LOG_INFO,"MAIN","%s(%d):Hello:esp_log.\n",__FUNCTION__,__LINE__);
        led_Toggle();
        vTaskDelay(300 / portTICK_PERIOD_MS);    
    }
}
