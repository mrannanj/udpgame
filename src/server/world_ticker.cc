#include <iostream>
#include <cstring>

#include "server/world_ticker.h"
#include "common/config.h"

using namespace std;

WorldTicker::WorldTicker():
	mCurrentTick(0)
{
}

void WorldTicker::setCurrentTick(unsigned tick) {
	mCurrentTick = tick;
}
