#pragma once
#include "game.h"
#include "utils.h"


int solve(game* position, int alpha, int beta, bool maxingPlayer);

// Need to build and utilize database on results 
std::string hashBoard(const board& b);
void init_db(const std::string& path);
bool get_db(const std::string& hash, int& outVal);
void set_db(const std::string& hash, int val);

