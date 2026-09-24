#include "bigInt.h"
#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>
#include <string>

//construtors 

largeInt::largeInt(unsigned long long n){
    if (n == 0) {
        digits.push_back(0);
        return;
    }

    while (n > 0) {
        digits.push_back(static_cast<uint8_t>(n & 0xFF)); //extract the lowest 8 bits 
        n >>= 8; //shift right 8 bits
    }
}
// each digit in n is 8 bits, or a byte, which can be extracted using the above method
// 8 bit bytes reconstructed as (in little endian order) : digits[0](256)^0 + digits[1](256)^1...digits[n]^n
    // at which point the benefits of little endian order become obvious 


largeInt::largeInt(const largeInt &a){
    digits = a.digits;
}





// comparisons 

bool operator<(const largeInt&a,const largeInt&b){
    int n = size(a.digits), m = size(b.digits);
    if(n!=m){
        return n<m;
    }
    while(n--){
        if(a.digits[n]!=b.digits[n]){
            return a.digits[n]<b.digits[n];
        }
    }
    return false;

}

bool operator>(const largeInt&a,const largeInt&b){
    return b<a;
}

bool operator>=(const largeInt&a,const largeInt&b){
    return !(a<b);
}

bool operator<=(const largeInt&a,const largeInt&b){
    return !(a>b);
}

bool operator==(const largeInt &a, const largeInt &b){
    return a.digits==b.digits;
}

bool operator!=(const largeInt &a, const largeInt &b){
    return !(a.digits==b.digits);
}


// operations 
largeInt& operator+=(largeInt& a, const largeInt& b){
    std::size_t maximum =
        std::max(a.digits.size(), b.digits.size());

    a.digits.resize(maximum, 0);

    unsigned int carry = 0;

    for (std::size_t i = 0; i < maximum; ++i) {
        unsigned int bDigit =
            (i < b.digits.size()) ? b.digits[i] : 0;

        unsigned int sum =
            static_cast<unsigned int>(a.digits[i])
            + bDigit
            + carry;

        a.digits[i] = static_cast<uint8_t>(sum & 0xFF);

        carry = sum >> 8;
    }

    if (carry > 0) {
        a.digits.push_back(static_cast<uint8_t>(carry));
    }

    return a;
}

largeInt operator+(const largeInt &a, const largeInt &b){
    largeInt temp;
    temp = a;
    temp +=b;
    return temp;
}


largeInt& operator-=(largeInt& a, const largeInt& b)
{
    if (a < b) {
        throw std::underflow_error("largeInt cannot become negative");
    }

    unsigned int borrow = 0;

    for (std::size_t i = 0; i < a.digits.size(); ++i) {
        unsigned int bDigit =
            (i < b.digits.size()) ? b.digits[i] : 0;

        int difference =
            static_cast<int>(a.digits[i])
            - static_cast<int>(bDigit)
            - static_cast<int>(borrow);

        if (difference < 0) {
            difference += 256;
            borrow = 1;
        } else {
            borrow = 0;
        }

        a.digits[i] = static_cast<uint8_t>(difference);
    }

    // Remove unnecessary most-significant zero bytes.
    while (a.digits.size() > 1 && a.digits.back() == 0) {
        a.digits.pop_back();
    }

    return a;
}

largeInt operator-(const largeInt& a,const largeInt&b){
    largeInt temp;
    temp = a;
    temp -= b;
    return temp;
}



largeInt& operator*=(largeInt& a, const largeInt& b){
    largeInt result;
    result.digits.assign(a.digits.size() + b.digits.size(), 0);

    for (std::size_t i = 0; i < a.digits.size(); ++i) {
        unsigned int carry = 0;

        for (std::size_t j = 0; j < b.digits.size(); ++j) {
            unsigned int value =
                static_cast<unsigned int>(a.digits[i]) * b.digits[j]
                + result.digits[i + j]
                + carry;

            result.digits[i + j] =
                static_cast<uint8_t>(value & 0xFF);

            carry = value >> 8;
        }

        result.digits[i + b.digits.size()] =
            static_cast<uint8_t>(carry);
    }

    while (result.digits.size() > 1 && result.digits.back() == 0) {
        result.digits.pop_back();
    }

    a = result;
    return a;
}


largeInt operator*(const largeInt&a,const largeInt&b){
    largeInt temp;
    temp = a;
    temp *= b;
    return temp;
}



// divisions 
std::pair<largeInt, largeInt>
divmod(const largeInt& a, const largeInt& b)
{
    if (b.digits.size() == 1 && b.digits[0] == 0) {
        throw std::domain_error("Division by zero");
    }

    largeInt quotient;
    largeInt remainder;
    quotient.digits.assign(a.digits.size(), 0);

    for (std::size_t i = a.digits.size(); i > 0; --i) {
        for (int bit = 7; bit >= 0; --bit) {
            // Bring down the next bit.
            remainder += remainder;
            remainder.digits[0] |=
                (a.digits[i - 1] >> bit) & 1u;

            if (!(remainder < b)) {
                remainder -= b;
                quotient.digits[i - 1] |= (1u << bit);
            }
        }
    }

    while (quotient.digits.size() > 1 && quotient.digits.back() == 0) {
        quotient.digits.pop_back();
    }

    return {std::move(quotient), std::move(remainder)};
}

largeInt& operator/=(largeInt& a, const largeInt& b)
{
    auto result = divmod(a, b);
    a = std::move(result.first);   // Quotient
    return a;
}

largeInt operator/(const largeInt &a,const largeInt &b){
    largeInt temp;
    temp =a;
    temp /=b;
    return temp;
}

void largeInt::divideBy2(){
    unsigned int carry = 0;

    for (std::size_t i = digits.size(); i-- > 0;) {
        unsigned int current = (carry << 8) | digits[i];

        digits[i] = static_cast<uint8_t>(current / 2);
        carry = current % 2;
    }

    while (digits.size() > 1 && digits.back() == 0) {
        digits.pop_back();
    }
}

largeInt& operator%=(largeInt& a, const largeInt& b)
{
    auto result = divmod(a, b);
    a = std::move(result.second);  // Remainder
    return a;
}
largeInt operator%(const largeInt &a,const largeInt &b){
    largeInt temp;
    temp =a;
    temp %= b;
    return temp;
}









std::ostream& operator<<(std::ostream& out, const largeInt& a)
{
    std::vector<uint8_t> temp = a.digits;
    std::string decimal;

    // Remove unnecessary most-significant zeros.
    while (!temp.empty() && temp.back() == 0) {
        temp.pop_back();
    }

    if (temp.empty()) {
        return out << '0';
    }

    while (!temp.empty()) {
        unsigned int remainder = 0;

        // Divide the entire number by 10.
        for (std::size_t i = temp.size(); i-- > 0;) {
            unsigned int current = remainder * 256u + temp[i];

            temp[i] = static_cast<uint8_t>(current / 10u);
            remainder = current % 10u;
        }

        // The remainder is the next decimal digit, starting at the ones.
        decimal.push_back(static_cast<char>('0' + remainder));

        while (!temp.empty() && temp.back() == 0) {
            temp.pop_back();
        }
    }

    std::reverse(decimal.begin(), decimal.end());
    return out << decimal;
}


