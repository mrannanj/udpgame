#include <signal.h>

#include "common/net/net_conf.h"
#include "server/server.h"

static int quit = 0;

void handle_sigint(int)
{
  quit = 1;
}

int main(void)
{
  signal(SIGINT, handle_sigint);

  Server server(SERVER_PORT, quit);
  server.listen();
  return 0;
}

