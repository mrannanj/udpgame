#include <iostream>
#include <unistd.h>
#include <assert.h>

#include "server/net/slave.h"
#include "common/die.h"

void* create_slave(void* pipes) {
  Slave slave((int*) pipes);
  slave.Serve();
  return nullptr;
}

Slave::Slave(int* pipes):
  pipes_(pipes)
{
}

void Slave::SignalReady() {
  char c = 's';
  assert(1 == write(pipes_[SLAVE_WRITE], &c, 1));
}

void Slave::GetTask() {
  char c;
  assert(1 == read(pipes_[SLAVE_READ], &c, 1));
  if (c == 'm') {
    std::cout << "received mission!" << std::endl;
  } else if (c == 'q') {
    std::cout << "done?" << std::endl;
  } else {
    assert(false);
  }
}

void Slave::Serve() {
  for (;;) {
    SignalReady();
    GetTask();
  }
}
