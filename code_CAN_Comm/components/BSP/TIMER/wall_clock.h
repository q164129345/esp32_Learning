#ifndef _WALL_CLOCK_H_
#define _WALL_CLOCK_H_

#include "stdbool.h"
#include "stdio.h"
#include "string.h"
#include "driver/gptimer.h"


void init_Wall_Clock_Timer(void);
gptimer_handle_t* get_Wall_Clock_Handler(void);



#endif

