#ifdef WIN32
#include <io.h>
#include <direct.h>
#else
#include
#endif

#include "SimpleLog.h"

int LogFile = -1;


int Init_Log_File(const TCHAR* LogName)
{

#ifdef WIN32
    _tmkdir(LogName);
    LogFile = _topen(FileName, _T("w+b"));
#else
    mkdir(LogName, 0777);
    LogFile = open(FileName,);
#endif

    if (LogFile)
        return true;

    return false;
}

int Close_Log_File()
{
    if (LogFile)
        fclose(LogFile);

    return true;
}

int Log_Info(const TCHAR *fmt, ...)
{
