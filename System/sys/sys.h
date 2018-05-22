#ifndef __SYS_H_
#define __SYS_H_

#include "chip.h"

extern void WFI_SET(void);
//关闭所有中断(但是不包括fault和NMI中断)
extern void INTX_DISABLE(void);
//开启所有中断
extern void INTX_ENABLE(void);
//设置栈顶地址
//addr:栈顶地址
extern void MSR_MSP(uint32_t addr);

#define __DEBUG__

#ifdef __DEBUG__
    #define DEBUG(format,...) printf("%s:"format"",__func__, ##__VA_ARGS__)
#else
    #define DEBUG(format,...)
#endif

#define LOG(format,...) printf(""format"", ##__VA_ARGS__)

#define ERROR(format,...) printf("ERROR:%s %s %d: "format"",__FILE__, __func__,__LINE__, ##__VA_ARGS__)

#endif //__SYS_H_
