#ifndef SERVER_NET_MASTER
#define SERVER_NET_MASTER

#include <netinet/in.h>

#include "common/google.h"

#define BUFLEN 512
#define MAX_CLIENTS 5

class Master {
public:
  Master();
  ~Master();
  DISALLOW_COPY_AND_ASSIGN(Master);

  void serve();

private:
  int m_fd;
  struct sockaddr_in m_si_me;
};

#endif
