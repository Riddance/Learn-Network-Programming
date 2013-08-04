#include <time.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#ifdef WIN32
#include <fcntl.h>
#include <sys\types.h>
#include <sys\stat.h>
#include <io.h>
#include <direct.h>
#include <stdarg.h>
#else

#endif

#include "simple_log.h"

int log_file = -1;

int GetNowTimeToBuffer(TCHAR* buffer, int buffer_size)
{
	time_t	  time_now;
	struct tm tm_time_now	= {0};
	int		  format_size	= 0;
	int		  used_size		= 0;

	time_now = time(NULL);

	const TCHAR* time_format = _T("%4d-%02d-%02d__%02d:%02d:%02d");
#ifdef WIN32
	localtime_s(&tm_time_now, &time_now);
	format_size = _tcslen(time_format);
#else
	localtime_r(&time_now, &tm_time_now);
	format_size = strlen(time_format);
#endif

	if (buffer_size < format_size)
		return used_size;

#ifdef WIN32
	used_size = (int)_sntprintf(buffer, (size_t)buffer_size, time_format, 
		tm_time_now.tm_year + 1900,tm_time_now.tm_mon + 1, tm_time_now.tm_mday,
		tm_time_now.tm_hour, tm_time_now.tm_min, tm_time_now.tm_sec
	);
#else
	used_size = (int)snprintf(buffer, (size_t)BufferSize, time_format,
		tm_time_now.tm_year + 1900,tm_time_now.tm_mon + 1, tm_time_now.tm_mday,
		tm_time_now.tm_hour, tm_time_now.tm_min, tm_time_now.tm_sec
	);
#endif

	return used_size;
}


int InitializeLogFile(const TCHAR* LogName)
{
	TCHAR		file_name[255];
	TCHAR* pos			= NULL;
	int left_size		= 0;
	int used_size		= 0;
	int ret				= false;

	if (!LogName)
		goto out;

	pos = file_name;
	left_size = (int)sizeof(file_name);

#ifdef WIN32
	used_size = _sntprintf(pos, left_size, _T("%s"), LogName);
#else
	used_size = snprintf(pos, left_size, _T("%s"), LogName);
#endif

	left_size -= used_size;
	pos += used_size;

	if (left_size == 0)
		goto out;

	used_size = GetNowTimeToBuffer(pos, left_size);
	if (used_size == 0)
		goto out;

	left_size -= used_size;
	pos += used_size;

	if (left_size <= 4)
		goto out;

#ifdef WIN32
    _tmkdir(LogName);
	_sntprintf(pos, left_size, _T(".log"));
	log_file = _topen(file_name, _O_WRONLY | _O_CREAT, _S_IREAD | _S_IWRITE);
#else
    mkdir(LogName, 0777);
	snprintf(pos, left_size, _T(".log"));
	log_file = open(file_name, O_WRONLY | O_CREAT);
#endif

	if (log_file == -1)
		goto out;

	ret = true;
out:
	return ret;
}

int CloseLogFile()
{
	if (log_file != -1)
		_close(log_file);

    return true;
}

int LogError(const TCHAR* fmt, ...)
{
	TCHAR error_info[65536];
	TCHAR line[65536];
	TCHAR time_buf[1024];
	va_list va;
	int ret = false;
	int used_size = 0;
	int wrote_size = 0;

	va_start(va, fmt);

#ifdef WIN32
	_vstprintf(error_info, fmt, va);
#else
	vsprintf(error_info, fmt, va);
#endif

	ret = GetNowTimeToBuffer(time_buf, _countof(time_buf));
	if (ret == 0)
		goto out;

#ifdef WIN32
	used_size = _sntprintf(line, 65536, _T("ERROR:[%s]\t%s\n"), time_buf, error_info);
#else
	used_size = snprintf(line, 65536, _T("ERROR:[%s]\t%s\n"), time_buf, error_info);
#endif

	_write(log_file, line, (unsigned int)used_size);

	ret = true;
out:
	va_end(va);
	return ret;
}

int LogInfo(const TCHAR* fmt, ...)
{
	int ret			= false;
	int used_size	= 0;
	int wrote_size	= 0;
	TCHAR error_info[65536];
	TCHAR time_buf[1024];
	TCHAR line[65536];

	va_list va;
	va_start(va, fmt);

#ifdef WIN32
	_vstprintf(error_info, fmt, va);
#else
	vsprintf(error_info, fmt, va);
#endif

	ret = GetNowTimeToBuffer(time_buf, _countof(time_buf));
	if (ret == 0)
		goto out;

#ifdef WIN32
	used_size = _sntprintf(line, _countof(line), _T("INFO:[%s]\t%s\n"), time_buf, error_info);
#else
	used_size = snprintf(line, _countof(line), _T("INFO:[%s]\t%s\n"), time_buf, error_info);
#endif

	_write(log_file, line, (unsigned int)used_size);

	ret = true;
out:
	va_end(va);
	return ret;
}
