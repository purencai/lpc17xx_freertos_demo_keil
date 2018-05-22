#ifndef __USBHOST_H_
#define __USBHOST_H_

#include "chip.h"
#include "system.h" 

#define EXPAND_BOARD_POWER_ENABLE_GPIO_PORT_NUM                      0
#define EXPAND_BOARD_POWER_ENABLE_GPIO_BIT_NUM                       21

extern void Usb_Init(void);

#endif //__USBHOST_H_
