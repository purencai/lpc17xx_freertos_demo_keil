#ifndef __FILE_OPERATION_H__
#define __FILE_OPERATION_H__

#include "system.h"
#include "ff.h"

extern FRESULT fatfs_init( void );
extern FRESULT fatfs_uninit( void );
extern FRESULT fatfs_open( const TCHAR *path, BYTE mode );
extern FRESULT fatfs_write( const void *buff, UINT btw, UINT *bw );
extern FRESULT fatfs_read( void *buff, UINT btr, UINT *br );
extern FRESULT fatfs_sync (void);
extern FRESULT fatfs_close( void );
extern FRESULT fatfs_lseek( DWORD ofs );
extern DWORD fatfs_size( void ); 
extern DWORD fatfs_tell( void );

extern FRESULT scan_files( const TCHAR* path );
extern bool is_find_file( const TCHAR* path, const TCHAR* file_name );

extern FRESULT fatfs_unlink ( const TCHAR *path );
extern FRESULT fatfs_rename( const TCHAR *old_name, const TCHAR *new_name );
extern FRESULT fatfs_mkdir( const TCHAR *path );
extern FRESULT fatfs_utime( const TCHAR* path, DWORD year, DWORD month, DWORD mday, DWORD hour, DWORD min, DWORD sec );

extern void fatfs_test( void );

#endif //__FILE_OPERATION_H__
