#include <signal.h>

#include "common/config.h"
#include "client/client.h"

static int quit = 0;

void handle_sigint(int)
{
  quit = 1;
}

int main(void)
{
  signal(SIGINT, handle_sigint);

  Client client(TICKS_PER_SEC, quit);
  client.keepalive();
  return 0;
}

