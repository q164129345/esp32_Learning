#include "broadcast_sender.h"
#include <stdio.h>
#include <string.h>
#include "esp_system.h"
#include "esp_timer.h"
#include "esp_now.h"           // 包含ESP-NOW库
#include "esp_wifi.h"          // 包含WiFi库
#include "esp_event.h"         // 包含事件库
#include "nvs_flash.h"         // 包含非易失性存储库
#include "esp_log.h"           // 包含日志库
#include "freertos/FreeRTOS.h" // 包含FreeRTOS库
#include "freertos/task.h"     // 包含FreeRTOS任务库

static esp_timer_handle_t g_Timer1; // 定时器1句柄

/**
 * @brief 发送回调函数
 * 
 * @param mac_addr 
 * @param status 
 */
static void esp_now_send_cb(const uint8_t* mac_addr, esp_now_send_status_t status) {
    ESP_LOGI("ESP_NOW","Send callback, status:%d", status);
}

/**
 * @brief 定时器1回调函数
 * 
 * @param arg 
 */
static void sender_Timer1_Callback(void* arg) {
    const char *message = "Hello, I am sender!"; // 要发送的消息
    ESP_ERROR_CHECK(esp_now_send(NULL, (const uint8_t *)message, strlen(message))); // 发送消息
}

/**
 * @brief 初始化定时器1
 * 
 */
static void timer_Init(void) {
    const esp_timer_create_args_t timer1_Arges = {
        .callback = sender_Timer1_Callback,
        .arg      = NULL,
        .name     = "timer1"
    };
    ESP_ERROR_CHECK(esp_timer_create(&timer1_Arges, &g_Timer1));  // 创建定时器1
    ESP_ERROR_CHECK(esp_timer_start_periodic(g_Timer1, 1000000)); // 启动定时器1，周期1000ms
}

/**
 * @brief 初始化ESP_NOW，广播发送
 * 
 */
static void esp_now_Init(void) {
    ESP_ERROR_CHECK(esp_now_init());     // 初始化ESP-NOW
    ESP_ERROR_CHECK(esp_now_register_send_cb(esp_now_send_cb)); // 注册发送回调函数

    esp_now_peer_info_t peerInfo = {};   // 创建peerInfo结构体
    peerInfo.channel = 0;                // 使用与发送方相同的信道
    peerInfo.ifidx = ESP_IF_WIFI_STA;    // 使用STA模式
    peerInfo.encrypt = false;            // 不加密
    memset(peerInfo.peer_addr, 0xFF, 6); // 设置广播地址
    ESP_ERROR_CHECK(esp_now_add_peer(&peerInfo)); // 添加广播对等点
}

/**
 * @brief 广播Sender main初始化
 * 
 */
void broadcast_Sender_Main_Init(void) {
    ESP_ERROR_CHECK(nvs_flash_init()); // 初始化NVS
    ESP_ERROR_CHECK(esp_netif_init()); // 初始化网络接口
    ESP_ERROR_CHECK(esp_event_loop_create_default()); // 创建默认事件循环

    wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT(); // 默认WiFi初始化配置
    ESP_ERROR_CHECK(esp_wifi_init(&cfg));                // 初始化WiFi
    ESP_ERROR_CHECK(esp_wifi_set_mode(WIFI_MODE_STA));   // 设置WiFi为STA模式
    ESP_ERROR_CHECK(esp_wifi_start());                   // 启动WiFi

    esp_now_Init(); // 初始化ESP-NOW

    timer_Init(); // 初始化、启动定时器
}


