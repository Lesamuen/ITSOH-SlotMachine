#ifndef OUTPUT_H
#define OUTPUT_H

/*Prints current budget/earnings*/
void printBudget (const int*& coins, const float*& vouchers, const float*& omens, const int& numVouchers, const int& numOmens);

/*Simulate a reel spin from a starting position to an end position*/
void simSpin (int*& current, const int*& desired);

#endif