#include "uart_echo.h"
#include "driver/uart.h"
#include "driver/gpio.h"

#define ECHO_UART_PORT_NUM      UART_NUM_1     // uart1
#define ECHO_UART_BAUD_RATE     115200         // 波特率
#define ECHO_UART_TX_PIN        GPIO_NUM_17    // TX引脚
#define ECHO_UART_RX_PIN        GPIO_NUM_16    // RX引脚
#define BUF_SIZE                256            // FIFO尺寸

volatile uint8_t rxBuffer[BUF_SIZE] = {0,};    // 接收信息的缓存（相当于Rx_FIFO的大小）

/**
 * @brief 初始化串口1
 * 
 */
void setup_Uart1(void) {
    // 配置UART参数
    uart_config_t config = {
        .baud_rate  = ECHO_UART_BAUD_RATE,       // 波特率
        .data_bits  = UART_DATA_8_BITS,          // 8位
        .parity     = UART_PARITY_DISABLE,       // 无奇偶校验
        .stop_bits  = UART_STOP_BITS_1,          // 1位停止位
        .flow_ctrl  = UART_HW_FLOWCTRL_DISABLE,  // 无硬件流控制
        .source_clk = UART_SCLK_APB,             // 时钟源APB
    };
    ESP_ERROR_CHECK(uart_param_config(ECHO_UART_PORT_NUM, &config)); // 应用以上配置
    ESP_ERROR_CHECK(uart_set_pin(ECHO_UART_PORT_NUM, ECHO_UART_TX_PIN, ECHO_UART_RX_PIN, UART_PIN_NO_CHANGE, UART_PIN_NO_CHANGE)); // 设置UART引脚
    ESP_ERROR_CHECK(uart_driver_install(ECHO_UART_PORT_NUM, BUF_SIZE, BUF_SIZE, 0, NULL, 0)); // 安装UART驱动，配置FIFO的大小，消息队列
}

/**
 * @brief 测试发送数据
 * 
 */
void test_Send(void) {
    uint8_t data[8] = {0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08};
    uint8_t dataLen = 8;
    uart_write_bytes(ECHO_UART_PORT_NUM, data, dataLen);
}

/**
 * @brief 测试接收与串行发送（有可能会阻塞）
 * 
 */
void test_Receive_and_Send_Block(void) {
    uint32_t dataLen = 0;
    ESP_ERROR_CHECK(uart_get_buffered_data_len(ECHO_UART_PORT_NUM, (size_t*)&dataLen)); // 看看rxFIFO有没有数据
    if (dataLen > 0) {
        uart_read_bytes(ECHO_UART_PORT_NUM, (uint8_t*)rxBuffer, dataLen, 100U); // 从rxFIFO读取数据
        /* 当Tx_FIFO满了，uart_write_bytes会阻塞程序，等待Tx_FIFO有足够的空间 */
        uart_write_bytes(ECHO_UART_PORT_NUM, (uint8_t*)rxBuffer, dataLen);      // 将rxFIFO读取的数据，发送出去
    }
}















