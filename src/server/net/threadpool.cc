#include <assert.h>
#include <unistd.h>
#include <iostream>
#include <netinet/in.h>
#include <string.h>

#include "server/net/threadpool.h"
#include "server/net/slave.h"

ThreadPool::ThreadPool(unsigned nthreads):
  nthreads_(nthreads),
  slaves_(nullptr)
{
}

void ThreadPool::Init() {
  threads_ = new pthread_t[nthreads_];
  assert(threads_ != nullptr);

  slaves_ = new Slave[nthreads_];
  assert(slaves_ != nullptr);
  for (unsigned i = 0; i < nthreads_; ++i) {
    slaves_[i].Init();
  }

  for (unsigned i = 0; i < nthreads_; ++i) {
    pthread_create(&threads_[i], nullptr, create_slave, &slaves_[i]);
  }
}


void ThreadPool::Destroy() {
  assert(threads_ != nullptr);
  delete[] threads_;
  assert(slaves_ != nullptr);
  for (unsigned i = 0; i < nthreads_; ++i) {
    slaves_[i].Destroy();
    pthread_join(threads_[i], NULL);
  }
}

Slave* ThreadPool::AssignConnection(sockaddr_in* sa_client) {
  unsigned thread = FindFreeWorker();
  if (thread == nthreads_)
    return nullptr;
  Slave& s = slaves_[thread];
  memcpy(&s.sa_client_, &sa_client, sizeof(*sa_client));
  int c = 'm';
  assert(1 == write(s.getMasterWritePipe(), &c, 1));
  return &s;
}

unsigned ThreadPool::FindFreeWorker() {
  for (unsigned i = 0; i < nthreads_; ++i) {
    char c;
    if (1 == read(slaves_[i].getMasterReadPipe(), &c, 1))
      return i;
  }
  return nthreads_;
}
