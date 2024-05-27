#include "broadcast_receiver.h"
#include <stdio.h>
#include <string.h>
#include "esp_now.h"           // 包含ESP-NOW库
#include "esp_wifi.h"          // 包含WiFi库
#include "esp_event.h"         // 包含事件库
#include "nvs_flash.h"         // 包含非易失性存储库
#include "esp_log.h"           // 包含日志库
#include "freertos/FreeRTOS.h" // 包含FreeRTOS库
#include "freertos/task.h"     // 包含FreeRTOS任务库

static int8_t g_last_rssi = 0; // 用于存储最后一个接收到的数据包的RSSI

/**
 * @brief promiscuous 回调函数
 * 
 * @param buf 数据包缓冲区
 * @param type 数据包类型
 */
void wifi_promiscuous_rx_cb(void *buf, wifi_promiscuous_pkt_type_t type) {
    wifi_promiscuous_pkt_t *pkt = (wifi_promiscuous_pkt_t *)buf;
    g_last_rssi = pkt->rx_ctrl.rssi; // 获取RSSI
}

/**
 * @brief 接收回调函数
 * 
 * @param mac_addr 
 * @param data 
 * @param data_len 
 */
void esp_now_recv_cb(const unsigned char* mac_addr, const unsigned char* data, int data_len, wifi_pkt_rx_ctrl_t *rx_ctrl) {
    char macStr[18] = {0,}; // 用于存储MAC地址的字符串
    snprintf(macStr, sizeof(macStr), "%02X:%02X:%02X:%02X:%02X:%02X", 
             mac_addr[0], mac_addr[1], mac_addr[2], 
             mac_addr[3], mac_addr[4], mac_addr[5]); // 格式化MAC地址
    ESP_LOGI("ESP_NOW", "Received message from: %s", macStr); // 打印发送方的MAC地址
    ESP_LOGI("ESP_NOW", "Message: %.*s", data_len, data); // 打印接收到的消息
    ESP_LOGI("ESP_NOW", "RSSI: %d", rx_ctrl->rssi); // 打印RSSI信号强度
}

/**
 * @brief 广播Receiver main初始化
 * 
 */
void broadcast_Receiver_Main_Init() {
    ESP_ERROR_CHECK(nvs_flash_init()); // 初始化NVS
    ESP_ERROR_CHECK(esp_netif_init()); // 初始化网络接口
    ESP_ERROR_CHECK(esp_event_loop_create_default()); // 创建默认事件循环

    wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT(); // 默认WiFi初始化配置
    ESP_ERROR_CHECK(esp_wifi_init(&cfg)); // 初始化WiFi
    ESP_ERROR_CHECK(esp_wifi_set_mode(WIFI_MODE_STA)); // 设置WiFi为STA模式
    ESP_ERROR_CHECK(esp_wifi_start()); // 启动WiFi

    // 注册promiscuous回调函数以获取RSSI
    // ESP_ERROR_CHECK(esp_wifi_set_promiscuous(true));
    // ESP_ERROR_CHECK(esp_wifi_set_promiscuous_rx_cb(wifi_promiscuous_rx_cb));

    ESP_ERROR_CHECK(esp_now_init()); // 初始化ESP-NOW
    ESP_ERROR_CHECK(esp_now_register_recv_cb(esp_now_recv_cb)); // 注册接收回调函数
}

