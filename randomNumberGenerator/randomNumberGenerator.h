#ifndef RANDOMNUMBERGENERATOR_H
#define RANDOMNUMBERGENERATOR_H
#include <stdint.h>
#include <vector>

std::vector<uint8_t> randomNumber(int max_bits, bool odd = false, bool exactLength = true);

#endif