#ifndef HEAVENORDAINING_H
#define HEAVENORDAINING_H

// Prints slot machine view
void printSlots (int* slots);

// Spins slot machine once
void spin (int gold);

// Spins slot machine once, but a lot faster, and returns the result
int bonusSpin ();

// Prints results, and returns true if bonus spins; false otherwise
bool payoutCheck (int roll, int gold);

// Same as above, but for list of spins, and ignores bonus spins
void payoutCheck (int* rolls, int size, int gold);

#endif