#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"
#include "driver/gpio.h"
#include "esp_system.h"  // ESP系统相关功能头文件
#include "esp_now.h"     // ESP-NOW通信协议头文件
#include "esp_wifi.h"    // ESP Wi-Fi功能头文件
#include "esp_event.h"   // ESP事件循环库头文件
#include "nvs_flash.h"   // 非易失性存储（NVS）库头文件
#include "esp_netif.h"   // ESP网络接口库头文件
#include "led.h"
#include "sender.h"
#include "receiver.h"
#include "broadcast_sender.h"
#include "broadcast_receiver.h"

/**
 * @brief 主函数
 * 
 */
void app_main(void)
{
    led_Init(); // 初始化LED
    while(1) {
        esp_log_write(ESP_LOG_INFO,"MAIN","%s(%d): mirco-ros\n",__FUNCTION__, __LINE__);
        led_Toggle();
        vTaskDelay(300 / portTICK_PERIOD_MS);    
    }
}