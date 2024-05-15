#ifndef _SENDER_H_
#define _SENDER_H_

#include "stdbool.h"
#include "stdio.h"
#include "string.h"

void esp_now_Init(void);
void send_Message(const char* message);
void sender_Main_Init(void);



#endif


