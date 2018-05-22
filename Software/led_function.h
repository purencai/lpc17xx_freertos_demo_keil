#ifndef __LED_FUNCTION_H__
#define __LED_FUNCTION_H__

#include "system.h"
#include "led.h"

// led的状态
typedef enum _led_status_t
{
    LED_OFF = 0,
    LED_ON,
    LED_FLASH,
}led_status_t;

// led的参数
typedef struct _led_parameter_t
{
    led_status_t status;
    uint16_t flash_interval;
}led_parameter_t;

extern void led_off( led_type_t led_type );
extern void led_on( led_type_t led_type );
extern void led_flash( led_type_t led_type, uint16_t flash_interval, uint16_t sys_interval );
extern void led_parameter_init( led_parameter_t* led_parameter);
extern BaseType_t set_led_status( led_type_t led_type, led_status_t led_status, uint16_t flash_interval );

#endif //__LED_FUNCTION_H__
