#ifndef _CAN_COMM_H_
#define _CAN_COMM_H_


#include "stdbool.h"
#include "stdio.h"
#include "string.h"

void can_Comm_Init(void);
void can_Comm_Init2(void);
void test_SendMsg(void);
void CAN_Receive_Msg_And_Send_Msg(void);

#endif

