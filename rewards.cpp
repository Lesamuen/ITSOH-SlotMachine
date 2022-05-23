#include <string>
#include <fstream>
#include <iostream>
#include <cmath>
#include <random>
#include "rewards.h"
#include "dice.h"

Symbol* genPayoutList (std::ifstream& file, const int& symbols)
{
    // Initialize input var
    std::string input;
    
    // Initialize every symbol
    Symbol* symbolList = new Symbol[symbols];
    for (int i = 0; i < symbols; i++)
    {
        std::getline(file, symbolList[i].name);
        std::getline(file, input);
        symbolList[i].weight = std::stoi(input);

        // Initialize payouts
        for (int j = 0; j < 3; j++)
        {
            std::getline(file, input);
            symbolList[i].payoutList[j].payType = std::stoi(input);
            std::getline(file, input);
            symbolList[i].payoutList[j].payVal = std::stof(input);
        }
    }

    return symbolList;
}

void expectedValue (const Symbol*& symbolList, const int& symbols, const float& payoutChance)
{
    // Init
    float expectedValue = 0;
    float totalWeight = 0;
    float expectedBonusSpins = 0;
    float unmodPayoutChance = 0;
    float payoutChances[symbols*3];

    // Calculate total weight first
    for (int i = 0; i < symbols; i++)
    {
        totalWeight += symbolList[i].weight;
    }

    // Calculate UNMODIFIED chances for every payout (when payout is not guaranteed)
    for (int i = 0; i < symbols; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            // (chance of appear)^n * (chance of not appear)^(5-n), where n = j + 3, for ONE PERMUTATION
            // Num of permutations is 5 choose n; for n = 0, 10, for n = 1, 5, for n = 2, 1
            payoutChances[i * 3 + j] = std::pow((symbolList[i].weight / totalWeight), j + 3) * std::pow(((totalWeight - symbolList[i].weight) / totalWeight), 2 - j);
            if (j == 0)
            {
                payoutChances[i * 3 + j] *= 10;
            }
            else if (j == 1)
            {
                payoutChances[i * 3 + j] *= 5;
            }
        }
    }

    // Calculate unmodified total payout chance
    for (int i = 0; i < symbols*3; i++)
    {
        unmodPayoutChance += payoutChances[i];
    }

    // Modify all chances such that total payout chance becomes as is weighted
    for (int i = 0; i < symbols*3; i++)
    {
        payoutChances[i] *= payoutChance / unmodPayoutChance;
    }

    // Calculate expected values for all symbols and payouts
    for (int i = 0; i < symbols; i++)
    {
        float symbolChance = 0;
        float symbolEV = 0;
        float symbolBonusEV = 0;

        std::cout << symbolList[i].name << "\n";
        // Calculate and print payout stats
        for (int j = 0; j < 3; j++)
        {
            symbolChance += payoutChances[i * 3 + j];
            float payoutEV = payoutChances[i * 3 + j] * symbolList[i].payoutList[j].payVal;
            if (symbolList[i].payoutList[j].payType == 1)
            {
                symbolBonusEV += payoutEV;
                std::cout << " - " << j + 3 << "-Match Chance: " << payoutChances[i * 3 + j] << "\n"
                << " - " << j + 3 << "-Match Expected Bonus Spins: " << payoutEV << "\n";
            }
            // Multiplier acts normally for omens and magic items
            else
            {
                symbolEV += payoutEV;
                std::cout << " - " << j + 3 << "-Match Chance: " << payoutChances[i * 3 + j] << "\n"
                << " - " << j + 3 << "-Match Expected Payout: " << payoutEV << "\n";
            }
        }

        expectedValue += symbolEV;
        expectedBonusSpins += symbolBonusEV;
        std::cout << " - Symbol Payout Chance: " << symbolChance << "\n";
        if (symbolEV != 0)
        {
            std::cout << " - Symbol Expected Payout: " << symbolEV << "\n";
        }
        if (symbolBonusEV != 0)
        {
            std::cout << " - Symbol Expected Bonus Spins: " << symbolBonusEV << "\n";
        }
    }

    // Print total chance of a payout
    std::cout << "TOTAL Payout Chance: " << payoutChance << "\n"
    // Print expected bonus spins
    << "Expected Value for Bonus Spins: " << expectedBonusSpins << "\n";

    // Current expected value does not include bonus spins; recursively account for bonus spins until error disappears outside of float type's scope
    // If expected bonus spins per spin is greater than or equal to 1, then mathematically the expected value will spiral off into infinity.
    if (expectedBonusSpins >= 1)
    {
        std::cout << "TOTAL Expected Payout Multiplier: INFINITY" << std::endl;
    }
    else{
        while (expectedBonusSpins > 0)
        {
            expectedValue += expectedValue * expectedBonusSpins;
            expectedBonusSpins *= expectedBonusSpins;
        }
        std::cout << "TOTAL Expected Payout Multiplier: " << expectedValue << std::endl;
    }
}

int* spin (const Symbol*& symbolList, const int& symbols, const float& payoutChance, const std::mt19937& rng)
{
    // See if payout happens or not
    if (r(1, 100, rng) < 100 * payoutChance)
    {
        
    }
    else
    {

    }
}