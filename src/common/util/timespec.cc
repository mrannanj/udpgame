#include "common/util/timespec.h"

#define GIGA 1000000000
#define MEGA 1000000

std::ostream& operator<<(std::ostream& out, const timespec& ts)
{
  long t = (ts.tv_sec * GIGA + ts.tv_nsec)/MEGA;
  out << t << " ms";
  return out;
}

void normalize(timespec& ts)
{
  time_t secs = ts.tv_nsec / GIGA;
  ts.tv_nsec -= secs * GIGA;
  ts.tv_sec += secs;
  if (ts.tv_sec * ts.tv_nsec >= 0) return;
  if (ts.tv_nsec < 0)
  {
    ts.tv_sec -= 1;
    ts.tv_nsec += GIGA;
  }
  else
  {
    ts.tv_sec += 1;
    ts.tv_nsec -= GIGA;
  }
}

timespec& operator-=(timespec& lhs, timespec& rhs)
{
  lhs.tv_sec -= rhs.tv_sec;
  lhs.tv_nsec -= rhs.tv_nsec;
  normalize(lhs);
  return lhs;
}

timespec operator-(timespec& lhs, timespec& rhs)
{
  timespec ts(lhs);
  return ts -= rhs;
}


timespec& operator+=(timespec& lhs, timespec& rhs)
{
  lhs.tv_sec += rhs.tv_sec;
  lhs.tv_nsec += rhs.tv_nsec;
  normalize(lhs);
  return lhs;
}

timespec operator+(timespec& lhs, timespec& rhs)
{
  timespec ts(lhs);
  return ts += rhs;
}

int ts_comp(timespec& lhs, timespec& rhs)
{
  if (lhs.tv_sec > rhs.tv_sec)
    return 1;
  if (lhs.tv_sec < rhs.tv_sec)
    return -1;
  if (lhs.tv_nsec > rhs.tv_nsec)
    return 1;
  if (lhs.tv_nsec < rhs.tv_nsec)
    return -1;
  return 0;
}

bool operator<(timespec& lhs, timespec& rhs)
{
  return ts_comp(lhs, rhs) == -1;
}


