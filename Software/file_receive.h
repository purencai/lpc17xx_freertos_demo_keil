#ifndef __FILE_RECEIVE_H__
#define __FILE_RECEIVE_H__

#include "chip.h"
#include "system.h"

#define BMP_WIDTH           1920
#define BMP_HEIGHT          1080

typedef enum _file_operate_t
{
    open = 0,
    write,
    close, 
}file_operate_t;

extern void file_receive( uint8_t *received_data, file_operate_t file_operate );
extern void file_test( void );

#endif //__FILE_RECEIVE_H__
