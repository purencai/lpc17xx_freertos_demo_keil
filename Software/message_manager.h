#ifndef __MESSAGE_MANAGER_H__
#define __MESSAGE_MANAGER_H__

#include "system.h"

typedef enum _usb_host_port_t
{
    UNATTACHED = 0,
    ATTACHED,
}usb_host_port_t;

typedef enum _type_msg_t
{
    idel = 0,
    download,
}type_msg_t;

typedef union _data_msg_t
{
    uint8_t percent;
}data_msg_t;

typedef struct _system_msg_t
{
    type_msg_t type;
    data_msg_t data;
}system_msg_t;

extern system_msg_t system_msg;
extern usb_host_port_t usb_host_port;

extern SemaphoreHandle_t emc_semaphore;
extern QueueHandle_t led_system_runing_msg_queue;
extern QueueHandle_t led_usb_attached_msg_queue;
extern QueueHandle_t usb_port_status_msg_queue;

extern void create_queue_semaphore(void);

#endif //__MESSAGE_MANAGER_H__
