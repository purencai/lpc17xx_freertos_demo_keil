#include "bmp.h"
#include "file_operation.h"
#include "file_receive.h"

//!接收缓存文件
const TCHAR* const RECEIVE_FILE = "0:/receive.tmp";

//!存储的目的文件夹
const TCHAR* const DESTINATION_FILE = "sonoscape";
//!存储的目的文件夹
const TCHAR* const DESTINATION_DIR = "0:/sonoscape";

/**
@brief  获得固定格式文件名
@author purc
@date   2018/5-2018/5
@param  void
@retval void  
*/
static void get_free_name_for_bmp( uint8_t *name )
{ 
    FRESULT res = FR_OK;     /* API result code */					 
	uint16_t index = 0;
	uint8_t *format = NULL;
	uint8_t *recevie_dir= {NULL};

	recevie_dir = (uint8_t *)malloc(30);
	if( NULL != recevie_dir)
	{
		while( index < 0XFFFF )
		{
            strcat((char *)recevie_dir , DESTINATION_DIR);
			format = (uint8_t *)strcat( (char *)recevie_dir, "/%05d.bmp" );
			sprintf( (char *)name, (const char *)format, index );
            LOG("%s\r\n", name);
			res = fatfs_open( (const TCHAR *)name, FA_READ );
            LOG( "file open-%d\r\n", res );
			if(res == FR_NO_FILE)
			{
                free(recevie_dir);
                *recevie_dir = NULL;
				break;
			}
			index++;
            
            memset(recevie_dir , NULL, strlen((const char *)recevie_dir) );
		}
	}
    free(recevie_dir);
    *recevie_dir = NULL;
}

/**
@brief  文件开始帧处理
@author purc
@date   2018/5-2018/5
@param  void
@retval void
*/
static void file_start(void)
{
	UINT bw = 0;								/* File read/write count */    
	FRESULT res = FR_OK;						/* API result code */	
	uint16_t bmp_header_size;					// bmp信息头头大小	   	
	bmp_header_t bmp_header;			    	// bmp头

	bmp_header_size = sizeof(bmp_header_t);               		// 得到bmp头的大小   
	memset((uint8_t *)&bmp_header, 0, sizeof(bmp_header_t));	// 置零空申请到的内存.

	bmp_header.info.biSize = sizeof( bmp_info_header_t );		// 信息头大小
	bmp_header.info.biWidth = BMP_WIDTH;						// bmp的宽度
	bmp_header.info.biHeight = BMP_HEIGHT;						// bmp的高度
	bmp_header.info.biPlanes = 1;								// 恒为1
	bmp_header.info.biBitCount = BMP_24_BIT_PIXEL;				// bmp为24位色bmp
	bmp_header.info.biCompression = BMP_BI_RGB;					// 每个象素的比特由指定的掩码决定。
	bmp_header.info.biSizeImage = ( bmp_header.info.biHeight * bmp_header.info.biWidth * bmp_header.info.biBitCount ) / 8; // bmp数据区大小
			
	bmp_header.file.bfType = BMP_WINDOWS;											// BM格式标志
	bmp_header.file.bfSize = bmp_header_size + bmp_header.info.biSizeImage;         // 整个bmp的大小
	bmp_header.file.bfOffBits = bmp_header_size;									// 到数据区的偏移

	res = fatfs_open( RECEIVE_FILE, ( FA_WRITE | FA_CREATE_ALWAYS ) );
	if ( res )
	{
		ERROR( "file open error-%d\r\n", res );
		return;
	}
    
	//taskENTER_CRITICAL();    
	res = fatfs_write( (uint8_t *)&bmp_header, bmp_header_size, &bw );
	//taskEXIT_CRITICAL();
	if ( res )
	{
		ERROR( "file write error-%d\r\n", res );
		return;
	}
}

