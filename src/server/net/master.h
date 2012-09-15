#ifndef SERVER_NET_MASTER
#define SERVER_NET_MASTER

#include <netinet/in.h>

#include "common/google.h"
#include "common/util/timer.h"

#define BUFLEN 512
#define MAX_CLIENTS 5
#define TICKS_PER_SECOND 20

constexpr long frame_time_ns = 1000000000 / TICKS_PER_SECOND;

class Master {
public:
  Master();
  ~Master();
  DISALLOW_COPY_AND_ASSIGN(Master);

  void serve();

private:
  int m_fd;
  sockaddr_in m_si_me;
  Timer m_timer;
  timespec m_frame_time;
};

#endif
