#include "miller_rabin.h"
bool miller_rabin(const largeInt& n, int k)
{
    if (n == 2 || n == 3)
        return true;

    if (n < 2 || (n.digits[0] & 1u) == 0)
        return false;

    largeInt nMinusOne = n - 1;
    largeInt d = nMinusOne;
    int s = 0;

    while ((d.digits[0] & 1u) == 0) {
        d.divideBy2();
        ++s;
    }

    // Montgomery setup: once per candidate n.
    unsigned int nPrime = montgomeryConstant(n);

    largeInt R;
    R.digits.assign(n.digits.size() + 1, 0);
    R.digits.back() = 1;

    largeInt oneMont = R % n;

    for (int i = 0; i < k; ++i) {
        largeInt a;
        largeInt upper = n - 2;
        int bits = static_cast<int>(n.digits.size() * 8);

        do {
            a.digits = randomNumber(bits, false, false);

            // Removing the forced top bit permits leading zero bytes.
            while (a.digits.size() > 1 && a.digits.back() == 0) {
                a.digits.pop_back();
            }
        } while (a < 2 || a > upper);

        largeInt x =
            montgomeryModexp(a, d, n, R, oneMont, nPrime);

        if (x == 1 || x == nMinusOne)
            continue;

        bool passed = false;

        for (int r = 1; r < s; ++r) {
            // x is an ordinary integer here.
            x = (x * x) % n;

            if (x == nMinusOne) {
                passed = true;
                break;
            }

            if (x == 1)
                return false;
        }

        if (!passed)
            return false;
    }

    return true;
}  


// need to fix random number generator still, and then use it to fix the a selection 

