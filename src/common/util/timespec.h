#pragma once

#if 0
#include <ostream>
#include <ctime>
#include <chrono>
#include <SFML/System/Time.hpp>

std::ostream& operator<<(std::ostream&, const timespec&);
timespec& operator-=(timespec&, timespec&);
timespec& operator+=(timespec&, timespec&);
timespec operator-(timespec&, timespec&);
timespec operator+(timespec&, timespec&);
bool operator<(timespec&, timespec&);

timespec from_duration(const std::chrono::duration<long, std::nano>&);
sf::Time from_duration(const std::chrono::duration<sf::Int64, std::micro>&);
#endif
