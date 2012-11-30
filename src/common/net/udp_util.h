#ifndef COMMON_NET_UDP_UTIL_H
#define COMMON_NET_UDP_UTIL_H

#include <arpa/inet.h>

struct sockaddr_in;

int open_udp_fd(uint16_t, sockaddr_in*);

#endif
