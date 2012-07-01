#include <assert.h>
#include <unistd.h>

#include "server/net/threadpool.h"

ThreadPool::ThreadPool(unsigned nthreads):
  nthreads_(nthreads),
  nfree_(nthreads), 
  threads_(nullptr),
  pipes_(nullptr)
{
}

bool ThreadPool::Init()
{
  threads_ = new pthread_t[nthreads_];
  assert(threads_ != nullptr);
  pipes_ = new int[2*nthreads_];
  assert(pipes_ != nullptr);

  for (unsigned i = 0; i < nthreads_*2; i += 2)
    assert(pipe(&pipes_[i]) > 0);

  return true;
}

void ThreadPool::Destroy()
{
  assert(threads_ != nullptr);
  delete[] threads_;
  assert(pipes_ != nullptr);
  for (unsigned i = 0; i < nthreads_*2; ++i)
  {
    close(pipes_[i]);
    close(pipes_[i+1]);
  }
}

bool ThreadPool::HasFreeWorker()
{
  return nfree_ > 0;
}
