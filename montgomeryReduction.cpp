#include "montgomeryReduction.h"
// Requires:
//   n is odd and >= 3
//   nPrime comes from montgomeryConstant(n)
//   0 <= T < n * R, where R = 256^(n.digits.size())
largeInt montgomeryReduce(
    largeInt T,
    const largeInt& n,
    unsigned int nPrime)
{
    const std::size_t k = n.digits.size();

    // Enough space for the product and an extra carry byte.
    T.digits.resize(2 * k + 1, 0);

    for (std::size_t i = 0; i < k; ++i) {
        // Choose a multiplier that cancels byte i.
        unsigned int multiplier =
            (T.digits[i] * nPrime) & 0xFFu;

        unsigned int carry = 0;

        // Add multiplier * n, starting at byte i.
        for (std::size_t j = 0; j < k; ++j) {
            unsigned int value =
                T.digits[i + j]
                + multiplier * n.digits[j]
                + carry;

            T.digits[i + j] =
                static_cast<uint8_t>(value & 0xFFu);

            carry = value >> 8;
        }

        // Propagate any remaining carry.
        std::size_t position = i + k;

        while (carry != 0) {
            unsigned int value = T.digits[position] + carry;

            T.digits[position] =
                static_cast<uint8_t>(value & 0xFFu);

            carry = value >> 8;
            ++position;
        }
    }

    // The lowest k bytes are now zero.
    // Discarding them divides by R.
    largeInt result;
    result.digits.assign(T.digits.begin() + k, T.digits.end());

    while (result.digits.size() > 1 && result.digits.back() == 0) {
        result.digits.pop_back();
    }

    // Under the input bound, the result is less than 2*n.
    if (!(result < n)) {
        result -= n;
    }

    return result;
}