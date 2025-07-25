#include <iostream>
#include "game.h"
// #include "tictactoe.h"
// #include "nimv1.h"
#include "nimv2.h"
#include "solve.cpp"

int main() {

	// Initial the game with the starting value

	// this is how to start the v1 of nim
	game* game = new nim(9);
	// game* game = new tictactoe("---------");
	gameResult result = solve(game);
	delete game;

	switch (result) {
		case WIN: std::cout << "Win" << std::endl; break; 
		case LOSE: std::cout << "Lose" << std::endl; break;
		case TIE: std::cout << "Tie" << std::endl; break;
		default: std::cout << "Undecided" << std::endl; break; 
	}

	return 0;
}
