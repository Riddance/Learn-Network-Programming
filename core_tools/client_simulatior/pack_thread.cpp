#include "stdafx.h"
#include "pack_thread.h"

PackThread::PackThread()
{
}

PackThread::~PackThread()
{
}

int PackThread::Initialize(const TCHAR* ip_address, int port)
{
	int ret = false;

	m_sockaddr_in.sin_family = AF_INET;
	m_sockaddr_in.sin_port = htons(port);
	USES_CONVERSION;
	m_sockaddr_in.sin_addr.s_addr = inet_addr(W2A(ip_address));

	if (m_sockaddr_in.sin_addr.s_addr == INADDR_NONE)
	{
	}

	ret = true;
out:
	return ret;
}

int PackThread::UnInit()
{
	if (INVALID_SOCKET != m_socket)
	{
		closesocket(m_socket);
		m_socket = INVALID_SOCKET;
	}

	m_run_flag = false;
}

int PackThread::Connect()
{
	int ret = false;
	int value = 0;
	if (INVALID_SOCKET != m_socket)
	{
		closesocket(m_socket);
		m_socket = INVALID_SOCKET;
	}
	Sleep(10);

	m_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_IP);
	if (m_socket == INVALID_SOCKET)
	{
	}

	value = connect(m_socket, (struct sockaddr *)&m_sockaddr_in, sizeof(m_sockaddr_in));
	if (value == SOCKET_ERROR)
	{
	}

	ret = true;
out:
	return ret;
}