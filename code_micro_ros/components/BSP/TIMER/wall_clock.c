#include "wall_clock.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gptimer.h"
#include "esp_attr.h"
#include "esp_log.h"

static gptimer_handle_t wallClock = NULL; // 句柄

/**
 * @brief 初始化定时器
 * 
 */
void init_Wall_Clock_Timer(void) {
    /* 定时器配置 */
    gptimer_config_t config = {
        .clk_src = GPTIMER_CLK_SRC_DEFAULT, // 默认时钟
        .direction = GPTIMER_COUNT_UP,      // 向上计数
        .resolution_hz = 1 * 1000 *1000,    // 频率1M
    };

    ESP_ERROR_CHECK(gptimer_new_timer(&config, &wallClock)); // 初始化定时器
    ESP_ERROR_CHECK(gptimer_enable(wallClock));              // 使能定时器
    esp_log_write(ESP_LOG_INFO, "ESP_TIMER","%s(%d): wall clock enable.\n",__FUNCTION__, __LINE__);
}

/**
 * @brief 返回定时器的句柄指针
 * 
 * @return gptimer_handle_t* 
 */
gptimer_handle_t* get_Wall_Clock_Handler(void) {
    return &wallClock;
}

































