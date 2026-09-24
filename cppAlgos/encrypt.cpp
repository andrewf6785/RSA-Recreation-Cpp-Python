#include "encrypt.h"
largeInt encrypt(largeInt &a, largeInt &b, largeInt &c){
    return modexp(a,b,c);
}

