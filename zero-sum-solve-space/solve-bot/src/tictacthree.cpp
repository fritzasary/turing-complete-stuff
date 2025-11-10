#include <iostream>
#include <cstdint>
#include <algorithm>
#include "game.h"
#include "tictacthree.h"
#include "utils.h"

// rule: x always goes first and should always #x geq #o
// let xPlayer be true and xPlayer be false boolean values for turn



////  New construction of the tictactoe board representation utilizing bitboards
tictacthree::tictacthree(t3board initialState) : state(initialState) {}



/////////////////////////////////////////////////////////////////
////////////////////// Core Function Begin //////////////////////
/////////////////////////////////////////////////////////////////



// return true if first player (X) turn, and second player (O) otherwise
bool tictacthree::turn() const {
    return countOnes(state.xBoard, 3) == countOnes(state.oBoard, 3);
}

// print the position of the current state

void tictacthree::printState() const {
    std::vector<std::string> conv;
    uint16_t xdup = state.xBoard;
    uint16_t odup = state.oBoard;
    for (int i = 0; i < 9; i++) {
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
    std::cout << "     -------------" << std::endl;
    for (int i = 0; i < 3; i++) {

        // Need to fix this part
        std::cout << "     | " << conv[3*(2-i)+2]  << " | " << conv[3*(2-i)+1] << " | " << conv[3*(2-i)] << " | " << std::endl;
        std::cout << "     -------------" << std::endl;
    }
    std::cout << std::endl;
}



// Generate possible moves in a given position
std::vector<std::string> tictacthree::generateMoves() const {
    std::vector<std::string> possiblities;
    uint16_t sumBoard = state.xBoard | state.oBoard;
    for (int i = 0; i < 9; i++) {
        if ((sumBoard & 1) == 0) possiblities.push_back(std::to_string(8-i));
        sumBoard >>= 1;
    }
    return possiblities;
}

// input an index for the player of the board to make the next move
game* tictacthree::doMove(const std::string& move) const {
    t3board newState = state;
    uint16_t newMove = 1 << (8 - std::stoi(move));
    // because of rule and limitness in tic-tac-toe: #x geq #o
    // how many 1's appear in xBoard vs oBoard
    if (countOnes(state.xBoard, 3) > countOnes(state.oBoard, 3)) {
        newState.oBoard = state.oBoard | newMove;
    }
    else {
        newState.xBoard = state.xBoard | newMove;
    }
    return new tictacthree(newState);
}

//Primitive value is from the perspective of what the function is given
// return 0 if lose, 1 if win, 2 if tie, -1 if not primitive

gameResult tictacthree::primitiveValue() const {
    // checks against winningPositions, uniqueness of binary representation ensures no overlap
    if ((state.xBoard | state.oBoard) == 0b111111111) return TIE;
    for (uint16_t winPos : winningPositions_tt3) {
        if (subset(winPos, state.xBoard)) return WIN;
        if (subset(winPos, state.oBoard)) return LOSE;
    }
    return UNDECIDED;
}

///////////////////////////////////////////////////////////////
////////////////////// Core Function End //////////////////////
///////////////////////////////////////////////////////////////
