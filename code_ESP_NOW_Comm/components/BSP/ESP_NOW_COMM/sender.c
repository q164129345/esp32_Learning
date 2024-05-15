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

static uint8_t peer_mac[6] = {0x24, 0x0A, 0xC4, 0x12, 0x34, 0x56}; // 接收端的MAC地址

/**
 * @brief Construct a new send callback object
 * 
 * @param mac_addr 
 * @param status 
 */
static void send_callback(const uint8_t* mac_addr, esp_now_send_status_t status) {
    ESP_LOGI("ESP_NOW","Send callback, status:%d", status);
}

/**
 * @brief 初始化esp_now
 * 
 */
void esp_now_Init(void) {
    ESP_ERROR_CHECK(esp_now_init()); // 初始化ESP-NOW
    ESP_ERROR_CHECK(esp_now_register_send_cb(send_callback));  // 注册发送回调函数

    esp_now_peer_info_t peer_info = {0,}; // 定义初始化peer结构体
    memcpy(peer_info.peer_addr, peer_mac, 6);
    peer_info.channel = 0; // 设置通信信道0
    peer_info.ifidx = ESP_IF_WIFI_STA; // 设置WIFI接口的STA模式
    peer_info.encrypt = false; // 不加密

    ESP_ERROR_CHECK(esp_now_add_peer(&peer_info)); // 添加peer信息
}

/**
 * @brief 向peer发送esp_now消息
 * 
 * @param message 
 */
void send_Message(const char* message) {
    ESP_ERROR_CHECK(esp_now_send(peer_mac, (uint8_t*)message, strlen(message))); // 发送消息
}

/**
 * @brief sender main初始化
 * 
 */
void sender_Main_Init(void) {
    ESP_ERROR_CHECK(nvs_flash_init()); // 初始化NVS
    ESP_ERROR_CHECK(esp_netif_init()); // 初始化网络接口
    ESP_ERROR_CHECK(esp_event_loop_create_default()); // 创建默认事件循环

    wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT(); // 默认的WIFI配置
    ESP_ERROR_CHECK(esp_wifi_init(&cfg));                // 初始化WIFI
    ESP_ERROR_CHECK(esp_wifi_set_mode(WIFI_MODE_STA));   // 设置WIFI的模式STA
    ESP_ERROR_CHECK(esp_wifi_start()); // 启动WIFI
    esp_now_Init(); // 初始化ESP_NOW

    uint8_t mac[6] = {0,};
    ESP_ERROR_CHECK(esp_wifi_get_mac(ESP_IF_WIFI_STA, mac));
    ESP_LOGI("esp_now", "sender Wi-Fi MAC address: %02x:%02x:%02x:%02x:%02x:%02x", mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);   
}



