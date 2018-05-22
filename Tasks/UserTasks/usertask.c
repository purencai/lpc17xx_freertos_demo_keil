#include "system.h"
#include "usertask.h"
#include "uarttask.h"
#include "ledtask.h"
#include "emctask.h"
#include "usbtask.h"

#define LED_TASK_PRIORITY           0
#define USB_TASK_PRIORITY           0
#define USART_TASK_PRIORITY         3
#define EMC_TASK_PRIORITY           4

#define USB_TASK_STACK_DEPTH        512
#define LED_TASK_STACK_DEPTH        512
#define USART_TASK_STACK_DEPTH      512
#define EMC_TASK_STACK_DEPTH        1024

void AppTaskCreate(void)
{
	create_queue_semaphore();
    
	// xTaskCreate( (TaskFunction_t)usart_task,/* Pointer to the function that implements the task. */
    //              "vUsart",                  /* Text name for the task.  This is to facilitate debugging only. */
    //              USART_TASK_STACK_DEPTH,    /* Stack depth in words. */
    //              NULL,                      /* We are not using the task parameter. */
    //              USART_TASK_PRIORITY,       /* This task will run at priority. */
    //              NULL );                    /* We are not using the task handle. */
    
    xTaskCreate( (TaskFunction_t)led_task,  /* Pointer to the function that implements the task. */
                 "led_task",                /* Text name for the task.  This is to facilitate debugging only. */
                 LED_TASK_STACK_DEPTH,      /* Stack depth in words. */
                 NULL,                      /* We are not using the task parameter. */
                 LED_TASK_PRIORITY,         /* This task will run at priority. */
                 NULL );                    /* We are not using the task handle. */
    
    xTaskCreate( (TaskFunction_t)emc_task,  /* Pointer to the function that implements the task. */
                 "emc_task",                /* Text name for the task.  This is to facilitate debugging only. */
                 EMC_TASK_STACK_DEPTH,      /* Stack depth in words. */
                 NULL,                      /* We are not using the task parameter. */
                 EMC_TASK_PRIORITY,         /* This task will run at priority. */
                 NULL );                    /* We are not using the task handle. */
    xTaskCreate( (TaskFunction_t)usb_task,  /* Pointer to the function that implements the task. */
                 "emc_task",                /* Text name for the task.  This is to facilitate debugging only. */
                 USB_TASK_STACK_DEPTH,      /* Stack depth in words. */
                 NULL,                      /* We are not using the task parameter. */
                 USB_TASK_PRIORITY,         /* This task will run at priority. */
                 NULL );                    /* We are not using the task handle. */
}
