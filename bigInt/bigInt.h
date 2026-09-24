#ifndef BIGINT_H
#define BIGINT_H
#include <vector>
#include <string>
#include <cstdint>
#include <utility>
#include <stdexcept>

class largeInt {
public:
    // integers will be stored as a vector of 8 bit integers
    std::vector<uint8_t> digits;

    // stored in little endian order, which means the least signifigant bit is stored at the lowest memory address

    // constructors 
    largeInt(unsigned long long n =0);
    largeInt(const largeInt &a);

    // comparisons 
    friend bool operator<(const largeInt&a,const largeInt&b);
    friend bool operator>(const largeInt&a,const largeInt&b);
    friend bool operator>=(const largeInt&a,const largeInt&b);
    friend bool operator<=(const largeInt&a,const largeInt&b);
    friend bool operator==(const largeInt &a, const largeInt &b);
    friend bool operator!=(const largeInt &, const largeInt &);
    // printing (only works for "small" numbers rn)
    friend std::ostream &operator<<(std::ostream & out,const largeInt &a);
    

    // operators
    friend largeInt &operator+=(largeInt &a, const largeInt &b);
    friend largeInt operator+(const largeInt &a, const largeInt &b);

    friend largeInt &operator-=(largeInt&a,const largeInt &b);
    friend largeInt operator-(const largeInt& a,const largeInt&b);


    // division
    friend std::pair<largeInt, largeInt> divmod(const largeInt& a, const largeInt& b);

    friend largeInt& operator/=(largeInt& a, const largeInt& b);
    friend largeInt operator/(const largeInt &a,const largeInt &b);

    friend largeInt& operator%=(largeInt& a, const largeInt& b);
    friend largeInt operator%(const largeInt &a,const largeInt &b);


    friend largeInt& operator*=(largeInt& a, const largeInt& b);
    friend largeInt operator*(const largeInt&a,const largeInt&b);

    void divideBy2();


    // magnitude handling 
    friend largeInt modSubtract(const largeInt& a, const largeInt& b, const largeInt& modulus){
    largeInt x = a % modulus;
    largeInt y = b % modulus;

    if (!(x < y)) {
        return x - y;
    }

    return modulus - (y - x);
}

};

#endif