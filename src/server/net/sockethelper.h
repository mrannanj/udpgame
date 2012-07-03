#ifndef SERVER_NET_SOCKETHELPER_H
#define SERVER_NET_SOCKETHELPER_H

#include <arpa/inet.h>

struct sockaddr_in;

int listen_udp(uint16_t, sockaddr_in*);

#endif
