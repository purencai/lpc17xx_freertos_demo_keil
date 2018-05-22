#ifndef __USART_H_
#define __USART_H_

#include "chip.h"
#include "system.h"

#define DEBUG_USART  LPC_UART1
#define DEBUG_RX_GPIO_PORT_NUM  0x00
#define DUBUG_RX_GPIO_BIT_NUM   0x10
#define DEBUG_TX_GPIO_PORT_NUM  0x00
#define DUBUG_TX_GPIO_BIT_NUM   0x0f

#define CCU_USART  LPC_UART3
#define CCU_RX_GPIO_PORT_NUM  0x04
#define CCU_RX_GPIO_BIT_NUM   0x1c
#define CCU_TX_GPIO_PORT_NUM  0x04
#define CCU_TX_GPIO_BIT_NUM   0x1d

extern void Debug_Usart_Init(uint32_t BoundRate);
extern void Ccu_Usart_Init(uint32_t BoundRate);
extern void Usart_Putchar( LPC_USART_T* USARTn, char Ch);
extern void Usart_Putstr( LPC_USART_T* USARTn, const char *Fmt, ... );
extern void Usart_Puts( LPC_USART_T* USARTn, const char *Buff, uint16_t Length );

#endif //__USART_H_
