#ifndef PACK_THREAD_H
#define PACK_THREAD_H

#include <tchar.h>

class PackThread
{
public:
	PackThread();
	~PackThread();

	int Initialize(const TCHAR* ip_address, int port);
	int UnInit();

	int Run();

private:
	int m_run_flag;

	SOCKET m_socket;
	SOCKADDR_IN m_sockaddr_in;

	int Connect();

};

#endif