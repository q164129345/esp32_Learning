#include "general_purpose_timer.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gptimer.h"
#include "esp_attr.h"
#include "esp_log.h"

static gptimer_handle_t gptimer1 = NULL; // 句柄
static uint64_t timer_CNT = 0;

/**
 * @brief 定时器回调函数
 * 
 * @param timer 
 * @param edata 
 * @param user_ctx 
 * @return true 
 * @return false 
 */
static IRAM_ATTR bool gptimer_callback(gptimer_handle_t timer, const gptimer_alarm_event_data_t *edata, void *user_ctx) {
    timer_CNT++;
    return true; // 返回 false 表示不重新加载计数器
}

/**
 * @brief 初始化gptimer1并启动
 * 
 */
void init_And_Start_GPtimer1(void) {
    /* 定时器配置*/
    gptimer_config_t config = {
        .clk_src   = GPTIMER_CLK_SRC_DEFAULT, // 默认时钟源
        .direction = GPTIMER_COUNT_UP,        // 向上计数
        .resolution_hz = 1 * 1000 * 1000      // 计数器频率1MHz
    };
    /* 报警器配置*/
    gptimer_alarm_config_t alarmConfig = {
        .alarm_count = 1 * 1000,              // 计数到1ms,触发报警
        .reload_count = 0,                    // 初始值
        .flags.auto_reload_on_alarm = true,   // 自动重载
    };
    /* 设置定时器回调*/
    gptimer_event_callbacks_t cbs = {
        .on_alarm = gptimer_callback, // 定时器回调函数
    };
    ESP_ERROR_CHECK(gptimer_new_timer(&config, &gptimer1));                  // 初始化通用定时器
    ESP_ERROR_CHECK(gptimer_set_alarm_action(gptimer1, &alarmConfig));       // 初始化报警器
    ESP_ERROR_CHECK(gptimer_register_event_callbacks(gptimer1, &cbs, NULL)); // 初始化回调
    ESP_ERROR_CHECK(gptimer_enable(gptimer1)); // 使能通用定时器
    ESP_ERROR_CHECK(gptimer_start(gptimer1));  // 启动通用定时器
    esp_log_write(ESP_LOG_INFO, "ESP_TIMER","%s(%d): gptimer1 start.\n",__FUNCTION__, __LINE__);
}

/**
 * @brief Get the Gptimer CNT object
 * 
 * @return uint64_t 
 */
uint64_t get_Gptimer_CNT(void) { 
    return timer_CNT;
}




















