#ifndef PICKPRIME_H
#define PICKPRIME_H
#include "bigInt/bigInt.h"
#include "randomNumberGenerator/randomNumberGenerator.h"
#include "commonPrimeCheck.h"
#include "miller_rabin.h"

largeInt pickPrime(int bits);

#endif