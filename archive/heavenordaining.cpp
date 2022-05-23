#include <iostream>
#include <string>
#include <thread>
#include <chrono>
#include "constants.h"
#include "heavenordaining.h"

void printSlots (int* slots)
{
    std::cout << "====================================================================" << std::endl
    << "||                    ||                    ||                    ||" << std::endl
    << "||" << arcana[slots[0]] << "||" << arcana[slots[1]] << "||" << arcana[slots[2]] << "||" << std::endl
    << "||                    ||                    ||                    ||" << std::endl
    << "====================================================================" << std::endl;
}

void spin (int gold)
{
    int rolls[3];
    
    // Fancy spinning that doesn't do anything
    for (int i = 1; i <= 49; i++)
    {
        rolls[0] = randArcana(rng);
        rolls[1] = randArcana(rng);
        rolls[2] = randArcana(rng);
        system("cls");
        printSlots(rolls);
        std::this_thread::sleep_for(std::chrono::milliseconds((int)((float)1/(50-i)*1000)));
    }

    // The actual big money (final spin)
    // 50% chance of getting nothing
    if (perc(rng) > 50){
        // 3 random, not equal
        rolls[0] = randArcana(rng);
        rolls[1] = randArcana(rng);
        do
        {
            rolls[2] = randArcana(rng);
        }
        while (rolls[2] == rolls[1]);
    }
    // 50% chance of getting something
    else
    {
        // 3 equals, weighted roll
        int weightedRoll = weight(rng);
        int i;
        for (i = 0; i < 22; i++)
        {
            weightedRoll -= weights[i];
            if (weightedRoll <= 0) break;
        }
        rolls[0] = i;
        rolls[1] = i;
        rolls[2] = i;
    }
    system("cls");
    printSlots(rolls);

    if (rolls[0] == rolls[1] && rolls[1] == rolls[2])
    {
        std::cout << std::endl;
        // Call payout check, AND check for bonus spins
        if (payoutCheck(rolls[0], gold))
        {
            int bonusSpins = spins(rng);
            std::cout << std::endl << "Congratulations! You have won " << bonusSpins << " bonus spins!" << std::endl;
            // List of rewards gained from bonus spins
            int* bonusResults = new int[bonusSpins];

            std::this_thread::sleep_for(std::chrono::seconds(3));

            for (int i = 0; i < bonusSpins; i++)
            {
                bonusResults[i] = bonusSpin();
                if (bonusResults[i] != -1 && payouts[bonusResults[i]] == -2)
                {
                    // Stacking bonus spins
                    int plusSpins = spins(rng);
                    std::cout << std::endl << "Congratulations! You have won " << plusSpins << " more bonus spins!" << std::endl;
                    bonusSpins += plusSpins;

                    // Expand bonusResults array
                    int* newResults = new int[bonusSpins];
                    for (int j = 0; j <= i; j++)
                    {
                        newResults[j] = bonusResults[j];
                    }
                    delete[] bonusResults;
                    bonusResults = newResults;
                    
                    std::this_thread::sleep_for(std::chrono::seconds(3));
                }
                std::this_thread::sleep_for(std::chrono::seconds(2));
            }

            // Iterate through bonus spin results
            std::cout << std::endl;
            payoutCheck(bonusResults, bonusSpins, gold);
        }
    }
    else
    {
        std::cout << std::endl << "You didn't win this time. Better luck next spin!" << std::endl;
    }
}

int bonusSpin ()
{
    int rolls[3];

    // Fancy spinning that doesn't do anything
    for (int i = 1; i <= 49; i++)
    {
        rolls[0] = randArcana(rng);
        rolls[1] = randArcana(rng);
        rolls[2] = randArcana(rng);
        system("cls");
        printSlots(rolls);
        std::this_thread::sleep_for(std::chrono::milliseconds((int)((float)1/(50-i)*250)));
    }

    // The actual big money (final spin)
    // 45% chance of getting nothing
    if (perc(rng) > 55){
        // 3 random, not equal
        rolls[0] = randArcana(rng);
        rolls[1] = randArcana(rng);
        do
        {
            rolls[2] = randArcana(rng);
        }
        while (rolls[2] == rolls[1]);
    }
    // 55% chance of getting something
    else
    {
        // 3 equals, weighted roll
        int weightedRoll = weight(rng);
        int i;
        for (i = 0; i < 22; i++)
        {
            weightedRoll -= weights[i];
            if (weightedRoll <= 0) break;
        }
        rolls[0] = i;
        rolls[1] = i;
        rolls[2] = i;
    }
    system("cls");
    printSlots(rolls);

    if (rolls[0] == rolls[1] && rolls[1] == rolls[2])
    {
        return rolls[0];
    }
    else
    {
        return -1;
    }
}

