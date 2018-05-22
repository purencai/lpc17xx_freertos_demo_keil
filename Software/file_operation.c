#include "file_operation.h"
#include "diskio.h"

FATFS *Fatfs = NULL;                //!< Filesystem object 
FIL fil = {NULL};                   //!< File object 
BYTE work0[FF_MAX_SS] = {NULL};     //!< Work area (larger is better for processing time) 

#define FATFS_GETFREE 

/**
@brief  文件系统初始化
@author purc
@date   2018/5-2018/5
@param  void
@retval FR_OK                   Succeeded 
@retval FR_DISK_ERR             A hard error occurred in the low level disk I/O layer
@retval FR_INT_ERR              Assertion failed
@retval FR_NOT_READY            The physical drive cannot work
@retval FR_NO_FILE              Could not find the file
@retval FR_NO_PATH              Could not find the path
@retval FR_INVALID_NAME         The path name format is invalid
@retval FR_DENIED			    Access denied due to prohibited access or directory full
@retval FR_EXIST			    Access denied due to prohibited access
@retval FR_INVALID_OBJECT	    The file/directory object is invalid
@retval FR_WRITE_PROTECTED	    The physical drive is write protected
@retval FR_INVALID_DRIVE	    The logical drive number is invalid
@retval FR_NOT_ENABLED	        The volume has no work area
@retval FR_NO_FILESYSTEM        There is no valid FAT volume
@retval FR_MKFS_ABORTED         The f_mkfs() aborted due to any problem
@retval FR_TIMEOUT              Could not get a grant to access the volume within defined period
@retval FR_LOCKED               The operation is rejected according to the file sharing policy
@retval FR_NOT_ENOUGH_CORE      LFN working buffer could not be allocated
@retval FR_TOO_MANY_OPEN_FILES  Number of open files > FF_FS_LOCK
@retval FR_INVALID_PARAMETER    Given parameter is invalid
@see    FRESULT 
*/
FRESULT fatfs_init(void)
{
    FRESULT res;        /* API result code */  
#ifdef FATFS_GETFREE  
    DWORD fre_clust, fre_sect, tot_sect;    
#endif   
    Fatfs = ( FATFS* )malloc( sizeof( FATFS ) );           /* Get work area for the volume */
    if ( Fatfs )
    {
        LOG("mount Fatfs...\r\n");
        res = f_mount( Fatfs, "0:", 1 );                    /* Mount the default drive */ 
        if (res != RES_OK)
        {
            LOG("file mount error-%d\r\n",res);
            res = f_mkfs( "0:", FM_FAT32, 4096, work0, sizeof(work0) );
            if (res != RES_OK)
            {
                ERROR("mkfs0 return:%d\r\n",res);
                return res;
            }
            res = f_mount(Fatfs, "0:", 1);                    /* Mount the default drive */  
            if (res != RES_OK)
            {
                ERROR("mount0 return:%d\r\n",res);
                return res;
            }           
        } 
        
#ifdef FATFS_GETFREE
        /* Get volume information and free clusters of drive 1 */
        res = f_getfree( "0:", &fre_clust, &Fatfs );
        if ( res != FR_OK )
        {
            ERROR("getfree Fatfs return-%d\r\n",res);
            return res;
        }
        /* Get total sectors and free sectors */
        tot_sect = (Fatfs->n_fatent - 2) * Fatfs->csize;
        fre_sect = fre_clust * Fatfs->csize;

        /* Print the free space (assuming 512 bytes/sector) */
        // LOG("USB0:%lu KB total drive space.\r\n       %lu KB available.\r\n",
        //        tot_sect/2, fre_sect/2 );  
          
        /* Print the free space (assuming 512 bytes/sector) */
        LOG("\r\nUSB0:%4.2f GB total drive space.\r\n     %4.2f GB available.\r\n",
               ((double)tot_sect)/2/1024/1024, ((double)fre_sect)/2/1024/1024 );  
#endif
    }
    else
    {   
        ERROR("malloc Fatfs error!\r\n");
        return FR_NOT_READY;
    }
    return FR_OK;
} 

/**
@brief  文件系统初始化
@author purc
@date   2018/5-2018/5
@param  void
@retval FR_OK                   Succeeded 
@retval FR_DISK_ERR             A hard error occurred in the low level disk I/O layer
@retval FR_INT_ERR              Assertion failed
@retval FR_NOT_READY            The physical drive cannot work
@retval FR_NO_FILE              Could not find the file
@retval FR_NO_PATH              Could not find the path
@retval FR_INVALID_NAME         The path name format is invalid
@retval FR_DENIED			    Access denied due to prohibited access or directory full
@retval FR_EXIST			    Access denied due to prohibited access
@retval FR_INVALID_OBJECT	    The file/directory object is invalid
@retval FR_WRITE_PROTECTED	    The physical drive is write protected
@retval FR_INVALID_DRIVE	    The logical drive number is invalid
@retval FR_NOT_ENABLED	        The volume has no work area
@retval FR_NO_FILESYSTEM        There is no valid FAT volume
@retval FR_MKFS_ABORTED         The f_mkfs() aborted due to any problem
@retval FR_TIMEOUT              Could not get a grant to access the volume within defined period
@retval FR_LOCKED               The operation is rejected according to the file sharing policy
@retval FR_NOT_ENOUGH_CORE      LFN working buffer could not be allocated
@retval FR_TOO_MANY_OPEN_FILES  Number of open files > FF_FS_LOCK
@retval FR_INVALID_PARAMETER    Given parameter is invalid
@see    FRESULT 
*/
FRESULT fatfs_uninit(void)
{
    FRESULT res;                   /* API result code */ 
    LOG("unmount Fatfs...\r\n");
    res = f_unmount( "0:" );		   /* uRegister volume work area (never fails) */
    if (res != RES_OK)
    {
    }
    free(Fatfs);
    Fatfs = NULL;
    return FR_OK;
}

