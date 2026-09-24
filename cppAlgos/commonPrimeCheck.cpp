#include "commonPrimeCheck.h"
bool commonPrimeCheck(largeInt &a){
    static constexpr unsigned int smallPrimes[] = {
    3,   5,   7,  11,  13,  17,  19,  23,  29,
    31,  37,  41,  43,  47,  53,  59,  61,  67,
    71,  73,  79,  83,  89,  97, 101, 103, 107,
    109, 113, 127, 131, 137, 139, 149, 151, 157,
    163, 167, 173, 179, 181, 191, 193, 197, 199,
    211, 223, 227, 229, 233, 239, 241, 251
    };
    
    for(int divisor : smallPrimes){
        unsigned int remainder = 0;
        for (std::size_t i = a.digits.size(); i-- > 0;) {
            remainder = (remainder * 256u + a.digits[i]) % divisor;
        }
        if(remainder ==0){
            return false;
        }
    }
    return true;
}