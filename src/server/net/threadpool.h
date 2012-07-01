#ifndef SERVER_NET_THREADPOOL_H
#define SERVER_NET_THREADPOOL_H

// FIXME: how to forward declare pthread_t?
#include <pthread.h>

#include "common/google.h"

class ThreadPool
{
public:
  explicit ThreadPool(unsigned);

  bool Init();
  void Destroy();
  bool HasFreeWorker();

private:
  DISALLOW_COPY_AND_ASSIGN(ThreadPool);

  unsigned nthreads_;
  unsigned nfree_;
  pthread_t* threads_;

  // FIXME?
  int* pipes_;
};

#endif