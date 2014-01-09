#pragma once

#include <cstddef>

#define SERVER_PORT 4666
#define SERVER_ADDR "127.0.0.1"
#define TICKS_PER_SEC 30

constexpr size_t GIGA = 1000000000;
constexpr size_t MEGA = 1000000;
constexpr float secs_per_tick = 1.0f/TICKS_PER_SEC;
constexpr long ns_per_tick = GIGA/TICKS_PER_SEC;
constexpr size_t STATIC_FRAME_DELTA = 3;
