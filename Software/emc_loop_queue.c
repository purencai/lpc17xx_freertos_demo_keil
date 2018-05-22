#include "emc_loop_queue.h"
#include "system.h"

uint8_t emc_queue[QUEUE_LENGTH][EMC_BUFF_LENGTH]={0x00};
LOOP_QUEUE emc_lq;

static __INLINE uint8_t *loop_queue_insert(LOOP_QUEUE *q, uint8_t queue[][EMC_BUFF_LENGTH])
{
    uint8_t *head = NULL;

    if ((q->front + 1) % QUEUE_LENGTH == q->rear)
    {
        return NULL;
    }
    q->front = (q->front + 1) % QUEUE_LENGTH;
    head = &queue[q->front][0];
    q->cnt++;
    return head;
}
static __INLINE uint8_t *loop_queue_read(LOOP_QUEUE *q, uint8_t queue[][EMC_BUFF_LENGTH])
{
    uint8_t *head = NULL;

    if (q->rear == q->front)
    {
        return NULL;
    }
    head = &queue[q->rear][0];
    q->rear = (q->rear + 1) % QUEUE_LENGTH;
    q->cnt--;
    return head;
}
uint8_t *loop_queue_get_front(LOOP_QUEUE *q, uint8_t queue[][EMC_BUFF_LENGTH])
{
    uint8_t *head = NULL;
    head = &queue[q->front][0];
    return head;
}
uint8_t *is_loop_queue_empty(LOOP_QUEUE *q, uint8_t queue[][EMC_BUFF_LENGTH])
{
    if (q->rear == q->front)
    {
        return NULL;
    }
    return &queue[q->rear][0];
}

void loop_queue_init(LOOP_QUEUE *q, uint8_t queue[][EMC_BUFF_LENGTH])
{
    q->front = 0;
    q->rear = 0;
    q->cnt = 0;
    q->timer_cnt = 0;
    q->buff_cnt = 0;
    q->emc_buff = loop_queue_get_front(q, queue);
}

static __INLINE void emc_gpio_irq(LOOP_QUEUE *q, uint8_t queue[][EMC_BUFF_LENGTH])
{
    // if (q->usart_buff == NULL)
    // {
    //     q->timer_cnt = QUEUE_TIME_OUT + 1;
    //     return;
    // }
    // q->usart_buff[q->buff_cnt] = USART_ReceiveData(USARTx);
    // q->buff_cnt++;
    // if (q->buff_cnt == USAER_BUFF_LENGTH)
    // {
    //     q->buff_cnt = USAER_BUFF_LENGTH - 1;
    // }
    // q->timer_cnt = 1;
}

uint8_t *emc_queue_insert(void)
{
    return loop_queue_insert(&emc_lq, emc_queue);
}

uint8_t *emc_queue_read(void)
{
    return loop_queue_read(&emc_lq, emc_queue);
}

void emc_queue_init(void)
{
    loop_queue_init(&emc_lq, emc_queue);
}

void emc_irq(void)
{
    emc_gpio_irq(&emc_lq, emc_queue);
}
