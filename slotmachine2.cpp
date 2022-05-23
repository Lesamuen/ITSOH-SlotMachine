#include <iostream>
#include <string>
#include <fstream>
#include "rewards.h"

using namespace std;

int main ()
{
    string input;
    // Current reel state; 5 reels
    int reel[5];
    // Keep track of 0 = pp, 1 = gp, 2 = sp, 3 = cp
    int money[4];
    // Keep track of won magic items and their value in gp.
    int numVouchers = 0;
    float vouchers[0];
    // Keep track of omens and their "value in gp"
    int numOmens = 0;
    float omens[0];
    // Initialize reel
    ifstream slots = ifstream("reel.cfg");
    getline(slots, input);
    int numSymbols = stoi(input);
    // Payouts have a weighted guaranteed chance of appearing, for more serotonin
    getline(slots, input);
    float payoutChance = stof(input);
    // Default payout chance to 0.5
    if (payoutChance > 1 || payoutChance < 0)
    {
        payoutChance = 0.5;
    }
    Symbol* symbolList = genPayoutList(slots, numSymbols);
    slots.close();

    cout << "Hello and welcome to the Devil's Palace!\n"
    "Our slot machines are new and improved, and you can win bigger than ever before!\n\n"
    "How much money do you have on you?\n"
    "Platinum: ";
    // Init budget; if non-int is inputted, then default to 0.
    getline(cin, input);
    try
    {
        money[0] = stoi(input);
    }
    catch (...)
    {
        money[0] = 0;
    }
    cout << "Gold: ";
    getline(cin, input);
    try
    {
        money[1] = stoi(input);
    }
    catch (...)
    {
        money[1] = 0;
    }
    cout << "Silver: ";
    getline(cin, input);
    try
    {
        money[2] = stoi(input);
    }
    catch (...)
    {
        money[2] = 0;
    }
    cout << "Copper: ";
    getline(cin, input);
    try
    {
        money[3] = stoi(input);
    }
    catch (...)
    {
        money[3] = 0;
    }
    
    cout << "\nGreat! Now, would you like to pull the lever? (y) ";

    inputLoop:
    /*Possible commands:
    LITERALLY ANYTHING ELSE - pulls the lever
    n/no - does not pull the lever, and exits the program
    rf/refresh - refreshes reel manually, in case config is updated while program is open
    ev/expectedvalue - prints calculated stats regarding the current reel config
    69 - nice*/
    getline(cin, input);
    system("cls");
    if (input == "n" || input == "N" || input == "no" || input == "NO")
    {
        exit:
        cout << "Alright, then. May the Wheel bless you! The Devil's Palace thanks you for your continued patronage!\n";
        delete[] symbolList;
        return 0;
    }
    else if (input == "rf" || input == "RF" || input == "refresh" || input == "REFRESH")
    {
        slots.open("reel.cfg");
        getline(slots, input);
        numSymbols = stoi(input);
        getline(slots, input);
        payoutChance = stof(input);
        if (payoutChance > 1 || payoutChance < 0)
        {
            payoutChance = 0.5;
        }
        // Clear old from heap, then replace with new
        delete[] symbolList;
        symbolList = genPayoutList(slots, numSymbols);
        slots.close();
        cout << "Reel updated!\n";
    }
    else if (input == "ev" || input == "EV" || input == "expectedvalue"|| input == "EXPECTEDVALUE")
    {
        cout << "\n";
        expectedValue(symbolList, numSymbols, payoutChance);
    }
    else if (input == "69")
    {
        cout << "nice\n";
    }
    else
    {
        // If out of money, ask if they want to take a loan :)
        // If not, they leave
        if (money[0] == 0 && money[1] == 0 && money[2] == 0 && money[3] == 0)
        {
            cout << "It appears you are out of money!\n"
            "Would you like to take a loan? (y) ";
            getline(cin, input);
            if (input == "n" || input == "N" || input == "no" || input == "NO")
            {
                goto exit;
            }
            else
            {
                cout << "Then, here's 50 gold pieces! Make sure you pay it back!\n"
                "(or we'll make you.)\n\n";
                money[1] += 50;
            }
        }
        
        // Print current earnings
    }

    cout << "\nPull the lever again! (y) ";

    // Repeat the slot machine
    goto inputLoop;
}