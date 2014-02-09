#include <iostream>

#include "common/util/tick_timer.h"
#include "common/util/timespec.h"

TickTimer::TickTimer(sf::Int64 tickTime):
  mClock(),
  mStart(),
  mTarget(),
  mTickTime(sf::microseconds(tickTime))
{
}

void TickTimer::newTick(sf::Time& moarSleep) {
  mStart = mClock.getElapsedTime();
  moarSleep = mTickTime;
}

bool TickTimer::isTickTime(sf::Time& moarSleep) {
  auto timePassed = mClock.getElapsedTime() - mStart;

  if (mTickTime < timePassed)
    return true;
  moarSleep = mTickTime - timePassed;
  return false;
}
