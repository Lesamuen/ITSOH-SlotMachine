#include <random>
#include <iostream>
#include "dice.h"

int r (const int& num, const int& size, const std::mt19937& rng)
{
	std::uniform_int_distribution<int> uid(1, size);
    int sum = 0;
    for (int i = 0; i < num; i++)
    {
        sum += uid(rng);
    }
    std::cout << sum << std::endl;
    return sum;
}