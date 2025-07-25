#include <iostream>
#include <random>
#include <algorithm>
#include "game.h"
#include "tictactoe.h"

// rule: x always goes first and should always #x geq #o
// let xPlayer be true and xPlayer be false boolean values for turn

// Constructor
tictactoe::tictactoe(std::string initialState) : state(initialState) {}


///////////////////////////////////////////////////////////////////
////////////////////// Helper Function Begin //////////////////////
///////////////////////////////////////////////////////////////////

// identify's based on current state of board to see who's turn it is

// Temporarily remove because can't have this as const function
// bool turn(const std::string& state) const {
//     long xNum = std::count(state.begin(), state.end(), 'x');
//     long yNum = std::count(state.begin(), state.end(), 'o');
//     if (xNum == yNum) {
//         return 1;
//     } else {
//         return 0;
//     }
// }

// this prints the current boards state
void printState(std::string state) {
    std::cout << "###########################" << std::endl;
    std::cout << "### Current board state ###" << std::endl;
    std::cout << "###########################" << std::endl;
    std::cout << std::endl;
    std::cout << "     -------------" << std::endl;
    for (int i = 0; i < 3; i++) {
        std::cout << "     | " << state[3*i]  << " | " << state[3*i+1] << " | " << state[3*i+2] << " | " << std::endl;
        std::cout << "     -------------" << std::endl;
    }
    std::cout << std::endl;
}

// this helps get a random number **for debug purposes
int getRandomInt(int min, int max) {
    static std::random_device rd;  // Seed source
    static std::mt19937 gen(rd()); // Mersenne Twister engine seeded with rd()

    std::uniform_int_distribution<> dist(min, max);
    return dist(gen);
}

std::string tictactoe::getState() const {
    return state;
}

///////////////////////////////////////////////////////////////////
////////////////////// Helper Function Begin //////////////////////
///////////////////////////////////////////////////////////////////







/////////////////////////////////////////////////////////////////
////////////////////// Core Function Begin //////////////////////
/////////////////////////////////////////////////////////////////


std::vector<int> tictactoe::generateMoves() const {
    std::vector<int> possiblities;
    for (int i = 0; i < state.length(); i++) {
        if (state[i] == '-') {
            possiblities.push_back(i);
        }
    }
    return possiblities;
}

// input an index for the player of the board to make the next move
game* tictactoe::doMove(const std::string& move) const {
    // because of rule and limitness in tic-tac-toe: #x geq #o
    long xNum = std::count(state.begin(), state.end(), 'x');
    long yNum = std::count(state.begin(), state.end(), 'o');
    std::string newState = state;
    if (xNum == yNum) {
        newState.at(std::stoi(move)) = 'x';
    } else {
        newState.at(std::stoi(move)) = 'o';
    }
    return new tictactoe(newState);
}

//Primitive value is from the perspective of what the function is given

// return 0 if lose, 1 if win, 2 if tie, -1 if not primitive
gameResult tictactoe::primitiveValue() const {
    // this checks the diags
    if ((state[0] != '-' && state[0] == state[4] && state[4] == state[8]) || (state[2] != '-' && state[2] == state[4] && state[4] == state[6])) {
            return LOSE;
        }
    for (int i = 0; i < 3; i++) {
        // this checks the rows
        if (state[3*i] == state[3*i + 1] && state[3*i + 1] == state[3*i + 2] && state[3*i] != '-') {
            return LOSE;
        }
        // this checks the columns
        if (state[i] != '-' && state[i] == state[i+3] && state[i+3] == state[i+6]) {
            return LOSE;
        }
    }
    int xNum = std::count(state.begin(), state.end(), 'x');
    int yNum = std::count(state.begin(), state.end(), 'o');
    if ((xNum + yNum) == 9) {
        return TIE;
    }
    return UNDECIDED;
}

///////////////////////////////////////////////////////////////
////////////////////// Core Function End //////////////////////
///////////////////////////////////////////////////////////////