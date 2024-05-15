#include "simple_timer.h"
#include "esp_log.h"
#include "esp_timer.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

static esp_timer_handle_t timer; // 定时器句柄

/**
 * @brief 定时器回调函数
 * 
 * @param arg 
 */
static void timer_Callback(void* arg) {
    esp_log_write(ESP_LOG_INFO, "ESP_TIMER","%s(%d):Timer ticked time since boot:%lld us \n",__FUNCTION__, __LINE__, esp_timer_get_time());
}

/**
 * @brief 定时器初始化
 * 
 */
void timer_Init(void) {
    /* 配置定时器参数*/
    const esp_timer_create_args_t timer_Args = {
        .callback = timer_Callback, // 指定定时器回调函数
        .arg = NULL,                // 传递参数，不需要
        .name = "timer1"            // 定时器名称
    };
    ESP_ERROR_CHECK(esp_timer_create(&timer_Args, &timer)); // 创建定时器
}

/**
 * @brief 启动定时器
 * 
 */
void timer_Start(void) {
    ESP_ERROR_CHECK(esp_timer_start_periodic(timer, 500000)); // 启动定时器，周期500ms
    //ESP_ERROR_CHECK(esp_timer_start_once(timer,1000000)); // 启动一次定时器，超时时间1S后
}






































