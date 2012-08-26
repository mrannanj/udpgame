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
  fd_(-1),
  thread_pool_(MAX_CLIENTS)
{
}

void Master::Init() {
  thread_pool_.Init();
  fd_ = listen_udp(SERVER_PORT, &si_me_);
}

void Master::Serve() {
  char buf[BUFLEN];
  sockaddr_in si_client;
  socklen_t slen = sizeof(si_client);

  for (;;) {
    memset(&buf, 0, sizeof(buf));
    if (0 > recvfrom(fd_, buf, BUFLEN, 0, reinterpret_cast<sockaddr*>(&si_client), &slen))
      die("recvfrom");
    std::cout << "Got message from " << inet_ntoa(si_client.sin_addr) << std::endl;

    if (strncmp("HI", buf, 2) == 0) {
      Slave* slave = thread_pool_.AssignConnection(&si_client);
      if (slave == nullptr) {
        std::cout << "Server is full, disconnecting client. " << std::endl;
        continue;
      }
      sprintf(buf, "OK %hu\n", slave->getListeningPort());
      sendto(fd_, buf, strlen(buf), 0, (const sockaddr*)&si_client, slen);
      continue;
    }
    const char byemsg[] = "BYE";
    sendto(fd_, byemsg, strlen(byemsg), 0, (const sockaddr*)&si_client, slen);
  }
}

void Master::Destroy() {
  thread_pool_.Destroy();
  close(fd_);
}
