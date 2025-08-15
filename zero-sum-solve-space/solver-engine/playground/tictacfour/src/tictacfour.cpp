#include <iostream>
#include <random>
#include <cstdint>
#include <algorithm>
#include "game.h"
#include "tictacfour.h"

// rule: x always goes first and should always #x geq #o
// let xPlayer be true and xPlayer be false boolean values for turn



////  New construction of the tictactoe board representation utilizing bitboards
tictactoe::tictactoe(t4board initialState) : state(initialState) {}



///////////////////////////////////////////////////////////////////
////////////////////// Helper Function Begin //////////////////////
///////////////////////////////////////////////////////////////////

// this helps get a random number **for debug purposes
int getRandomInt(int min, int max) {
    static std::random_device rd;  // Seed source
    static std::mt19937 gen(rd()); // Mersenne Twister engine seeded with rd()

    std::uniform_int_distribution<> dist(min, max);
    return dist(gen);
}




// Count the number of 1's present in a number's binary representation
int countOnes(uint16_t num) {
    int cnt = 0;
    for (int i = 0; i < 16; i++) {
        if ((num & 1) == 1) cnt++;
        num >>= 1;
    }
    return cnt;
}


bool turn(t4board board) {
    return countOnes(board.xBoard) == countOnes(board.oBoard);
} 

// To see if a winning position bit representation exists as a subset of the current state
bool subset(uint16_t sub,  uint16_t super) {
    return (sub & super) == sub;
}

std::string tictactoe::getState() const {
    return state.to_string();
}



void tictactoe::printState() const {
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
    std::cout << "###########################" << std::endl;
    std::cout << "### Current board state ###" << std::endl;
    std::cout << "###########################" << std::endl;
    std::cout << std::endl;
    std::cout << "     -------------" << std::endl;
    for (int i = 0; i < 4; i++) {

        // Need to fix this part
        std::cout << "     | " << conv[4*i]  << " | " << conv[4*i+1] << " | " << conv[4*i+2] << " | " << conv[4*i+3] << " | " << std::endl;
        std::cout << "     -------------" << std::endl;
    }
    std::cout << std::endl;
}


///////////////////////////////////////////////////////////////////
////////////////////// Helper Function End //////////////////////
///////////////////////////////////////////////////////////////////






/////////////////////////////////////////////////////////////////
////////////////////// Core Function Begin //////////////////////
/////////////////////////////////////////////////////////////////



// Generate possible moves in a given position
std::vector<std::string> tictactoe::generateMoves() const {
    std::vector<std::string> possiblities;
    uint16_t sumBoard = state.xBoard | state.oBoard;
    for (int i = 0; i < 16; i++) {
        if ((sumBoard & 1) == 0) possiblities.push_back(std::to_string(i));
        sumBoard >>= 1;
    }
    return possiblities;
}

// input an index for the player of the board to make the next move
game* tictactoe::doMove(const std::string& move) const {
    t4board newState = state;
    uint16_t newMove = 1 << std::stoi(move);
    // because of rule and limitness in tic-tac-toe: #x geq #o
    // how many 1's appear in xBoard vs oBoard
    if (countOnes(state.xBoard) > countOnes(state.oBoard)) {
        newState.oBoard = state.oBoard | newMove;
    }
    else {
        newState.xBoard = state.xBoard | newMove;
    }
    return new tictactoe(newState);
}

//Primitive value is from the perspective of what the function is given
// return 0 if lose, 1 if win, 2 if tie, -1 if not primitive

gameResult tictactoe::primitiveValue() const {
    // checks against winningPositions, uniqueness of binary representation ensures no overlap
    for (uint16_t winPos : winningPositions) {
        if (subset(winPos, state.xBoard)) return turn(state) ? WIN : LOSE;
        if (subset(winPos, state.oBoard)) return !turn(state) ? LOSE : WIN;
    }
    if ((state.xBoard | state.oBoard) == 0b1111111111111111) return TIE;
    return UNDECIDED;
}

///////////////////////////////////////////////////////////////
////////////////////// Core Function End //////////////////////
///////////////////////////////////////////////////////////////


// int main() {
//     t3board board;

//     game* game = new tictactoe(board);

//     std::vector<std::string> moves;

//     while (game->primitiveValue() == UNDECIDED) {
//         moves = game->generateMoves();
//         if (moves.empty()) break;
//         int randInt = getRandomInt(0, static_cast<int>(moves.size()) - 1);
//         game = game->doMove(moves[randInt]);
//         static_cast<tictactoe*>(game)->printState();
//     }


//     return 0;
// }