#include "keys.h"
std::tuple<largeInt,largeInt,largeInt> keys(){
    largeInt p, q;
    p=pickPrime(1024);
    q=pickPrime(1024);

    largeInt n = p*q;
    largeInt tn = (p-1)*(q-1);

    // e is chosen to be 65,537 because it is exposed to the public anyways, and this number
    // traditionally makes arithmetic easier. It can be any number coprime to tn, however.
    // (so any prime number)
    largeInt e = 65537;

    largeInt d = eea(e,tn);
    return {std::move(n), std::move(e), std::move(d)};



}