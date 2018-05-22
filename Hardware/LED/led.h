#ifndef __LED_H_
#define __LED_H_

#include "chip.h"
#include "system.h" 

// led类型 指示不同的状态
typedef enum _led_type_t
{
    SYSTEM_RUNING = 0,
    USB_ATTACHED,
    RESERVERD1,
    RESERVERD2,
}led_type_t;

#define LED0_GPIO_PORT_NUM                      2
#define LED0_GPIO_BIT_NUM                       12

#define LED1_GPIO_PORT_NUM                      2
#define LED1_GPIO_BIT_NUM                       13

#define LED2_GPIO_PORT_NUM                      2
#define LED2_GPIO_BIT_NUM                       12

#define LED3_GPIO_PORT_NUM                      2
#define LED3_GPIO_BIT_NUM                       12

extern void Led_Init(void);
extern void set_led_value(led_type_t led_type, bool value);

#endif //__LED_H_
