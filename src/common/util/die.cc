#include <stdio.h>
#include <stdlib.h>

#include "common/util/die.h"

void die(const char* s) {
  perror(s);
  exit(EXIT_FAILURE);
}
