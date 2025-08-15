#include <iostream>
#include <unordered_map>
#include <string>
#include <vector>
#include <memory>
#include "game.h"
#include "tictacfour.h"

std::unordered_map<std::string, gameResult> memo;


// Convert a game position to a unique ID (for memoization)
std::string stateID(const game* g) {
    // Might need to override this in derived classes if needed
    // For instance, for the game of Nim, just use the remaining sticks as a string
    // const nim* gameptr = dynamic_cast<const nim*>(g);
    // if (gameptr) {
    //     return gameptr->getState();
    const tictactoe* tictactoePtr = dynamic_cast<const tictactoe*>(g);
    if (tictactoePtr) {
        return tictactoePtr->getState();
    }
    return "";
}




// Recursive, exhaustive search engine
// int solve(game* position, int alpha, int beta, bool maxingPlayer) {
//     std::string id = stateID(position);
//     if (!id.empty() && memo.count(id)) return memo[id];

//     int result = position->primitiveValue();
//     if (result != UNDECIDED) {
//         if (!id.empty()) memo[id] = (gameResult)result;
//         return memo[id];
//     }

//     int best = -1; //assume the worst

//     for (const auto& move : position->generateMoves()) {
//         std::unique_ptr<game> next(position->doMove(move));

//         //recursively get the result of the next position with this move
//         int result = solve(next.get(), alpha, beta, !maxingPlayer);

//         if (maxingPlayer) {

//             int result = solve(next.get(), alpha, beta, !maxingPlayer);
//             if (result >= beta) break;
//             alpha = std::max(alpha, (int)result);
//         }

//         else {

//             int result = solve(next.get(), alpha, beta, maxingPlayer);
//             if (result <= alpha) break;
//             beta = std::min(beta, (int)result);
//         }

//     }
//     if (!id.empty()) memo[id] = (gameResult)best;
//     return best;
// }



int solve(game* position, int alpha, int beta, bool maxingPlayer) {
    std::string id = stateID(position);
    if (!id.empty() && memo.count(id)) return memo[id];

    int value = position->primitiveValue();
    if (value != UNDECIDED) {
        if (!id.empty()) memo[id] = static_cast<gameResult>(value);
        return value;
    }

    int best = maxingPlayer ? INT_MIN : INT_MAX;

    for (const auto& move : position->generateMoves()) {
        std::unique_ptr<game> next(position->doMove(move));
        int result = solve(next.get(), alpha, beta, !maxingPlayer);

        if (maxingPlayer) {
            best = std::max(best, result);
            alpha = std::max(alpha, best);
        } else {
            best = std::min(best, result);
            beta = std::min(beta, best);
        }

        if (alpha >= beta) break; // prune
    }

    if (!id.empty()) memo[id] = static_cast<gameResult>(best);
    return best;
}
