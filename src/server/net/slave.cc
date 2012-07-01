#include <iostream>
#include <unistd.h>
#include <assert.h>
#include <sys/select.h>

#include "server/net/slave.h"
#include "common/die.h"

void* slave(void* void_pipes)
{
  int* p = (int*) void_pipes;

  for (;;)
  {
    char c = 's';
    assert(1 == write(p[SLAVE_WRITE], &c, 1));

    fd_set rfds;
    FD_ZERO(&rfds);
    FD_SET(p[SLAVE_READ], &rfds);

    select(p[SLAVE_READ]+1, &rfds, nullptr, nullptr, nullptr);

    assert(1 == read(p[SLAVE_READ], &c, 1));
    if (c == 'm') {
      std::cout << "received mission!" << std::endl;
    }
    else if (c == 'q')
    {
      std::cout << "done!" << std::endl;
      break;
    }
    else
    {
      std::cout << "thread received unknown command" << std::endl;
    }
  }

  return NULL;
}
