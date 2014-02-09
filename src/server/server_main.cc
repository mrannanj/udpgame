#include "server/server.h"
#include "common/util/die.h"

int main(int, char**) {
  Server server;
  server.serve();
  return 0;
}
