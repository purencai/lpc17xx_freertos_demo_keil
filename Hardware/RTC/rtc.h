#ifndef __RTC_H_
#define __RTC_H_

#include "integer.h"

typedef struct {
	WORD	year;	/* 1..4095 */
	BYTE	month;	/* 1..12 */
	BYTE	mday;	/* 1.. 31 */
	BYTE	wday;	/* 1..7 */
	BYTE	hour;	/* 0..23 */
	BYTE	min;	/* 0..59 */
	BYTE	sec;	/* 0..59 */
} RTC;

extern int rtc_initialize (void);		/* Initialize RTC */
extern int rtc_gettime (RTC*);			/* Get time */
extern int rtc_settime (const RTC*);	/* Set time */

#endif //__RTC_H_