/**
@brief  文件数据帧处理
@author purc
@date   2018/5-2018/5
@param  bmp_data 数据帧指针
@retval void  
*/
static void file_data(uint8_t* bmp_data)
{
	UINT bw = 0;								/* File read/write count */    
	FRESULT res = FR_OK;						/* API result code */

	//taskENTER_CRITICAL();    
	res = fatfs_write( bmp_data, 1024, &bw );
	//taskEXIT_CRITICAL();
	if ( res )
	{
		ERROR( "file write error-%d\r\n", res );
		return;
	}
	if( bw != 1024 )
	{
		ERROR( "file write error-%d\r\n", bw );
		return;
	}
}

/**
@brief  文件结束帧处理
@author purc
@date   2018/5-2018/5
@param  void
@retval void  
*/
static void file_end(void)
{
	FRESULT res = FR_OK;						/* API result code */
    uint8_t *name = NULL;
    
	printf( "file size:%lu\r\n", fatfs_size() );     

	res = fatfs_close();
	if ( res )
	{
		ERROR( "file close error-%d\r\n", res );
		return;
	}

	// 是否发现目标文件夹
	if( !is_find_file( "0:", DESTINATION_FILE ) )
	{
		res = fatfs_mkdir( DESTINATION_FILE );
		if ( res )
		{
			LOG( "file mkdir error-%d\r\n", res );
			return;
		}
	}
    
    name = (uint8_t *)malloc(30);
    if( name )
    {
        get_free_name_for_bmp( name );
        res = fatfs_rename( RECEIVE_FILE, (const TCHAR *)name );
        if ( res )
        {
            ERROR( "file rename error-%d\r\n", res );
            return;
        }

        fatfs_unlink( RECEIVE_FILE );
        free( name );
        *name = NULL;
    }
    else
    {
        ERROR( "malloc name fail\r\n" );
    }
}

/**
@brief  文件操作
@author purc
@date   2018/5-2018/5
@param  received_data 串口缓存数据 
@param  file_operate 操作命令
@retval void  
*/
void file_receive( uint8_t *received_data, file_operate_t file_operate )
{
	switch( file_operate )
	{
    case open:
        file_start();
    break;
    case write:
        file_data( received_data );
    break;
    case close:
        file_end();
    break;
    default:
    break;
	}
}

/**
@brief  文件操作
@author purc
@date   2018/5-2018/5
@param  received_data 串口缓存数据 
@param  file_operate 操作命令
@retval void  
*/
void file_test( void )
{
    FRESULT res = FR_OK;						/* API result code */
    uint8_t *name = NULL;
    UINT bw;         /* File read/write count */    
    const char *write_line = "this is read/write message.txt.";
    
    res = fatfs_open ( RECEIVE_FILE, ( FA_WRITE|FA_CREATE_ALWAYS ) );
    if ( res )
    {
        LOG("file open error-%d\r\n",res);
        fatfs_close();
        return;
    }
    res = fatfs_write( write_line, strlen(write_line), &bw );
    LOG( "res=%d\r\n", res );
    LOG( "br=%d\r\n", bw );
    res = fatfs_sync();
    LOG( "file size:0x%08x Bytes\r\n", (uint32_t)fatfs_size() );
    /* Close the file */
    fatfs_close();
    LOG( "colse file\r\n" );
    
    // 是否发现目标文件夹
    if( !is_find_file( "0:", DESTINATION_FILE ) )
    {
        res = fatfs_mkdir( DESTINATION_FILE );
        if ( res )
        {
            LOG( "file mkdir error-%d\r\n", res );
            return;
        }
    }
    LOG( "find or create \"0:/sonoscape\"\r\n" );
    
    name = (uint8_t *)malloc(30);
    if( name )
    {
        get_free_name_for_bmp( name );
        res = fatfs_rename( RECEIVE_FILE, (const TCHAR *)name );
        if ( res )
        {
            ERROR( "file rename error-%d\r\n", res );
            return;
        }

        fatfs_unlink( RECEIVE_FILE );
        free( name );
        *name = NULL;
    }
    else
    {
        ERROR( "malloc name fail\r\n" );
    }
}
