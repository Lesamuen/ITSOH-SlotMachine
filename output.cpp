#include <string>
#include <iostream>
#include "output.h"

void printBudget (const int*& coins, const float*& vouchers, const float*& omens, const int& numVouchers, const int& numOmens)
{
    std::cout << "Your current budget:\n";
    if (coins[0] == 0 && coins[1] == 0 && coins[2] == 0 && coins[3] == 0)
    {
        std::cout << " - No money :(\n";
    }
    else
    {
        if (coins[0] != 0)
        {
            std::cout << " - " << coins[0] << "pp\n";
        }
        if (coins[1] != 0)
        {
            std::cout << " - " << coins[1] << "gp\n";
        }
        if (coins[2] != 0)
        {
            std::cout << " - " << coins[2] << "sp\n";
        }
        if (coins[3] != 0)
        {
            std::cout << " - " << coins[3] << "cp\n";
        }
    }
    if (numVouchers > 0 || numOmens > 0)
    {
        std::cout << "In your pocket you also have:\n";
    }
    if (numVouchers > 0)
    {
        for (int i = 0; i < numVouchers; i++)
        {
            std::cout << " - A Magician-emblazoned voucher with \'" << (int)vouchers[i] << " gp\' written on it.\n";
        }
    }
    if (numOmens > 0)
    {
        for (int i = 0; i < numOmens; i++)
        {
            std::cout << " - A silver coin that has appeared in your pocket, printed with a simple \'" << (int)omens[i] << "\'.\n";
        }
    }
}