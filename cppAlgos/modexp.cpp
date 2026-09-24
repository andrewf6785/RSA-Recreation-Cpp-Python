#include "modexp.h"
largeInt modexp(largeInt a, largeInt b, const largeInt &c){
    largeInt result =1;
    a = a%c;

    while(b>0){
        if((b.digits[0] & 1u)!=0)result = (result *a)%c;

        a = (a*a)%c;
        b.divideBy2();
    }

    return result;
}