/**
@brief  打开一个文件
@author purc
@date   2018/5-2018/5
@param[in] path 文件路径
@param[in] mode 文件打开的模式
    @verbatim FA_READ			0x01 @endverbatim
    @verbatim FA_WRITE			0x02 @endverbatim
    @verbatim FA_OPEN_EXISTING	0x00 @endverbatim
    @verbatim FA_CREATE_NEW	    0x04 @endverbatim
    @verbatim FA_CREATE_ALWAYS	0x08 @endverbatim
    @verbatim FA_OPEN_ALWAYS	0x10 @endverbatim
    @verbatim FA_OPEN_APPEND	0x30 @endverbatim
@retval FRESULT 
@see    FRESULT   
*/
FRESULT fatfs_open(const TCHAR *path, BYTE mode)
{
    return f_open( &fil, path, mode );
}

/**
@brief  写入打开的文件
@author purc
@date   2018/5-2018/5
@param[in]  buff 需要写入数据的地址
@param[in]  btw  需要写入的字节数
@param[out] *bw  实际写入的字节数
@retval FRESULT 具体内容参考:@link FRESULT @endlink  
*/
FRESULT fatfs_write(const void *buff, UINT btw, UINT *bw)
{
    return f_write( &fil, buff, btw, bw );
}

/**
@brief  读取打开的文件
@author purc
@date   2018/5-2018/5
@param[out] buff 读出数据的缓存地址
@param[in]  btr  需要读出数据的字节数
@param[out] *br  实际读出数据的字节数
@retval FRESULT 
@see    FRESULT   
*/
FRESULT fatfs_read (void *buff, UINT btr, UINT *br)
{
    return f_read( &fil, buff, btr, br );
}

/**
@brief  关闭打开的文件
@author purc
@date   2018/5-2018/5
@param  void
@retval FRESULT 
@see    FRESULT   
*/
FRESULT fatfs_sync (void)
{
    return f_sync( &fil );
}

/**
@brief  关闭打开的文件
@author purc
@date   2018/5-2018/5
@param  void
@retval FRESULT 
@see    FRESULT   
*/
FRESULT fatfs_close (void)
{
    return f_close( &fil );
}

/**
@brief  移动文件读写指针
@author purc
@date   2018/5-2018/5
@param[in] ofs 读写指针偏移字节数
@retval FRESULT 
@see    FRESULT   
*/
FRESULT fatfs_lseek (DWORD ofs)
{
    return f_lseek( &fil, ofs );	
} 

/**
@brief  文件大小
@author purc
@date   2018/5-2018/5
@param  void
@retval FSIZE_t 文件长度
*/
DWORD fatfs_size(void)
{
    return  f_size( &fil );
}

/**
@brief  获取文件读写指针
@author purc
@date   2018/5-2018/5
@param  void
@retval DWORD 文件读写指针
*/
DWORD fatfs_tell(void)
{
    return  f_tell( &fil );
}

/**
@brief  扫描目录下的所有文件
@author purc
@date   2018/5-2018/5
@param[in] path 文件路径
@retval FRESULT 
@see    FRESULT   
*/
FRESULT scan_files( const TCHAR *path )
{
    FRESULT res;
    DIR dir;
    UINT i;
    static FILINFO fno;
    
    TCHAR current_path[50];

    strcpy( current_path , path );
    res = f_opendir( &dir, current_path );                       /* Open the directory */
    if ( res == FR_OK ) 
    {
        for (;;)
        {
            res = f_readdir( &dir, &fno );                   /* Read a directory item */
            if ( res != FR_OK || fno.fname[0] == 0 ) break;  /* Break on error or end of dir */
            if ( fno.fattrib & AM_DIR ) 
            {   
                 /* It is a directory */
                i = strlen(current_path);
                sprintf(&current_path[i], "/%s", fno.fname);
                res = scan_files(current_path);                    /* Enter the directory */
                if (res != FR_OK) break;
                current_path[i] = 0;
            } 
            else 
            {   
                 /* It is a file. */
                LOG("%s/%s\r\n", current_path, fno.fname);
            }
        }
        f_closedir(&dir);
    }

    return res;
}

