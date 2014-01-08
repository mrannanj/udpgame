#include <signal.h>
#include <cstring>
#include <unistd.h>

#include "client/client.h"

int main(int, char** argv) {
  if (strcmp(argv[0], "/usr/bin/udpgame_client"))
    chdir("/usr/share/udpgame");
  Client client;
  client.run();
}
