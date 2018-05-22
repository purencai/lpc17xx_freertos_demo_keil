#include "delay.h"
#include "sys.h"
#include "FreeRTOS.h"
#include "task.h"
#include "stdio.h"

#define  US_TO_SYSTICKS(x)  ( (x) * (SystemCoreClock/1000000) )

void Delay_Init(void)
{
#ifdef configTICK_RATE_HZ
    SysTick->LOAD  = ( SystemCoreClock/configTICK_RATE_HZ ) - 1UL;
#else
    SysTick->LOAD  = (SystemCoreClock) - 1UL;
#endif
    SysTick->CTRL |= ( SysTick_CTRL_CLKSOURCE_Msk | SysTick_CTRL_ENABLE_Msk );
}

void Delay_Us(uint32_t us)
{
    uint32_t ticks = 0;
    uint32_t start_ticks = 0;
    uint32_t now_ticks = 0;
    uint32_t total_ticks = 0;
    BaseType_t RTOS_State = taskSCHEDULER_NOT_STARTED;
    RTOS_State = xTaskGetSchedulerState();
    if ( RTOS_State == taskSCHEDULER_NOT_STARTED )
    {
        
        start_ticks = SysTick->VAL;
        ticks = US_TO_SYSTICKS(us);        
        while(1)
        {
            now_ticks = SysTick->VAL;
            if ( start_ticks >= now_ticks )
            {
                total_ticks += start_ticks - now_ticks;
            }
            else
            {
                total_ticks += SysTick->LOAD - now_ticks + start_ticks;
            }
            start_ticks = now_ticks;
            if (total_ticks >= ticks)break;
        }    
    }
    else
    {
        vTaskSuspendAll();
        start_ticks = SysTick->VAL;
        ticks = US_TO_SYSTICKS(us);        
        while(1)
        {
            now_ticks = SysTick->VAL;
            if ( start_ticks >= now_ticks )
            {
                total_ticks += start_ticks - now_ticks;
            }
            else
            {
                total_ticks += SysTick->LOAD - now_ticks + start_ticks;
            }
            start_ticks = now_ticks;
            if (total_ticks >= ticks)break;
        } 
        xTaskResumeAll();
    }   
}

void Delay_Ms(uint16_t ms)
{
    BaseType_t RTOS_State = taskSCHEDULER_NOT_STARTED;
    RTOS_State = xTaskGetSchedulerState();
    if ( RTOS_State == taskSCHEDULER_NOT_STARTED )
    {
        Delay_Us(ms*1000);
    }
    else
    {
        vTaskDelay(pdMS_TO_TICKS(ms));
    }
}
