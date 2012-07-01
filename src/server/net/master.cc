#include <iostream>
#include <string.h>
#include <pthread.h>

#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#include "common/die.h"
#include "common/defaults.h"

#define BUFLEN 512
#define MAX_CLIENTS 5

static void* slave_server(void*);

void* slave_server(void* /* ptr */)
{
  std::cout << "slave spawned" << std::endl;
  return NULL;
}

int main(void)
{
  struct sockaddr_in si_me, si_other;
  int fd;
  char buf[BUFLEN];
  socklen_t slen = sizeof(si_other);
  pthread_t threads[MAX_CLIENTS];
  char free_threads[MAX_CLIENTS];
  memset(&free_threads, 1, sizeof(free_threads));

	std::cout << "Setting up udp socket on port " << SERVER_PORT << std::endl;

  if (0 > (fd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)))
    die("socket");

  memset(&si_me, 0, sizeof(si_me));
  si_me.sin_family = AF_INET;
  si_me.sin_port = htons(SERVER_PORT);
  si_me.sin_addr.s_addr = htonl(INADDR_ANY);
  if (0 > bind(fd, reinterpret_cast<const sockaddr*>(&si_me), sizeof(si_me)))
    die("bind");

  for (int i = 0; i < 10; ++i)
  {
    memset(&buf, 0, sizeof(buf));
    if (0 > recvfrom(fd, buf, BUFLEN, 0, reinterpret_cast<sockaddr*>(&si_other), &slen))
      die("recvfrom");

    std::cout << "Received packet from " << inet_ntoa(si_other.sin_addr) << std::endl;
    std::cout << "it says: " << buf << std::endl;

    int j = 0;
    for (; j < MAX_CLIENTS; ++j)
      if (free_threads[j])
        break;

    if (j == MAX_CLIENTS)
    {
      std::cout << "server is full, not serving" << std::endl;
    }
    else 
    {
      free_threads[j] = 0;
      pthread_create(&threads[j], NULL, slave_server, NULL);
    }
  }

  close(fd);

	return 0;
}
