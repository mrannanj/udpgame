#include <signal.h>

#include "common/config.h"
#include "client/client.h"

int main(void) {
  Client client(TICKS_PER_SEC);
  client.run();
}
