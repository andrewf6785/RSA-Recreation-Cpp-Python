#ifndef MILLERRABIN_H
#define MILLERRABIN_H
#include "bigInt/bigInt.h"
#include "randomNumberGenerator/randomNumberGenerator.h"
#include "montgomeryConstant.h"
#include "montgomeryModularExpo.h"

bool miller_rabin(const largeInt &n, int k);

#endif