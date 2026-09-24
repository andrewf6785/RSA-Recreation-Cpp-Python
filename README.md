# RECREATING RSA ENCRYPTION

First I created a template for this project in python, and it went very smoothly because python automatically handles big integers all on its own.

This portion of this project can be found in `/pythonAlgos`.
`keys.py` calls `pickPrime.py` and `eea.py`. Run from `demo.py`.

`pickPrime` picks a prime using `secrets.randbits(1024)`, which, as you may guess picks a random number that is up to 1024 bits.
It then uses the Miller Rabin probabilistic primality test to determine if that number is prime

`eea.py` contains `gcdExtended`, which is the Extended Euclidean Algorithm.
This is used to find `d`, the modular inverse of `e`, modulo the totient function of `n`.

```text
n = p * q
φ(n) = (p - 1) * (q - 1)
e * d ≡ 1 (mod φ(n))
```

Python actually has a lot of native libraries that handle these operations, but I wanted to get more familiar with the math needed for this project so I implemented a lot of it in a more hands on manner.

## THE C++ IMPLEMENTATION

This part of the project started with me realizing that C++ has no native ability or library to handle big integers. That left me with the options of either getting one off the internet or trying to implement my own. It would sound better to say that I immediately tried to implement my own, but in all honesty I found the most simple BigInt implementation I could online at first and tried to use that. However, it was way too slow as it stored the integers in strings and operations were just taking too long. Using some of the math I learned later, this implementation likely would still have worked, but I decided to try and implement my own minimal BigInt class, mostly to get familiar with how these kinds of numbers can be stored.

### How it works:

`largeInt` stores a n bit integer in a vector of `uint8_t` variables, using little endian order to make arithmetic easier. Each byte represents a base-256 digit (with the most significant digit first).
Operations such as `+` and `-` are performed like regular step by step addition and subtraction, utilizing a carry variable or a borrow variable.

Operations like `*` and `/` again use familiar methods (although specifically, division uses binary long division), and division and modulus are implemented as `divmod` to avoid calling division again if the remainder is also required.

### Other Roadblocks:

When the initial demo was completed, it was very very slow as I was originally performing modular exponentiation (as in my decrypt and encrypt functions) for each iteration of Miller Rabin. This meant that Miller Rabin took far too long to complete its 40 rounds (a number that is itself slightly overkill to be sure that a number is prime, but it was the goal) for each selected prime. Because, on average, Miller Rabin will be called somewhere around 300 times for each execution, this wasn't working.

To speed this up, I implemented Montgomery reduction. During modular exponentiation, values are converted into Montgomery form and kept there throughout the repeated multiplications and squarings. Montgomery reduction replaces the expensive division-based reductions in that loop with multiplication, addition, and byte shifts. The final result is then converted back to an ordinary integer.

### Notes on Random Number Generation:

This current implementation uses std::mt19937_64 as a seed for the random number generator.
This is not technically cryptographically secure. 


### Compilation

Run make from /cppAlgos or the following command: 
g++ -O2 -o m bigInt/bigInt.cpp randomNumberGenerator/randomNumberGenerator.cpp decrypt.cpp demo.cpp eea.cpp encrypt.cpp keys.cpp miller_rabin.cpp modexp.cpp pickPrime.cpp commonPrimeCheck.cpp montgomeryConstant.cpp montgomeryModularExpo.cpp montgomeryReduction.cpp

Alternatively, run m.exe


