#include "message_manager.h"
#include "emc_loop_queue.h"
#include "led_function.h"

system_msg_t system_msg = {NULL};
usb_host_port_t usb_host_port = UNATTACHED;

SemaphoreHandle_t emc_semaphore = NULL;
__forceinline static void create_emc_semaphore(void)
{
    emc_semaphore = xSemaphoreCreateCounting( QUEUE_LENGTH, 0 );
    if( emc_semaphore == NULL )
    {
        LOG("create emc_semaphore fail\r\n");
    }
}

QueueHandle_t led_system_runing_msg_queue = NULL;
__forceinline static void create_led_system_runing_msg_queue(void)
{
    led_system_runing_msg_queue = xQueueCreate( 5, sizeof( led_parameter_t ) ); 
    if( led_system_runing_msg_queue == NULL )
    {
        LOG("create led_system_runing_msg_queue fail\r\n");
    }
}

QueueHandle_t led_usb_attached_msg_queue = NULL;
__forceinline static void create_led_usb_attached_msg_queue(void)
{
    led_usb_attached_msg_queue = xQueueCreate( 5, sizeof( led_parameter_t ) ); 
    if( led_usb_attached_msg_queue == NULL )
    {
        LOG("create led_usb_attached_msg_queue fail\r\n");
    }
}

QueueHandle_t usb_port_status_msg_queue = NULL;
__forceinline static void create_usb_port_status_msg_queue(void)
{
    usb_port_status_msg_queue = xQueueCreate( 5, sizeof( usb_host_port_t ) ); 
    if( usb_port_status_msg_queue == NULL )
    {
        LOG("create usb_port_status_msg_queue fail\r\n");
    }
}

void create_queue_semaphore(void)
{
    create_emc_semaphore();
    create_led_system_runing_msg_queue();
    create_led_usb_attached_msg_queue();
    // create_usb_port_status_msg_queue();
}
