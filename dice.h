#ifndef DICE_H
#define DICE_H

#include <random>

/*Roll (num) dice with (size) sides, and return the sum of the results.*/
int r (const int& num, const int& size, const std::mt19937& rng);

#endif