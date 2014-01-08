#pragma once

#include <ctime>

class TickTimer {
public:
  TickTimer(long);

  void newTick(timespec&);
  bool isTickTime(timespec&);

private:
  timespec mStart;
  timespec mTickTime;
  timespec mTarget;
};
