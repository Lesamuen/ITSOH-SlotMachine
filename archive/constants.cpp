#include <random>
#include <string>
#include "constants.h"

std::random_device rd;

std::mt19937_64 rng = std::mt19937_64(rd());

std::uniform_int_distribution<int> randArcana = std::uniform_int_distribution<int>(0,21);

std::uniform_int_distribution<int> perc = std::uniform_int_distribution<int>(1,100);

std::uniform_int_distribution<int> spins = std::uniform_int_distribution<int>(1,10);

std::uniform_int_distribution<int> weight = std::uniform_int_distribution<int>(1,490);

std::uniform_int_distribution<int> death = std::uniform_int_distribution<int>(1,4);

extern const std::string arcana[22] = {
    "      The Fool      ", // 35  | 1:0.5
    "    The Magician    ", // 1   | magic item coupon
    " The High Priestess ", // 60  | 1:1
    "    The Empress     ", // 4   | 1:10
    "    The Emperor     ", // 10  | 1:5
    "   The Hierophant   ", // 55  | 1:0.75
    "     The Lovers     ", // 6.9 | 1:6.9
    "    The Chariot     ", // 10  | 1:5
    "      Strength      ", // 35  | 1:2
    "     The Hermit     ", // 45  | 1:0.5
    "  Wheel of Fortune  ", // 10  | bonus spins
    "      Justice       ", // 42  | 1:1.5
    "   The Hanged Man   ", // 12  | 1:0.1
    "       Death        ", // 31  | 1:10/1/0.1/0.01
    "     Temperance     ", // 60  | 1:1
    "     The Devil      ", // 1   | 1:75
    "     The Tower      ", // 1   | 1:-1
    "      The Star      ", // 4   | 1:15
    "      The Moon      ", // 1   | 1:?
    "      The Sun       ", // 2   | 1:25
    "     Judgement      ", // 60  | 1:1
    "     The World      "  // 4   | 1:10
};

extern const int weights[22] = {
    35,
    1,
    60,
    4,
    10,
    55,
    7,
    10,
    35,
    45,
    10,
    42,
    12,
    55,
    60,
    1,
    1,
    4,
    1,
    2,
    60,
    4
};

extern const float payouts[22] = {
    0.5,
    -4, // magic item coupon
    1,
    10,
    5,
    0.75,
    6.9,
    5,
    2,
    0.5,
    -2, // bonus spins
    1.5,
    0.1,
    -5, // transmogrify
    1,
    75,
    -1,
    15,
    -3, // mystery moon
    25,
    1,
    10
};