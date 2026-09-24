#include "pickPrime.h"
largeInt pickPrime(int bits){
    largeInt possiblePrime;
    while(true){
        possiblePrime.digits = randomNumber(bits,true);
        if(!commonPrimeCheck(possiblePrime))continue;
        if(miller_rabin(possiblePrime,40))return possiblePrime;
    }
}