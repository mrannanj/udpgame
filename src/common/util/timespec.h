#pragma once

#include <ostream>
#include <ctime>

std::ostream& operator<<(std::ostream&, const timespec&);
timespec& operator-=(timespec&, timespec&);
timespec& operator+=(timespec&, timespec&);
timespec operator-(timespec&, timespec&);
timespec operator+(timespec&, timespec&);
bool operator<(timespec&, timespec&);
