#include <stdio.h>
#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "esp_now.h"
#include "esp_wifi.h"
#include "esp_event.h"
#include "nvs_flash.h"
#include "esp_log.h"
#include "esp_netif.h"

/**
 * @brief 接收回调函数
 * 
 * @param mac_addr 
 * @param data 
 * @param len 
 */
void receive_Callback(const unsigned char* mac_addr, const unsigned char* data, int len) {
    char message[len + 1]; // 定义接收缓冲区
    memcpy(message, data, len); // 复制消息到缓冲区
    message[len] = '\0'; // 添加字符串结束符
    ESP_LOGI("ESP_NOW", "Received message: %s", message); // 打印接收到的消息
}

/**
 * @brief 初始化esp_now
 * 
 */
static void receive_esp_now_Init(void) {
    ESP_ERROR_CHECK(esp_now_init()); // 初始化ESP_NOW
    ESP_ERROR_CHECK(esp_now_register_recv_cb(receive_Callback)); // 注册接收回调函数
}

/**
 * @brief 接收端的main初始化
 * 
 */
void receiver_Main_Init(void) {
    ESP_ERROR_CHECK(nvs_flash_init()); // 初始化NVS
    ESP_ERROR_CHECK(esp_netif_init()); // 初始化网络接口
    ESP_ERROR_CHECK(esp_event_loop_create_default()); // 创建默认事件循环

    wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT(); // 定义WIFI初始化配置
    ESP_ERROR_CHECK(esp_wifi_init(&cfg)); // 初始化WIFI
    ESP_ERROR_CHECK(esp_wifi_set_mode(WIFI_MODE_STA)); // WIFI模式是STA
    ESP_ERROR_CHECK(esp_wifi_start()); // 启动WIFI

    receive_esp_now_Init(); // 初始化ESP_NOW
}













