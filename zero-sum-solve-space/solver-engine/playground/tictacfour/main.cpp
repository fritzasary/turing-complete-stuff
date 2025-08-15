#include <iostream>
#include <chrono>
#include "tictacfour.h"
#include "solve.h"

int main() {
	using namespace std::chrono;
    auto start = high_resolution_clock::now();

	// Initial the game with the starting value

	// this is how to start the v1 of nim
	// uint64_t startPosition = 0x0;
	// game* game = new nim(startPosition);
	// t3board board;
	t4board board;
	game* game = new tictactoe(board);
	int result = solve(game, LOSE, WIN, true);
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
