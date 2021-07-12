#pragma once

#include "common/net/connection.h"

#include <vector>
#include <map>
#include <array>

struct WorldTicker {
	WorldTicker();

	bool handleAMessage(int);
	void fillMissingInputs(unsigned, std::vector<Connection>&);
	void removeOldFrame(unsigned);
	void setHashes(unsigned, const uint32_t*);
	void setCurrentTick(unsigned);
	bool compareHashes(unsigned);

	unsigned mCurrentTick;
};
