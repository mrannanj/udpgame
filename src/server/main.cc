#include "server/net/master.h"

int main(void)
{
  Master master;
  master.Init();
  master.Serve();
  return 0;
}
