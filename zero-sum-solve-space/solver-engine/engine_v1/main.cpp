#include <iostream>
#include <chrono>
// #include "game.h"
// #include "tictactoe.h"
// #include "tictactoev2.h"
#include "./zero-sums/tictac-variants/tictactoev2.h"
// #include "nimv1.h"
// #include "nimv2.h"
#include "./solver-engine/solve.cpp"

int main() {



	using namespace std::chrono;
    auto start = high_resolution_clock::now();

	// Initial the game with the starting value

	// this is how to start the v1 of nim
	// uint64_t startPosition = 0x0;
	// game* game = new nim(startPosition);
	// t3board board;
	t3board board;
	game* game = new tictactoe(board);
	gameResult result = solve(game);
	delete game;

	switch (result) {
		case WIN: std::cout << "Win" << std::endl; break; 
		case LOSE: std::cout << "Lose" << std::endl; break;
		case TIE: std::cout << "Tie" << std::endl; break;
		default: std::cout << "Undecided" << std::endl; break; 
	}


	auto end = high_resolution_clock::now();
    duration<double> elapsed = end - start; // seconds as double

    std::cout << "Total wall time: " << elapsed.count() << " seconds\n";
    return 0;

}
