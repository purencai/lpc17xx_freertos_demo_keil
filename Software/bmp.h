#ifndef __BMP_H_
#define __BMP_H_

#include "system.h"
#include "integer.h"

//BMP信息头
typedef __packed struct 
{
    DWORD  biSize; 
    LONG   biWidth; 
    LONG   biHeight; 
    WORD   biPlanes; 
    WORD   biBitCount; 
    DWORD  biCompression; 
    DWORD  biSizeImage; 
    LONG   biXPelsPerMeter; 
    LONG   biYPelsPerMeter; 
    DWORD  biClrUsed; 
    DWORD  biClrImportant; 
}BITMAPINFOHEADER;

//BMP头文件
typedef __packed struct
{
    WORD   bfType; 
    DWORD  bfSize; 
    WORD   bfReserved1; 
    WORD   bfReserved2; 
    DWORD  bfOffBits; 
}BITMAPFILEHEADER ;

//彩色表 
typedef __packed struct 
{
    uint8_t Blue;
    uint8_t Green;
    uint8_t Red;
    uint8_t Reserved;
}RGBQUAD ;

typedef BITMAPFILEHEADER bmp_file_header_t;
typedef BITMAPINFOHEADER bmp_info_header_t;

//位图信息头
typedef __packed struct _bmp_header_t
{ 
	bmp_file_header_t file;
	bmp_info_header_t info;
}bmp_header_t; 

#define BMP_WINDOWS         0x4d42

//图象数据压缩的类型
#define BMP_BI_RGB          0
#define BMP_BI_RLE8         1
#define BMP_BI_RLE4         2
#define BMP_BI_BITFIELDS    3
#define BMP_BI_JPEG         4
#define BMP_BI_PNG          5

#define BMP_1_BIT_PIXEL     1
#define BMP_4_BIT_PIXEL     4
#define BMP_8_BIT_PIXEL     8
#define BMP_16_BIT_PIXEL    16
#define BMP_24_BIT_PIXEL    24
#define BMP_32_BIT_PIXEL    32

#endif //__BMP_H_
