#include "montgomeryConstant.h"

unsigned int montgomeryConstant(const largeInt& n)
{
    if (n < largeInt(3ULL) || (n.digits[0] & 1u) == 0) {
        throw std::invalid_argument("Modulus must be odd and >= 3");
    }

    // Find the inverse of the lowest byte modulo 256.
    unsigned int inverse = 1;

    while ((n.digits[0] * inverse) % 256u != 1u) {
        inverse += 2;
    }

    // Positive representation of -inverse modulo 256.
    return 256u - inverse;
}