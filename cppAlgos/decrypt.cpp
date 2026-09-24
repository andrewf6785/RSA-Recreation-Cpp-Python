#include "decrypt.h"
largeInt decrypt(largeInt &a, largeInt &b, largeInt &c){
    return modexp(a,b,c);
}