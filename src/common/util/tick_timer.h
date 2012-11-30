#ifndef COMMON_UTIL_TICK_TIMER_H
#define COMMON_UTIL_TICK_TIMER_H

#include <ctime>

class TickTimer
{
public:
  TickTimer(long);
  void start_tick();
  void end_tick();

private:
  unsigned long time_delta() const;
  void sleep_rest() const;

  timespec m_start;
  timespec m_end;
  timespec m_tick_time;
  timespec m_target;
};

#endif