/**
@brief  扫描目录下的所有文件
@author purc
@date   2018/5-2018/5
@param[in] path 文件路径
@retval FRESULT 
@see    FRESULT   
*/
bool is_find_file( const TCHAR *path, const TCHAR *file_name )
{
    FRESULT res;
    DIR dir;
    static FILINFO fno;

    res = f_opendir( &dir, path );                           /* Open the directory */
    if ( res == FR_OK ) 
    {
        for (;;)
        {
            res = f_readdir( &dir, &fno );                   /* Read a directory item */
            if ( res != FR_OK || fno.fname[0] == 0 ) break;  /* Break on error or end of dir */
            if( NULL != strstr( fno.fname, file_name ) )
            {
                f_closedir(&dir);
                return true;
            }
        }
        f_closedir(&dir);
    }
    
    return false;
}

/**
@brief  删除一个文件或文件夹
@author purc
@date   2018/5-2018/5
@param[in] path 文件路径
@retval FRESULT 
@see    FRESULT   
*/
FRESULT fatfs_unlink( const TCHAR *path )
{
   return f_unlink( path );
}

/**
@brief  重新命名文件或文件夹，附有移动功能
@author purc
@date   2018/5-2018/5
@param[in] old_name 指定要修改的文件或文件夹
@param[in] new_name 新的名称
@retval FRESULT 
@see    FRESULT
*/
FRESULT fatfs_rename( const TCHAR *old_name, const TCHAR *new_name )
{
    return f_rename( old_name, new_name );
}

/**
@brief  创建文件夹
@author purc
@date   2018/5-2018/5
@param[in] path 文件路径
@retval FRESULT 具体内容参考:@link FRESULT @endlink  
*/
FRESULT fatfs_mkdir( const TCHAR* path )
{
    return f_mkdir( path );
}

/**
@brief  更新文件或文件夹时间参数
@author purc
@date   2018/5-2018/5
@param  void
@retval FRESULT 具体内容参考:@link FRESULT @endlink  
*/
FRESULT fatfs_utime( const TCHAR *path, DWORD year, DWORD month, DWORD mday, DWORD hour, DWORD min, DWORD sec )
{
    FILINFO fno;
    fno.fdate = (WORD)(((year - 1980) * 512U) | month * 32U | mday);
    fno.ftime = (WORD)(hour * 2048U | min * 32U | sec / 2U);
    return f_utime(path, &fno);
}

/**
@brief  文件系统测试函数
@deprecated 仅供测试使用
@author purc
@date   2018/5-2018/5
@param  void
@retval void
*/
void fatfs_test(void)
{
    FRESULT res;     /* API result code */
    UINT br;         /* File read/write count */
    UINT bw;         /* File read/write count */    
    const char WriteLine[] = "this is read/write message.txt.";
    char ReadLine[50];
    
    res = fatfs_open ( "0:/message.txt", ( FA_WRITE|FA_READ|FA_CREATE_ALWAYS ) );
    if ( res )
    {
        LOG("file open error-%d\r\n",res);
        fatfs_close();
        return;
    }
    res = fatfs_write( WriteLine, strlen(WriteLine), &bw );
    LOG( "res=%d\r\n", res );
    LOG( "br=%d\r\n", bw );
    res = fatfs_sync();
    LOG( "file size:0x%08x Bytes\r\n", (unsigned int)fatfs_size() );
    /* Close the file */
    fatfs_close();
    LOG( "colse file\r\n" );
        
    res = fatfs_open( "message.txt", FA_READ );
    if ( res )
    {
        LOG( "file open error-%d\r\n", res );
        fatfs_close();
        return;
    }
    res = fatfs_read( ReadLine, 50 , &br );  /* Read a chunk of source file */
    LOG( "res=%d\r\n", res );
    LOG( "br=%d\r\n", br );
    LOG( "%s\r\n", ReadLine );
    /* Close the file */
    fatfs_close();
    LOG( "colse file\r\n" );
    
    scan_files("0:");
    
    if( is_find_file( "0:", "purencai" ) )
    {
        LOG( "find_file \"0:/purencai\"\r\n" );
        
        res = fatfs_unlink("0:/purencai/message.txt");
        if ( res )
        {
            LOG( "file unlink error-%d\r\n", res );
            return;
        }
        res = fatfs_unlink("0:/purencai");
        if ( res )
        {
            LOG( "file unlink error-%d\r\n", res );
            return;
        }
    };
    
    res = fatfs_mkdir( "0:/purc" );
    if ( res )
    {
        LOG( "file mkdir error-%d\r\n", res );
        return;
    }

    res = fatfs_rename( "0:/message.txt", "0:/purc/message.txt" );
    if ( res )
    {
        LOG( "file rename error-%d\r\n", res );
        return;
    }

    res = fatfs_rename( "0:/purc", "0:/purencai" );
    if ( res )
    {
        LOG( "file rename error-%d\r\n", res );
        return;
    }
    
    LOG( "fatfs test finish\r\n" );
}
