#ifndef SIMPLE_LOG_H
#define SIMPLE_LOG_H 1

#include "core_base.h"

#ifdef WIN32
#include <tchar.h>
#else
#define TCHAR char
#define _T(x) x
#define _TEXT(x) x
#endif

#ifdef __cplusplus
extern "C" {
#endif

CORE_API int InitializeLogFile(const TCHAR* log_name);
CORE_API int CloseLogFile();

CORE_API int LogInfo(const TCHAR *fmt, ...);
CORE_API int LogError(const TCHAR *fmt, ...);

#ifdef __cplusplus
}
#endif

#endif