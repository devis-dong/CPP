/*** 
 * @Author: devis dong
 * @Date: 2021-07-13 12:56:45
 * @LastEditTime: 2021-07-15 17:41:24
 * @LastEditors: devis dong
 * @Description: 
 * @FilePath: \C++\src\common\dsdefine.h
 */

#ifndef DSDEFINES_H
#define DSDEFINES_H

#ifndef I
    #define I
#endif

#ifndef O
    #define O
#endif


#ifdef WIN32
    #ifdef __cplusplus
        #define DLL_EXPORT_C_DECL extern "C" __declspec(dllexport)
        #define DLL_IMPORT_C_DECL extern "C" __declspec(dllimport)
        #define DLL_EXPORT_DECL extern __declspec(dllexport)
        #define DLL_IMPORT_DECL extern __declspec(dllimport)
        #define DLL_EXPORT_CLASS_DECL __declspec(dllexport)
        #define DLL_IMPORT_CLASS_DECL __declspec(dllimport)
    #else
        #define DLL_EXPORT_DECL __declspec(dllexport)
        #define DLL_IMPORT_DECL __declspec(dllimport)
    #endif
#else
    #ifdef __cplusplus
        #define DLL_EXPORT_C_DECL extern "C"
        #define DLL_IMPORT_C_DECL extern "C"
        #define DLL_EXPORT_DECL extern
        #define DLL_IMPORT_DECL extern
        #define DLL_EXPORT_CLASS_DECL
        #define DLL_IMPORT_CLASS_DECL
    #else
        #define DLL_EXPORT_DECL extern
        #define DLL_IMPORT_DECL extern
    #endif
#endif

#define LOGTARGET   Logger::target_all
#define LOGLEVEL    Logger::level_all
#define LOGFILE     "logs/log.txt"

typedef enum ds_ostype_
{
    os_unknown,
    os_windows,
    os_linux,
    os_unix,
    os_sun_sparc,
    os_sun_x86,
    os_aix,
}ds_ostype;



#endif
