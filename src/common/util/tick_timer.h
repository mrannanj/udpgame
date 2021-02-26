#pragma once

#include <ctime>
#include <chrono>
#include <ratio>

class TickTimer {
public:
	TickTimer(long);

	void newTick(timespec&);
	bool isTickTime(timespec&);

private:
	 std::chrono::high_resolution_clock mClock;
	 std::chrono::time_point<std::chrono::high_resolution_clock> mStart;
	 std::chrono::time_point<std::chrono::high_resolution_clock> mTarget;
	 std::chrono::duration<long, std::nano> mTickTime;
};
