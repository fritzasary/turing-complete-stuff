
#include <iostream>
#include <unordered_map>
#include <string>
#include <vector>
#include <memory>
#include "game.h"



//////// This implementation was purely a functional implementation


// this is like a hashmap, essentially
// std::unordered_map<int, int> memo;

// int searcher(int state) {

// 	// // for debugging purposes if run into depth error
// 	// if (depth > 1000) {
//     //     std::cerr << "Recursion too deep at state: " << state << std::endl;
//     //     exit(1);
//     // }

// 	// if this state has been encountered before and solved, get the result instead of recomputing it
//     if (memo.count(state)) return memo[state];
//     int value = primitiveValue(state);
//     if (value != -1) {
//         memo[state] = value;
//         return value;
//     }
//     std::vector<int> moves = possibleMoves(state);
//     bool canWin = false;
//     bool canTie = false;
//     for (int move : moves) {
//         int nextState = doMove(state, move);
//         int result = searcher(nextState);
        
//         if (result == 0) canWin = true;
//         else if (result == 2) canTie = true;
//     }
//     if (canWin) {
//         memo[state] = 1;
//         return 1;
//     } else if (canTie) {
//         memo[state] = 2;
//         return 2;
//     } else {
//         memo[state] = 0;
//         return 0;
//     }
// }


// int solve(int state) {
//     memo.clear(); // Clear memo before each new solve
//     return searcher(state);
// }



std::unordered_map<std::string, gameResult> memo;


// Convert a game position to a unique ID (for memoization)
std::string stateID(const game* g) {
    // Might need to override this in derived classes if needed
    // For Nim, just use the remaining sticks as a string
    const nim* gameptr = dynamic_cast<const nim*>(g);
    if (gameptr) {
        return gameptr->getState();
    }
    // const tictactoe* tictactoePtr = dynamic_cast<const tictactoe*>(g);
    // if (tictactoePtr) {
    //     return tictactoePtr->getState();
    // }
    return "";
}

// Recursive search
gameResult solve(game* position) {
    std::string id = stateID(position);
    if (!id.empty() && memo.count(id)) return memo[id];

    gameResult value = position->primitiveValue();
    if (value != UNDECIDED) {
        if (!id.empty()) memo[id] = value;
        return value;
    }

    gameResult best = LOSE; // Here we assume the worst outcome
    for (const auto& move : position->generateMoves()) {
        std::unique_ptr<game> next(position->doMove(std::to_string(move)));
        int result = solve(next.get());

        if (result == LOSE) {
            best = WIN;
            break;
        }
        if (result == TIE && best != WIN) {
            best = TIE;
        }
    }

    if (!id.empty()) memo[id] = best;
    return best;
}