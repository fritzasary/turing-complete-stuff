
#include <iostream>
#include <unordered_map>
#include <string>
#include <vector>
#include <memory>
#include "tictacfour.h"
#include "game.h"


std::unordered_map<std::string, gameResult> memo;


// Convert a game position to a unique ID (for memoization)
std::string stateID(const game* g) {
    // Might need to override this in derived classes if needed
    const tictactoe* tictactoePtr = dynamic_cast<const tictactoe*>(g);
    if (tictactoePtr) {
        return tictactoePtr->getState();
    }
    return "";
}

// Recursive, exhaustive search engine
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
        std::unique_ptr<game> next(position->doMove(move));
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