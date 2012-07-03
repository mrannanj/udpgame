#include <assert.h>
#include <string.h>

#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>

#include "server/net/sockethelper.h"

int listen_udp(uint16_t port, sockaddr_in* sa_me) {
  int fd;

  assert (0 <= (fd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)));
  memset(sa_me, 0, sizeof(*sa_me));
  sa_me->sin_family = AF_INET;
  sa_me->sin_port = htons(port);
  sa_me->sin_addr.s_addr = htonl(INADDR_ANY);
  assert(0 ==
    bind(fd, reinterpret_cast<const sockaddr*>(sa_me), sizeof(*sa_me)));

  return fd;
}
