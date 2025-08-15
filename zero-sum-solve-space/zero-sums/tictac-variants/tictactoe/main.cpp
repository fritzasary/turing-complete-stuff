#include <iostream>
#include <chrono>
#include "tictactoe.h"
#include "solve.h"

int main() {
	using namespace std::chrono;
    auto start = high_resolution_clock::now();

	// Initial the game with the starting value
	
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
