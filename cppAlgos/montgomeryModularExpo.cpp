#include "montgomeryModularExpo.h"
largeInt montgomeryModexp(
    const largeInt& a,
    const largeInt& exponent,
    const largeInt& n,
    const largeInt& R,
    const largeInt& oneMont,
    unsigned int nPrime){
    largeInt base = (a * R) % n; // Convert a into Montgomery form
    largeInt result = oneMont;   // Montgomery form of 1
    largeInt remaining = exponent;

    while (remaining != 0) {
        if ((remaining.digits[0] & 1u) != 0) {
            result = montgomeryReduce(result * base, n, nPrime);
        }

        remaining.divideBy2();

        if (remaining != 0) {
            base = montgomeryReduce(base * base, n, nPrime);
        }
    }

    // Return an ordinary integer.
    return montgomeryReduce(result, n, nPrime);
    }