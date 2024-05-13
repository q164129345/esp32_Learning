#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"
#include "driver/gpio.h"
#include "led.h"
#include "can_comm.h"

/**
 * @brief 主函数
 * 
 */
void app_main(void)
{
    led_Init();       // 初始化LED
    can_Comm_Init2(); // 初始化CAN控制器、方案2
    esp_log_write(ESP_LOG_INFO,"MAIN","%s(%d): system tick:%ldHz\n",__FUNCTION__, __LINE__, 1000U / portTICK_PERIOD_MS);
    while(1) {
        esp_log_write(ESP_LOG_INFO,"MAIN","%s(%d): i2c example \n",__FUNCTION__, __LINE__);
        led_Toggle();
        CAN_Receive_Msg_And_Send_Msg();
        vTaskDelay(500 / portTICK_PERIOD_MS);    
    }
}

