#ifndef SERVER_NET_MASTER
#define SERVER_NET_MASTER

#include <netinet/in.h>

#include "common/google.h"
#include "server/net/threadpool.h"

#define BUFLEN 512
#define MAX_CLIENTS 5

class Master {
public:
  Master();

  void Init();
  void Serve();
  void Destroy();

private:
  DISALLOW_COPY_AND_ASSIGN(Master);

  int fd_;
  ThreadPool thread_pool_;
  struct sockaddr_in si_me_;
};

#endif
