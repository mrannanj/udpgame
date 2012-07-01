#ifndef SERVER_NET_THREADPOOL_H
#define SERVER_NET_THREADPOOL_H

// FIXME: how to forward declare pthread_t?
#include <pthread.h>

#include "common/google.h"

struct sockaddr_in;

class ThreadPool {
public:
  explicit ThreadPool(unsigned);

  void Init();
  void Destroy();
  bool AssignConnection(struct sockaddr_in*);

private:
  DISALLOW_COPY_AND_ASSIGN(ThreadPool);

  unsigned FindFreeWorker();
  void SetNonBlocking(int);

  unsigned nthreads_;
  unsigned npipes_;
  pthread_t* threads_;
  int* pipes_;
  struct sockaddr_in* sockaddrs_;
};

#endif

