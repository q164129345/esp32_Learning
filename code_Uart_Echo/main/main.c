#include <stdio.h>
#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"
#include "driver/gpio.h"
#include "led.h"

void app_main(void)
{
    led_Init();       // 初始化LED
    while(1) {
        esp_log_write(ESP_LOG_INFO,"MAIN","%s(%d): UART Echo\n",__FUNCTION__, __LINE__);
        led_Toggle();
        vTaskDelay(500 / portTICK_PERIOD_MS);    
    }
}
