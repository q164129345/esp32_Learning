#ifndef _UART_ECHO_H_
#define _UART_ECHO_H_

#include "stdbool.h"
#include "stdio.h"
#include "string.h"


void setup_Uart1(void);
void test_Send(void);
void test_Receive_and_Send_Block(void);

#endif

