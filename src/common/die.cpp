#include <stdio.h>
#include <stdlib.h>

#include "common/die.h"

void die(const char* s)
{
  perror(s);
  exit(1);
}
