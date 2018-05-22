#ifndef __SYSTEM_H__
#define __SYSTEM_H__

#include "FreeRTOS.h"
#include "task.h"
#include "timers.h"
#include "semphr.h"
#include "queue.h"
#include "list.h"

#include "string.h"
#include "stdint.h"
#include "stdlib.h"
#include "stdio.h"
#include "stdarg.h"
#include "math.h"

#include "message_manager.h"

#include "sys.h"
#include "delay.h"

static __inline void assert_failed(uint8_t* file, uint32_t line){
    printf("file:%s-line[%d] param error!\r\n",file,line);while(1);
}

#define ASSERT(expr) ((expr) ? (void )0 : assert_failed(__FILE__,__LINE__))

#endif 
