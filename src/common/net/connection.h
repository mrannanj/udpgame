#pragma once

#include <arpa/inet.h>
#include <string>
#include <cstring>
#include <iostream>
#include <unistd.h>

constexpr ssize_t MAXMSG = 1000000;

struct Connection {
	Connection();
	Connection(int, const sockaddr_in&);
	Connection(const std::string&);

	Connection(Connection&&);
	Connection& operator=(Connection&&);

	Connection& operator=(const Connection&) = delete;
	Connection(const Connection&) = delete;
	~Connection();

	void sendMessage();
	template <class T> ssize_t checkMessages(T&);

	ssize_t mPos;
	int mSocket;
	sockaddr_in mSockaddr;
	unsigned mLastFrameOk;
	char *mBuf;
};

template <class T> ssize_t Connection::checkMessages(T& handler)
{
	if (mPos >= MAXMSG)
		return -1;
	size_t count = MAXMSG - mPos;
	ssize_t nread = read(mSocket, &mBuf[mPos], count);
	if (nread <= 0)
		return -1;
	mPos += nread;
	while ((size_t)mPos >= sizeof(int)) {
		int size;
		memcpy(&size, mBuf, sizeof(int));
		size = ntohl(size);
		int tsize = size + sizeof(int);
		if (tsize > MAXMSG)
			return -1;
	}
	return nread;
}

std::ostream& operator<<(std::ostream& os, const Connection&);
