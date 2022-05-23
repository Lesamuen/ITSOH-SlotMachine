#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <random>
#include <string>

// Pseudo-random number generator: mersenne-twister prime 19937, 64-bit
extern std::random_device rd;
extern std::mt19937_64 rng;

// Random arcana number (0-21)
extern std::uniform_int_distribution<int> randArcana;

// Percentile roll (1-100)
extern std::uniform_int_distribution<int> perc;

// Random number of bonus spins (1-10)
extern std::uniform_int_distribution<int> spins;

// Weight roll (1-514)
extern std::uniform_int_distribution<int> weight;

// Random coin type (1-4)
extern std::uniform_int_distribution<int> death;

// List of arcana by number
extern const std::string arcana[22];

// List of weights by arcana number
extern const int weights[22];

// List of payouts by arcana number
extern const float payouts[22];

#endif