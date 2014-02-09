#pragma once

#include <ctime>
#include <chrono>
#include <ratio>

#include <SFML/System/Time.hpp>
#include <SFML/System/Clock.hpp>

class TickTimer {
public:
  TickTimer(sf::Int64);

  void newTick(sf::Time&);
  bool isTickTime(sf::Time&);

private:
  sf::Clock mClock;
  sf::Time mStart;
  sf::Time mTarget;
  sf::Time mTickTime;
};
