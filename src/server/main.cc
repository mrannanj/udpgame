#include <signal.h>

#include "server/server.h"

#define PORT 4666

static int quit = 0;

void handle_sigint(int)
{
  quit = 1;
}

int main(void)
{
  signal(SIGINT, handle_sigint);

  Server server(PORT, quit);
  server.listen();
  return 0;
}

