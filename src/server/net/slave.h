#ifndef SERVER_NET_SLAVE_H
#define SERVER_NET_SLAVE_H

#include <netinet/in.h>

class Slave {
public:
  Slave();
  ~Slave();

  void Init();
  void Destroy();

  int getMasterReadPipe() const;
  int getMasterWritePipe() const;
  uint16_t getListeningPort();

  void Serve();

  struct sockaddr_in sa_me_;
  struct sockaddr_in sa_client_;

private:
  void InitReadFds();
  void SignalReady();
  void GetTask();
  void SetNonBlocking(int);
  void SayHi();

  int socket_fd_;
  int read_p_[2];
  int write_p_[2];
};

void* create_slave(void*);

#endif
