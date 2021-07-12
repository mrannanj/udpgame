#include "server/server.h"
#include "common/config.h"
#include "common/util/die.h"
#include "common/util/timespec.h"
#include "common/util/tick_timer.h"

#include <netinet/tcp.h>
#include <iostream>
#include <cassert>
#include <cstring>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/select.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>

using namespace std;

Server::Server(int quit):
	mQuit(quit),
	mListenSA(),
	mListenFD(-1),
	mClients(),
	mWorld(true),
	mWorldTicker()
{
}

void Server::init() {
	memset(&mListenSA, 0, sizeof(mListenSA));
	mListenSA.sin_family = AF_INET;
	mListenSA.sin_addr.s_addr = INADDR_ANY;
	mListenSA.sin_port = htons(SERVER_PORT);
	mListenFD = socket(AF_INET, SOCK_STREAM, 0);
	if (mListenFD == -1) die("socket");

	int on = 1;
	if (0 != setsockopt(mListenFD, SOL_SOCKET,
			    SO_REUSEADDR, &on, sizeof(on)))
		die("setsockopt");
	if (0 != setsockopt(mListenFD, IPPROTO_TCP,
			    TCP_NODELAY, &on, sizeof(on)))
		die("setsockopt");

	if (0 != ::bind(mListenFD, (sockaddr*)&mListenSA, sizeof(mListenSA)))
		die("bind");
	if (0 != listen(mListenFD, 10))
		die("listen");
	if (-1 == fcntl(mListenFD, F_SETFL, O_NONBLOCK))
		die("fcntl");
}

void Server::serve() {
	fd_set fds;
	TickTimer timer(ns_per_tick);
	timespec max_sleep;
	timer.newTick(max_sleep);
	do {
		int nfds = mkFDSet(&fds);
		if (-1 == pselect(nfds, &fds, nullptr, nullptr,
				  &max_sleep, nullptr)) {
			if (errno != EINTR)
				die("select");
			FD_ZERO(&fds);
		}
		acceptNewClient(fds);
		checkClientInput(fds);
		if (timer.isTickTime(max_sleep)) {
			unsigned tickNum = mWorld.mTickNumber + 1;
			mWorldTicker.setCurrentTick(tickNum);
			timer.newTick(max_sleep);
		}
	} while(!FD_ISSET(mQuit, &fds));
	cout << "quitting" << endl;
}

void Server::acceptNewClient(fd_set& fds) {
	if (FD_ISSET(mListenFD, &fds)) {
		sockaddr_in sa;
		socklen_t sa_len;
		int client = accept(mListenFD, (sockaddr*)&sa, &sa_len);
		if (client != -1) {
			mClients.emplace_back(client, sa);
			Connection& c = mClients.back();
			c.mLastFrameOk = mWorld.mTickNumber;
			cout << c << " connected" << endl;
		}
	}
}

void Server::checkClientInput(fd_set& fds) {
	for (auto c = mClients.begin(); c != mClients.end();) {
		if (!FD_ISSET(c->mSocket, &fds)) {
			++c;
			continue;
		}
		ssize_t nread = c->checkMessages(mWorldTicker);
		if (nread <= 0) {
			cout << *c << " disconnected" << endl;
			c = mClients.erase(c);
		} else {
			++c;
		}
	}
}

int Server::mkFDSet(fd_set *set) {
	FD_ZERO(set);
	FD_SET(mQuit, set);
	FD_SET(mListenFD, set);
	int m = max(mListenFD, mQuit);
	for (const Connection& c : mClients) {
		m = max(m, c.mSocket);
		FD_SET(c.mSocket, set);
	}
	return m + 1;
}
