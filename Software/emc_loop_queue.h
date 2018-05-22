#ifndef __EMC_LOOP_QUEUE_H__
#define __EMC_LOOP_QUEUE_H__

#include "usart.h"

#define QUEUE_LENGTH 3
#define EMC_BUFF_LENGTH 1040
#define QUEUE_TIME_OUT 20

typedef struct loop_queue{
    uint8_t front;
    uint8_t rear;
    uint16_t cnt;
    
    uint16_t timer_cnt;
    uint16_t buff_cnt; 
    uint8_t *emc_buff; 
}LOOP_QUEUE;

extern LOOP_QUEUE emc_lq;

extern void emc_queue_init(void);
extern uint8_t *emc_queue_read(void);
extern void emc_irq(void);

#endif //__EMC_LOOP_QUEUE_H__