bool payoutCheck (int roll, int gold)
{
    float payout = payouts[roll];
    if (payout == -2)
    {
        return true;
    }
    else if (payout == -3)
    {
        std::cout << "A sudden chill runs down your spine. Best to go to the next spin." << std::endl;
    }
    else if (payout == -4)
    {
        std::cout << "Instead of coins, a ticket prints out from the slot machine." << std::endl;
        std::cout << "It's a...coupon, for a free magic item at your nearest Temple of The Magician?" << std::endl;
    }
    else if (payout == -1)
    {
        std::cout << "You didn't win this time. Better luck next sp--" << std::endl;
        std::cout << "Wait...why does your coin bag feel lighter? " << gold << " gold pieces lighter, in fact." << std::endl;
    }
    else if (payout == -5)
    {
        std::cout << "The machine rumbles a bit, and out comes the same amount of coins." << std::endl;
        int coinType = death(rng);
        if (coinType == 4)
        {
            std::cout << "Amazingly, they are the gleaming white of platinum!" << std::endl;
        }
        else if (coinType == 3)
        {
            std::cout << "For some reason, they look a lot shinier than when you put them in." << std::endl;
        }
        else if (coinType == 2)
        {
            std::cout << "Amazingly, they are the gleaming white of--oh, it's just silver." << std::endl;
        }
        else
        {
            std::cout << "They are a strange shade of yellow. Almost...brown. Very copper-like." << std::endl;
        }
    }
    else
    {
        float goldPayout = payout*gold;
        float silverPayout = (goldPayout - (int)goldPayout)*10;
        float copperPayout = (silverPayout - (int)silverPayout)*10;
        std::cout << "A heap of coins pours out from the slot machine! There are " << (int)goldPayout << " gold";
        if ((int)silverPayout > 0 && (int)copperPayout > 0)
        {
            std::cout << ", " << (int)silverPayout << " silver, and " << (int)copperPayout << " copper";
        }
        else
        {
            if ((int)silverPayout > 0)
            {
                std::cout << " and " << (int)silverPayout << " silver";
            }
            else if ((int)copperPayout > 0)
            {
                std::cout << " and " << (int)copperPayout << " copper";
            }
        }
        std::cout << " pieces." << std::endl;
    }
    return false;
}

void payoutCheck (int* rolls, int size, int gold)
{
    // Tally up all rewards first
    int specials[3] = {0,0,0};
    float totalPayout = 0;
    for (int i = 0; i < size; i++)
    {
        if (rolls[i] == -1) continue;
        float payout = payouts[rolls[i]];
        if (payout == -1)
        {
            // Lose Money
            specials[0]++;
        }
        else if (payout == -4)
        {
            // Magic Item
            specials[1]++;
        }
        else if (payout == -3)
        {
            // "Nothing"
            specials[2]++;
        }
        else if (payout == -5)
        {
            // Death; Transmutation
            int coinType = death(rng);
            if (coinType = 4)
            {
                totalPayout += 10;
            }
            else if (coinType = 3)
            {
                totalPayout += 1;
            }
            else if (coinType = 2)
            {
                totalPayout += 0.1;
            }
            else
            {
                totalPayout += 0.01;
            }
        }
        else if (payout != -2)
        {
            totalPayout += payout;
        }
    }

    // Announce rewards
    float goldPayout = totalPayout*gold;
    float silverPayout = (goldPayout - (int)goldPayout)*10;
    float copperPayout = (silverPayout - (int)silverPayout)*10;
    std::cout << "A pile of coins pours out from the slot machine! There are " << (int)goldPayout << " gold";
    if ((int)silverPayout > 0 && (int)copperPayout > 0)
    {
        std::cout << ", " << (int)silverPayout << " silver, and " << (int)copperPayout << " copper";
    }
    else
    {
        if ((int)silverPayout > 0)
        {
            std::cout << " and " << (int)silverPayout << " silver";
        }
        else if ((int)copperPayout > 0)
        {
            std::cout << " and " << (int)copperPayout << " copper";
        }
    }
    std::cout << " pieces." << std::endl;
    // Tower
    if (specials[0] > 0)
    {
        std::cout << "However, as you go for your coin purse, you realize it is lighter. " << (-1*specials[0]*gold) << " gold pieces lighter, in fact." << std::endl;
    }
    // Magician
    if (specials[1] > 0)
    {
        std::cout << "Along with the coins comes " << specials[1] << ((specials[1] == 1) ? " ticket" : " identical tickets") << " for free magic items at your nearest Temple of The Magician!" << std::endl;
    }
    // Moon
    if (specials[2] > 0)
    {
        std::cout << "During that entire ordeal, however, " << specials[2] << ((specials[2] == 1) ? " ominous shiver runs" : " ominous shivers run") << " down your spine. Odd." << std::endl;
    }
}