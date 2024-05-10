#include "can_comm.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/twai.h"
#include "driver/gpio.h"
#include "esp_log.h"

#define CAN_RX_PIN    GPIO_NUM_17 // RX引脚
#define CAN_TX_PIN    GPIO_NUM_16 // TX引脚

/**
 * @brief 初始化CAN控制器
 * 
 */
void can_Comm_Init(void) {

    /* 配置CAN控制器*/
    twai_general_config_t g_config = TWAI_GENERAL_CONFIG_DEFAULT(CAN_TX_PIN, CAN_RX_PIN, TWAI_MODE_NORMAL);
    twai_timing_config_t timeConfig = TWAI_TIMING_CONFIG_500KBITS();        // CAN通讯波特率500K
    twai_filter_config_t filterConfig = TWAI_FILTER_CONFIG_ACCEPT_ALL();    // 接收所有CAN报文
    ESP_ERROR_CHECK(twai_driver_install(&g_config, &timeConfig, &filterConfig)); // 安装CAN驱动
    ESP_ERROR_CHECK(twai_start()); // 启动CAN驱动
}

void CAN_Receive_Msg_And_Send_Msg(void) {
    twai_message_t recMsg;
    twai_message_t sendMsg;
    /* 接收到CAN报文时，将CAN报文发送回去 */
    if (ESP_OK == twai_receive(&recMsg,0U)) {
        memcpy(&sendMsg, &recMsg, sizeof(twai_message_t));
        esp_log_write(ESP_LOG_INFO,"CAN","%s(%d): Get CAN message.\n",__FUNCTION__, __LINE__);
        twai_transmit(&sendMsg, pdMS_TO_TICKS(10)); // 发送CAN报文
    }
}




/**
 * @brief 测试发送功能
 * 
 */
void test_SendMsg(void) {
    twai_message_t canMsg = {
        .identifier = 0x123,       // CANID
        .extd = 0,                 // 标准帧  
        .data_length_code = 8,     // 数据长度
        .data = {0,1,2,3,4,5,6,7}, // 数据
    };

    if(ESP_OK == twai_transmit(&canMsg, pdMS_TO_TICKS(1000))) {
       esp_log_write(ESP_LOG_INFO,"MAIN","%s(%d): CAN message sand\n",__FUNCTION__, __LINE__); 
    } 
}




















