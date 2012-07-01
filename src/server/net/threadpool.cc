#include <assert.h>
#include <unistd.h>
#include <fcntl.h>
#include <iostream>
#include <netinet/in.h>

#include "server/net/threadpool.h"
#include "server/net/slave.h"

ThreadPool::ThreadPool(unsigned nthreads):
  nthreads_(nthreads),
  npipes_(nthreads*4),
  threads_(nullptr),
  free_threads_(nullptr),
  pipes_(nullptr),
  sockaddrs_(nullptr)
{
}

bool ThreadPool::Init()
{
  threads_ = new pthread_t[nthreads_];
  assert(threads_ != nullptr);

  free_threads_ = new bool[nthreads_];
  assert(threads_ != nullptr);
  for (unsigned i = 0; i < nthreads_; ++i) free_threads_[i] = false;

  pipes_ = new int[npipes_];
  assert(pipes_ != nullptr);
  for (unsigned i = 0; i < npipes_; i += 2)
  {
    assert(pipe(&pipes_[i]) == 0);
    int flags = fcntl(pipes_[i+MASTER_READ], F_GETFL, 0);
    assert(flags != -1);
    assert(fcntl(pipes_[i+MASTER_READ], F_SETFL, flags | O_NONBLOCK) == 0);
  }

  sockaddrs_ = new struct sockaddr_in[nthreads_];
  assert(sockaddrs_ != nullptr);

  for (unsigned i = 0; i < nthreads_; ++i)
  {
    pthread_create(&threads_[i], NULL, slave, &pipes_[i*4]);
  }

  return true;
}

void ThreadPool::Destroy()
{
  assert(threads_ != nullptr);
  delete[] threads_;
  assert(free_threads_ != nullptr);
  delete[] free_threads_;
  assert(pipes_ != nullptr);
  for (unsigned i = 0; i < npipes_; ++i)
    close(pipes_[i]);
  delete[] pipes_;
}

bool ThreadPool::AssignConnection(struct sockaddr_in*)
{
  unsigned thread = FindFreeWorker();
  if (thread == nthreads_)
    return false;
  return true;
}

unsigned ThreadPool::FindFreeWorker()
{
  for (unsigned i = 0; i < nthreads_; ++i)
  {
    char c;
    if (free_threads_[i] || (1 == read(pipes_[4*i+MASTER_READ], &c, 1)))
    {
      std::cout << "assigning thread: " << i << std::endl;
      free_threads_[i] = false;
      c = 'm';
      assert(1 == write(pipes_[4*i+MASTER_WRITE], &c, 1));
      return i;
    }
  }

  std::cout << "no threads free" << std::endl;
  return nthreads_;
}
