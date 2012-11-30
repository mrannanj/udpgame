#ifndef COMMON_UTIL_TIMESPEC_H
#define COMMON_UTIL_TIMESPEC_H

#include <ostream>
#include <ctime>

std::ostream& operator<<(std::ostream&, const timespec&);
timespec& operator-=(timespec&, timespec&);
timespec& operator+=(timespec&, timespec&);
timespec operator-(timespec&, timespec&);
timespec operator+(timespec&, timespec&);
bool operator<(timespec&, timespec&);

#endif

