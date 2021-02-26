#include <iostream>

#include "common/util/tick_timer.h"
#include "common/util/timespec.h"

using namespace std::chrono;

TickTimer::TickTimer(long tickTime):
	mClock(),
	mStart(),
	mTarget(),
	mTickTime(nanoseconds(tickTime))
{
}

void TickTimer::newTick(timespec& moarSleep)
{
	mStart = mClock.now();
	moarSleep = from_duration(mTickTime);
}

bool TickTimer::isTickTime(timespec& moarSleep)
{
	duration<long, std::nano> timePassed = mClock.now() - mStart;

	if (mTickTime < timePassed)
		return true;
	moarSleep = from_duration(mTickTime - timePassed);
	return false;
}
