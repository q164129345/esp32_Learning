#include <stdio.h>
#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"
#include "driver/gpio.h"
#include "led.h"
#include "uart_echo.h"

/**
 * @brief 主函数
 * 
 */
void app_main(void)
{
    led_Init();    // 初始化LED
    setup_Uart1(); // 初始化UART1
    while(1) {
        esp_log_write(ESP_LOG_INFO,"MAIN","%s(%d): UART Echo\n",__FUNCTION__, __LINE__);
        led_Toggle();
        test_Receive_and_Send_Block();
        vTaskDelay(500 / portTICK_PERIOD_MS);    
    }
}
