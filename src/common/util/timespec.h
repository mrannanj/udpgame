#pragma once

#include <ostream>
#include <ctime>
#include <chrono>

std::ostream& operator<<(std::ostream&, const timespec&);
timespec& operator-=(timespec&, timespec&);
timespec& operator+=(timespec&, timespec&);
timespec operator-(timespec&, timespec&);
timespec operator+(timespec&, timespec&);
bool operator<(timespec&, timespec&);

timespec from_duration(const std::chrono::duration<long, std::nano>&);
