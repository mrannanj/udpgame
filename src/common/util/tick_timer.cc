#include <iostream>

#include "common/util/tick_timer.h"
#include "common/util/timespec.h"

TickTimer::TickTimer(long tickTime):
  mStart(),
  mTickTime(),
  mTarget()
{
  mTickTime.tv_sec = 0;
  mTickTime.tv_nsec = tickTime;
}

void TickTimer::newTick(timespec& moarSleep) {
  clock_gettime(CLOCK_MONOTONIC, &mStart);
  moarSleep = mTickTime;
}

bool TickTimer::isTickTime(timespec& moarSleep) {
  timespec now;
  clock_gettime(CLOCK_MONOTONIC, &now);
  timespec passedTime = now - mStart;

  if (mTickTime < passedTime)
    return true;
  moarSleep = mTickTime - passedTime;
  return false;
}
