#include "usbhost.h" 

void Usb_Init(void)
{ 
    Chip_IOCON_PinMuxSet(LPC_IOCON, EXPAND_BOARD_POWER_ENABLE_GPIO_PORT_NUM, EXPAND_BOARD_POWER_ENABLE_GPIO_BIT_NUM, ( IOCON_MODE_INACT | IOCON_FUNC0 ) );
 
	/* Initialize expand board power enable */
	/* Pin PIO0_21 is configured as GPIO pin during SystemInit */
	/* Set the PIO_21 as output */
	Chip_GPIO_WriteDirBit(LPC_GPIO, EXPAND_BOARD_POWER_ENABLE_GPIO_PORT_NUM, EXPAND_BOARD_POWER_ENABLE_GPIO_BIT_NUM, true);
	Chip_GPIO_WritePortBit(LPC_GPIO, EXPAND_BOARD_POWER_ENABLE_GPIO_PORT_NUM, EXPAND_BOARD_POWER_ENABLE_GPIO_BIT_NUM, true);

    NVIC_SetPriority( USB_IRQn, NVIC_EncodePriority( 0x02, 0, 0 ) );
}
