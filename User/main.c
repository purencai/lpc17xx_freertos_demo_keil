#include "system.h"
#include "usertask.h" 

#include "usart.h"
#include "delay.h"
#include "led.h"
#include "usbhost.h" 

#include "MassStorageHost.h"
#include "file_operation.h"
#include "file_receive.h"

int main(void)
{
    portENABLE_INTERRUPTS();
    NVIC_SetPriorityGrouping( 0x02 );

    SystemCoreClockUpdate();
    
    Delay_Init();
    Usb_Init();
    Delay_Ms(5);           // 后面板上电时间，否则丢数据
    Debug_Usart_Init(115200);
    Led_Init();
 
    // LOG("USB_IRQn's Priority is %d\r\n",(uint32_t)NVIC_EncodePriority( 0x05, 31, 1 ));
    SetupHardware();
    LOG("\r\nboard init finished\r\n");
    Delay_Ms(100);

    fatfs_init();
    fatfs_test();
    file_test();
    fatfs_uninit();

    // freeRTOS start
    AppTaskCreate();
    vTaskStartScheduler();

    while(1)
    {
    }
}
