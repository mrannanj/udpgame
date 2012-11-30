#include <iostream>

#include "common/util/tick_timer.h"
#include "common/util/timespec.h"

#define GIGA 1000000000

TickTimer::TickTimer(long tick_time)
{
  m_tick_time.tv_sec = 0;
  m_tick_time.tv_nsec = tick_time;
}

void TickTimer::start_tick()
{
  clock_gettime(CLOCK_MONOTONIC, &m_start);
  m_target = m_start + m_tick_time;
}

void TickTimer::end_tick()
{
  clock_gettime(CLOCK_MONOTONIC, &m_end);
  if (m_end < m_target)
  {
    timespec diff(m_target - m_end);
    nanosleep(&diff, NULL);
  }
  else
  {
    timespec diff(m_end - m_target);
    std::cout << "tick went " << diff << " overtime" << std::endl;
  }
}

unsigned long ns_per_tick(unsigned ticks_per_sec)
{
  return (unsigned long)(GIGA * (1.0f/ticks_per_sec));
}

