#ifndef _LED_H_
#define _LED_H_

#include "stdbool.h"
#include "stdio.h"
#include "string.h"

#define LED_GPIO_PIN GPIO_NUM_1  // LED连接到IO1

void led_Init(void);
void led_Toggle(void);


#endif
