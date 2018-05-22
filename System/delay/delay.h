#ifndef __DELAY_H_
#define __DELAY_H_

#include "sys.h"

extern void Delay_Init(void);
extern void Delay_Us(uint32_t us);
extern void Delay_Ms(uint16_t ms);

#endif //__DELAY_H_
