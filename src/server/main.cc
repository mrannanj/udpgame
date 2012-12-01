#include <signal.h>

#include "common/config.h"
#include "server/server.h"

static int quit = 0;

void handle_sigint(int)
{
  quit = 1;
}

int main(void)
{
  signal(SIGINT, handle_sigint);

  Server server(TICKS_PER_SEC, quit);
  server.listen();
  return 0;
}

