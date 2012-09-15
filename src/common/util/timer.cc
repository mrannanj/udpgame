#include "common/util/timer.h"

Timer::Timer()
{
}

void Timer::start_timer()
{
  clock_gettime(CLOCK_MONOTONIC, &m_start);
}

void Timer::stop_timer()
{
  clock_gettime(CLOCK_MONOTONIC, &m_end);
}

const timespec& Timer::start() const
{
  return m_start;
}

const timespec& Timer::end() const
{
  return m_end;
}

void time_delta(const timespec& t1, const timespec& t2, timespec& delta)
{
  delta.tv_sec = t2.tv_sec - t2.tv_sec;
  if (t2.tv_nsec >= t1.tv_nsec)
  {
    delta.tv_nsec = t2.tv_nsec - t1.tv_nsec;
  }
  else
  {
    delta.tv_nsec = t2.tv_nsec - t1.tv_nsec + 1000000000;
  }
}

