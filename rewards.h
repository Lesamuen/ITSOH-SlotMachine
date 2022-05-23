#ifndef REWARDS_H
#define REWARDS_H

#include <string>
#include <fstream>

struct Payout
{
    /*The type of payout.
    Current implementations:
    0 = Multiplier
    1 = Bonus Spin Trigger
    2 = Magic Item Voucher
    3 = Omen*/
    char payType;

    /*A value associated with payout, the use of which depends on the type of payout*/
    float payVal;
};

struct Symbol
{
    /*The name of the symbol*/
    std::string name;

    /*A weight value for the symbol, to determine its likelihood of appearing in the reel*/
    int weight;

    /*A list of payouts for this symbol, using struct Payout
    First payout is for 3 matches in any order,
    Second payout is for 4,
    Third payout is for all 5*/
    Payout payoutList[3];
};

/*Takes in a file and the amount of expected symbol inputs.
The syntax of the file should be as follows:

number of symbols
payoutChance (chance that payout is guaranteed to happen; more wins = more dopamine!!!)
name (20 characters max)
weight
payType (3 matches)
payVal (3 matches)
payType (4 matches)
payVal (4 matches)
payType (5 matches)
payVal (5 matches)
name
...

Otherwise, errors will most likely occur.

The first line, number of inputs, will be taken from the stream in the main function and stored there, then put back into the function.*/
Symbol* genPayoutList (std::ifstream& file, const int& symbols);

/*Used for debug/balancing purposes.
Per symbol, prints the chance for it to appear GIVEN THAT A PAYOUT HAPPENS, the expected value contribution, and its chance for attributed payouts to appear.
Prints the expected value in terms of a multiplier of inputted money
Magic item vouchers, omens, and bonus spins are included.*/
void expectedValue (const Symbol*& symbolList, const int& symbols, const float& payoutChance);

/*Spins the slots. Returns expected position, 5 int array of indices of symbolList.*/
int* spin (const Symbol*& symbolList, const int& symbols, const float& payoutChance);

/*Checks if an array of ints of size 5 has 3 or more matches
Returns 10*<matching num> + #matching, in a scuffed attempt to condense information into a single variable
Returns -1 if no match found*/
int checkMatches (const int*&);

#endif