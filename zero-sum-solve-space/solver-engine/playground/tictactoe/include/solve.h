#pragma once
#include "game.h"
#include "tictactoe.h"


// Convert a game position to a unique ID (for memoization)
std::string stateID(const game* g);
// Recursive, exhaustive search engine
gameResult solve(game* position, int alpha, int beta, bool maxingPlayer);