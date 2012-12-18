#include "common/util/fp.h"

#define FRACTION_SIZE 10

FP::FP(int i): val(i << FRACTION_SIZE)
{
}

FP::FP(float f): val((int)f)
{
}


