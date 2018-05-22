#include "system.h"
#include "ledtask.h"
#include "led_function.h"

#define LED_TASK_INTERVAL               10      //单位ms
#define LED_SYSTEM_RUNING_INTERVAL      500     //单位ms

#define TICK_TO_WAIT                    0       //单位ms

void led_poll( led_type_t led_type, led_parameter_t led_parameter )
{
    switch( led_parameter.status )
    {
	case LED_OFF:
        led_off( led_type );
	break;
	case LED_ON:
        led_on( led_type );
	break;
	case LED_FLASH:
        led_flash( led_type,  led_parameter.flash_interval, LED_TASK_INTERVAL );
	break;
	default:
	break;
    }
}

void led_task(void *pvParameters)
{
    BaseType_t xQueueReceiveStatus = pdPASS;
    led_parameter_t led_system_runing_parameter;
    led_parameter_t led_usb_attached_parameter;

    led_parameter_init( &led_system_runing_parameter );
    led_parameter_init( &led_usb_attached_parameter ); 

    xQueueReceiveStatus = xQueueReceiveStatus;

    led_system_runing_parameter.status = LED_FLASH;
    led_system_runing_parameter.flash_interval = LED_SYSTEM_RUNING_INTERVAL;

    while(1)
    {
        xQueueReceiveStatus = xQueueReceive( led_system_runing_msg_queue, &led_system_runing_parameter,  pdMS_TO_TICKS(TICK_TO_WAIT) );
        led_poll( SYSTEM_RUNING, led_system_runing_parameter );

        xQueueReceiveStatus = xQueueReceive( led_usb_attached_msg_queue, &led_usb_attached_parameter,  pdMS_TO_TICKS(TICK_TO_WAIT) );
        led_poll( USB_ATTACHED, led_usb_attached_parameter );

        vTaskDelay( pdMS_TO_TICKS( LED_TASK_INTERVAL ) );
    }
}
