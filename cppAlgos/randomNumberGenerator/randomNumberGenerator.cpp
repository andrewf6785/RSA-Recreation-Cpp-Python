#include <stdint.h>
#include <random>
#include <limits>
#include <vector>
std::vector<uint8_t> randomNumber(int max_bits, bool odd = false, bool exactLength = true){
    std::vector<uint8_t> randomNum;  

    if(max_bits%8!=0){
        throw("max_bits or min_bits must be divisible by 8");
    }
    
    static thread_local std::mt19937_64 gen(
        std::random_device{}()
    );

    // produce a regular unsinged int (32 bit size) but small enough that it fits in a standard uint8_t
    std::uniform_int_distribution<unsigned int>distrib(0,255);
    for(int i=0; i<max_bits/8;++i){
        uint8_t b = static_cast<uint8_t>(distrib(gen));
        //set highest bit to ensure requested bit length
        if(exactLength && i==max_bits / 8 - 1){
            b |= (1u << 7);
        }
        if(odd && i ==0){
            //set lowest bit to ensure an odd number
            b |= 1u;    
        }
        
        randomNum.push_back(b);
    }   

    return randomNum;
}



// Arithmetic: start at index 0 and move upward.
// Normal human-readable printing: start at the highest index and move downward.


// NOTE : Not neccessarily crytographically secure for RSA key generation 