#ifndef MONTGOMERYMODULAREXPO_H
#define MONTGOMERYMODULAREXPO_H
#include "bigInt/bigInt.h"
#include "montgomeryReduction.h"

largeInt montgomeryModexp(
    const largeInt& a,
    const largeInt& exponent,
    const largeInt& n,
    const largeInt& R,
    const largeInt& oneMont,
    unsigned int nPrime);

#endif