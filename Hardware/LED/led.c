#include "led.h" 

void Led_Init(void)
{
	/* Initializes GPIO */
	Chip_GPIO_Init( LPC_GPIO );
    /* Initializes IOCON */
	Chip_IOCON_Init( LPC_IOCON );
    
	/* Initialize LEDs */
	/* Pin PIO0_22 is configured as GPIO pin during SystemInit */
	/* Set the PIO_22 as output */
    Chip_IOCON_PinMuxSet(LPC_IOCON, LED0_GPIO_PORT_NUM, LED0_GPIO_BIT_NUM, ( IOCON_MODE_INACT | IOCON_FUNC0 ) );
    Chip_IOCON_PinMuxSet(LPC_IOCON, LED1_GPIO_PORT_NUM, LED1_GPIO_BIT_NUM, ( IOCON_MODE_INACT | IOCON_FUNC0 ) );

	Chip_GPIO_WriteDirBit(LPC_GPIO, LED0_GPIO_PORT_NUM, LED0_GPIO_BIT_NUM, true);
	Chip_GPIO_WriteDirBit(LPC_GPIO, LED1_GPIO_PORT_NUM, LED1_GPIO_BIT_NUM, true);
}

void set_led_value(led_type_t led_type, bool value)
{
	switch( led_type )
	{
	case SYSTEM_RUNING:
		Chip_GPIO_WritePortBit(LPC_GPIO, LED0_GPIO_PORT_NUM, LED0_GPIO_BIT_NUM, value);
	break;
	case USB_ATTACHED:
		Chip_GPIO_WritePortBit(LPC_GPIO, LED1_GPIO_PORT_NUM, LED1_GPIO_BIT_NUM, value);
	break;
	case RESERVERD1:
		Chip_GPIO_WritePortBit(LPC_GPIO, LED2_GPIO_PORT_NUM, LED2_GPIO_BIT_NUM, value);
	break;
	case RESERVERD2:
		Chip_GPIO_WritePortBit(LPC_GPIO, LED3_GPIO_PORT_NUM, LED3_GPIO_BIT_NUM, value);
	break;
	default:
	break;
	}
}
