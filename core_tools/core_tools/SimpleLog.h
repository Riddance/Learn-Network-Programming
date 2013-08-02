#ifndef SIMPLE_LOG_H
#define SIMPLE_LOG_H 1

#include "CoreBase.h"

#ifdef WIN32
#include <tchar.h>
#else
#define TCHAR char
#endif

#ifdef __cplusplus
extern "C" {
#endif

CORE_API int Init_Log_File(const TCHAR* FileName);

CORE_API int Close_Log_File();

CORE_API int Log_Info(const TCHAR *fmt, ...);



#ifdef __cplusplus
}
#endif

#endif