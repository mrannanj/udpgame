#ifndef COMMON_UTIL_TIMER_H
#define COMMON_UTIL_TIMER_H

#include <ctime>

class Timer
{
public:
  Timer();

  void start_timer();
  void stop_timer();
  const timespec& start() const;
  const timespec& end() const;

private:
  timespec m_start;
  timespec m_end;
};

void time_delta(const timespec&, const timespec&, timespec&);

#endif
