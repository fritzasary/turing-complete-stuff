#include <iostream>
#include <random>
#include <cstdint>
#include <algorithm>
#include <bitset>
#include "game.h"
#include "tictacfour.h"
#include "utils.h"

// rule: x always goes first and should always #x geq #o
// let xPlayer be true and xPlayer be false boolean values for turn



////  New construction of the tictactoe board representation utilizing bitboards
tictacfour::tictacfour(t4board initialState) : state(initialState) {}


bool tictacfour::turn() const {
    return countOnes(state.xBoard, 4) == countOnes(state.oBoard, 4);
}


void tictacfour::printState() const {
    std::vector<std::string> conv;
    uint16_t xdup = state.xBoard;
    uint16_t odup = state.oBoard;
    for (int i = 0; i < 16; i++) {
        uint16_t xBit = xdup & 1;
        uint16_t oBit = odup & 1;
        if (xBit == 1) {
            conv.push_back("x");
        }
        else if (oBit == 1) {
            conv.push_back("o");
        } else {
            conv.push_back(" ");
        }
        xdup >>= 1;
        odup >>= 1;
    }
    std::cout << std::endl;
    std::cout << "     -----------------" << std::endl;
    for (int i = 0; i < 4; i++) {
        std::cout << "     | " << conv[4*(3-i)+3]  << " | " << conv[4*(3-i)+2] << " | " << conv[4*(3-i)+1] << " | " << conv[4*(3-i)] << " | " << std::endl;
        std::cout << "     -----------------" << std::endl;
    }
    std::cout << std::endl;
}


// Generate possible moves in a given positions
std::vector<std::string> tictacfour::generateMoves() const {
    std::vector<std::string> possiblities;
    uint16_t sumBoard = state.xBoard | state.oBoard;
    for (int i = 0; i < 16; i++) {
        if ((sumBoard & 1) == 0) possiblities.push_back(std::to_string(15-i));
        sumBoard >>= 1;
    }
    return possiblities;
}

// input an index for the player of the board to make the next move
game* tictacfour::doMove(const std::string& move) const {
    t4board newState = state;
    uint16_t newMove = 1 << (15 - std::stoi(move));
    // because of rule and limitness in tic-tac-toe: #x geq #o
    // how many 1's appear in xBoard vs oBoard
    if (countOnes(state.xBoard, 4) > countOnes(state.oBoard, 4)) {
        newState.oBoard = state.oBoard | newMove;
    }
    else {
        newState.xBoard = state.xBoard | newMove;
    }
    return new tictacfour(newState);
}

//Primitive value is from the perspective of what the function is given
// return 0 if lose, 1 if win, 2 if tie, -1 if not primitive
gameResult tictacfour::primitiveValue() const {
    uint16_t sumBoard = state.xBoard | state.oBoard;
    // checks against winningPositions, uniqueness of binary representation ensures no overla
    for (uint16_t winPos : winningPositions_tt4) {
        if (subset(winPos, state.xBoard)) return WIN;
	if (subset(winPos, state.oBoard)) return LOSE;
    }
    if (sumBoard == 0b1111111111111111) return TIE;
    return UNDECIDED;
}
