#include <iostream>
#include <random>
#include "utils.h"





/* need to add dim = n for the size dimenision of the tictactoe board*/
int countOnes(uint16_t num, int dim) {
    int cnt = 0;
    for (int i = 0; i < dim*dim; i++) {
        if ((num & 1) == 1) cnt++;
        num >>= 1;
    }
    return cnt;
}

bool subset(uint16_t sub,  uint16_t super) {
    return (sub & super) == sub;
}

int getRandomInt(int min, int max) {
    static std::random_device rd;  // Seed source
    static std::mt19937 gen(rd()); // Mersenne Twister engine seeded with rd()

    std::uniform_int_distribution<> dist(min, max);
    return dist(gen);
}