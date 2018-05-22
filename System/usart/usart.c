#include "usart.h"	

//加入以下代码,支持printf函数,而不需要选择use MicroLIB	  
#pragma import(__use_no_semihosting)             
//标准库需要的支持函数                 
struct __FILE 
{ 
	int handle; 
}; 

FILE __stdout;       
//定义_sys_exit()以避免使用半主机模式    
void _sys_exit(int x) 
{ 
	x = x; 
} 
//定义_sys_exit()以避免使用半主机模式    
void _ttywrch(int ch) 
{ 
	ch = ch; 
} 
//重定义fputc函数 
int fputc(int ch, FILE *f)
{
	Chip_UART_SendByte( DEBUG_USART, (uint8_t) ch );
	while ( ( Chip_UART_ReadLineStatus( DEBUG_USART ) & UART_LSR_THRE ) == 0 ) {};
	return ch;
}

void Debug_Usart_Init(uint32_t BoundRate)
{
    Chip_IOCON_PinMuxSet(LPC_IOCON, DEBUG_RX_GPIO_PORT_NUM, DUBUG_RX_GPIO_BIT_NUM, ( IOCON_MODE_INACT | IOCON_FUNC1 ) );
    Chip_IOCON_PinMuxSet(LPC_IOCON, DEBUG_TX_GPIO_PORT_NUM, DUBUG_TX_GPIO_BIT_NUM, ( IOCON_MODE_INACT | IOCON_FUNC1 ) );
  
	Chip_UART_Init(DEBUG_USART);
	Chip_UART_SetBaud(DEBUG_USART, BoundRate);
	Chip_UART_ConfigData(DEBUG_USART, UART_LCR_WLEN8 | UART_LCR_SBS_1BIT | UART_LCR_PARITY_DIS);

	/* Enable UART Transmit */
	Chip_UART_TXEnable(DEBUG_USART);
	//while ( ( Chip_UART_ReadLineStatus( DEBUG_USART ) & UART_LSR_THRE ) == 0 ) {};
}

void Ccu_Usart_Init(uint32_t BoundRate)
{
    Chip_IOCON_PinMuxSet(LPC_IOCON, CCU_RX_GPIO_PORT_NUM, CCU_RX_GPIO_BIT_NUM, ( IOCON_MODE_INACT | IOCON_FUNC3 ) );
    Chip_IOCON_PinMuxSet(LPC_IOCON, CCU_TX_GPIO_PORT_NUM, CCU_TX_GPIO_BIT_NUM, ( IOCON_MODE_INACT | IOCON_FUNC3 ) );
  
	Chip_UART_Init(CCU_USART);
	Chip_UART_SetBaud(CCU_USART, BoundRate);
	Chip_UART_ConfigData(CCU_USART, UART_LCR_WLEN8 | UART_LCR_SBS_1BIT | UART_LCR_PARITY_DIS);

	/* Enable UART Transmit */
	Chip_UART_TXEnable(CCU_USART);
	// while ( ( Chip_UART_ReadLineStatus( CCU_USART ) & UART_LSR_THRE ) == 0 ) {};
}

void Usart_Putchar( LPC_USART_T* USARTn, char ch )
{
    while ( ( Chip_UART_ReadLineStatus( USARTn ) & UART_LSR_THRE ) == 0 ) {};
	Chip_UART_SendByte( USARTn, (uint8_t) ch );
}

static char Usart_Tx_Buff[1024];
void Usart_Putstr( LPC_USART_T* USARTn, const char *Fmt, ... )
{
	uint16_t i = 0;
    uint16_t j = 0;
	va_list ap;
	va_start(ap, Fmt);
	vsprintf(Usart_Tx_Buff, Fmt, ap);
	va_end(ap);
	i = strlen((const char*)Usart_Tx_Buff);
	for(j=0; j<i; j++)
	{
        Usart_Putchar(USARTn, Usart_Tx_Buff[j]);
	}
}

void Usart_Puts( LPC_USART_T* USARTn, const char *Buff, uint16_t Length )
{
	uint16_t i = 0;
	for( i=0; i<Length; i++ )
	{
        Usart_Putchar( USARTn, Buff[i] );
	}
}

void USART1_IRQHandler(void)
{
	
}
