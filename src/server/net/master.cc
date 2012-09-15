#include <iostream>
#include <string.h>
#include <pthread.h>

#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#include "server/net/master.h"
#include "common/die.h"
#include "common/defaults.h"

#include "server/net/threadpool.h"
#include "server/net/slave.h"

#include "common/net/sockethelper.h"

Master::Master():
  m_fd(listen_udp(SERVER_PORT, &m_si_me))
{
  memset(&m_frame_time, 0, sizeof(m_frame_time));
  m_frame_time.tv_nsec = frame_time_ns;
}

void Master::serve()
{
  char buf[BUFLEN];

  for (;;) {
    m_timer.start_timer();
    sockaddr_in si_client;
    socklen_t slen = sizeof(si_client);
    memset(&buf, 0, sizeof(buf));
    if (0 > recvfrom(m_fd, buf, BUFLEN, 0, (sockaddr*)(&si_client), &slen))
      die("recvfrom");

    if (strncmp("PING", buf, 4) == 0)
    {
      const char byemsg[] = "PONG";
      sendto(m_fd, byemsg, sizeof(byemsg), 0, (sockaddr*)&si_client, slen);
      std::cout << "PING from " << inet_ntoa(si_client.sin_addr) << std::endl;
    }
    else
    {
      std::cout << "unknown message from " << inet_ntoa(si_client.sin_addr) << std::endl;
    }
    m_timer.stop_timer();
    timespec elapsed;
    timespec sleep_time;
    time_delta(m_timer.start(), m_timer.end(), elapsed);
    time_delta(elapsed, m_frame_time, sleep_time);
    nanosleep(&sleep_time, NULL);
  }
}

Master::~Master() {
  close(m_fd);
}
