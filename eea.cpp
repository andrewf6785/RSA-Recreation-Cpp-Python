#include "eea.h"
// extended euclidian algorithm to find the modular inverse of "a" modulo modulus
// we store the modular inverse always as > 0
largeInt eea(const largeInt& a, const largeInt& modulus){
    largeInt r = modulus;
    largeInt newR = a % modulus;

    largeInt t = 0ULL;
    largeInt newT = 1ULL;

    while (newR != largeInt(0ULL)) {
        largeInt quotient = r / newR;

        largeInt nextR = r % newR;

        largeInt product = (quotient * newT) % modulus;
        largeInt nextT = modSubtract(t, product, modulus);

        r = newR;
        newR = nextR;

        t = newT;
        newT = nextT;
   
    }

    if (r != largeInt(1ULL)) {
        throw std::domain_error("Modular inverse does not exist");
    }

    return t;
}