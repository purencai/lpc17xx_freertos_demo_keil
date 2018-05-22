#include "emctask.h"
#include "system.h"
#include "file_receive.h"
#include "emc_loop_queue.h"

void emc_task(void *pvParameters)
{
    uint8_t *emc_data = NULL;

    while(1)
    {
        while( xSemaphoreTake( emc_semaphore, portMAX_DELAY ) != pdPASS )
        {
            ERROR("emc_semaphore error\r\n");
        }

        emc_data = emc_queue_read();
        if ( emc_data )
        {
            file_receive( emc_data, write );
            memset(emc_data, 0x00, EMC_BUFF_LENGTH);
        }
        else
        {
            // DEBUG("emc_queue empty\r\n");
        }

        taskYIELD();
    }
}
