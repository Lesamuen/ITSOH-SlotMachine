#include <iostream>
#include <string>
#include "heavenordaining.h"

using namespace std;

int main ()
{
    string cont;
    cout << "Pull the lever! (y/y)" << endl;
    cin >> cont;
    while (cont != "n")
    {
        int gold;
        cout << "How much gold are you putting in?" << endl;
        cin >> gold;

        // do the thing
        spin(gold);

        cout << endl << "Pull the lever again! (y/y)" << endl;
        cin >> cont;
    }
    cout << "Thank you for your patronage, we hope to see you again soon :)" << endl;

    return 0;
}