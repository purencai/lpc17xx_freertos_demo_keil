#include "usbtask.h"
#include "system.h"
#include "led_function.h"
#include "file_operation.h"

#define USB_TASK_INTERVAL               500     //单位ms

#define TICK_TO_WAIT                    0       //单位ms

void usb_task(void *pvParameters)
{
    while(1)
    {
        // xQueueReceiveStatus = xQueueReceive( usb_port_status_msg_queue, &usb_host_port,  pdMS_TO_TICKS(TICK_TO_WAIT) );
        // switch( usb_host_port )
        // {
        // case UNATTACHED:
        //     set_led_status( USB_ATTACHED, LED_ON, 0 );
        // break;
        // case ATTACHED:
        //     set_led_status( USB_ATTACHED, LED_OFF, 0);
        // break;
        // default:
        // break;
        // }     

        if( usb_host_port == ATTACHED)
        {
            set_led_status( USB_ATTACHED, LED_ON, 0 );
            // fatfs_init();
        }
        else
        {
            set_led_status( USB_ATTACHED, LED_OFF, 0);
            // fatfs_uninit();
        }

        vTaskDelay( pdMS_TO_TICKS( USB_TASK_INTERVAL ) );
    }
}
