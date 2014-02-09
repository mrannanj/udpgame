#pragma once

#include <cstddef>

#define SERVER_PORT 4666
#define SERVER_ADDR "127.0.0.1"
#define TICKS_PER_SEC 30

const size_t GIGA = 1000000000;
const size_t MEGA = 1000000;
const float secs_per_tick = 1.0f/TICKS_PER_SEC;
const long ns_per_tick = GIGA/TICKS_PER_SEC;
const long ms_per_tick = MEGA/TICKS_PER_SEC;
const size_t STATIC_FRAME_DELTA = 2;
