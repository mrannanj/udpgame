#include <iostream>

#include "server/net/slave.h"

void* slave(void* /* arg */)
{
  std::cout << "slave" << std::endl;
  return NULL;
}
