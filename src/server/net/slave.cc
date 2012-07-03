#include <iostream>
#include <unistd.h>
#include <assert.h>
#include <fcntl.h>
#include <iostream>

#include <sys/socket.h>

#include "common/die.h"

#include "server/net/slave.h"
#include "server/net/sockethelper.h"

#define MAXBUF 512

void* create_slave(void* slave) {
  ((Slave*)slave)->Serve();
  return nullptr;
}

Slave::Slave():
  socket_fd_(-1)
{
}

void Slave::Init() {
  assert(pipe(write_p_) == 0);
  SetNonBlocking(write_p_[0]);
  assert(pipe(read_p_) == 0);
  socket_fd_ = listen_udp(0, &sa_me_);
  std::cout << "Slave listening to " << getListeningPort() << std::endl;
}

void Slave::Destroy() {
  close(socket_fd_);
  close(write_p_[0]);
  close(write_p_[1]);
  close(read_p_[0]);
  close(read_p_[1]);
}

void Slave::SetNonBlocking(int fd) {
  int flags = fcntl(fd, F_GETFL, 0);
  assert(flags != -1);
  assert(fcntl(fd, F_SETFL, flags | O_NONBLOCK) == 0);
}

int Slave::getMasterReadPipe() const {
  return write_p_[0];
}

int Slave::getMasterWritePipe() const {
  return read_p_[1];
}

uint16_t Slave::getListeningPort() {
  sockaddr_in sa;
  socklen_t addrlen = sizeof(sa);
  assert(0 == getsockname(socket_fd_, (sockaddr*)&sa, &addrlen));
  return ntohs(sa.sin_port);
}

void Slave::SignalReady() {
  char c = 's';
  assert(1 == write(write_p_[1], &c, 1));
}

void Slave::GetTask() {
  char c;
  assert(1 == read(read_p_[0], &c, 1));
  assert(c == 'm');
  assert(connect(socket_fd_, (sockaddr*)&sa_client_, sizeof(sa_client_) == 0));
}

void Slave::Serve() {
  for (;;) {
    SignalReady();
    GetTask();
    SayHi();
  }
}

void Slave::SayHi() {
  char buf[MAXBUF];
  ssize_t nread;
  nread = recv(socket_fd_, buf, MAXBUF, 0);
  assert(nread > 0);
  buf[nread] = '\0';

  std::cout << "client said: " << buf << std::endl;
  send(socket_fd_, "HI", 2, 0);
}
