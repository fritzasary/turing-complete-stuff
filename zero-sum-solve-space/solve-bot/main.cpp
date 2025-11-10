#include <iostream>
#include <chrono>
#include "tictacthree.h"
//#include "tictacfour.h"
#include "solve.h"
#include <bitset>

int main() {
	using namespace std::chrono;
	auto start = high_resolution_clock::now();

	// initialize the start of game

	init_db("/home/fritz/Documents/sandbox/centralized_dbs/tictacthree_positions.db");
	t3board b;
	b.xBoard = 0b0010010000110100;
	b.oBoard = 0b0000101011000000;
	b.xBoard = 0b1110000000000000;
	b.oBoard = 0b0001000001001000;
	//b.xBoard = 0b0000001101110110;
	//b.oBoard = 0b0110010010001001;
	b.xBoard = 0b0000;
	b.oBoard = 0b000;
	game* g = new tictacthree(b);
	//g = g->doMove("4");
	//std::cout << "This board hash: " <<  hashBoard(b) << std::endl;
	g->printState();
	int result = solve(g, LOSE, WIN, g->turn());
	

	// Finding children move with their results for debugging purposes in the future
	for (const auto& move : g->generateMoves()) {
		std::unique_ptr<game> next(g->doMove(move));
		std::cout << hashBoard(*next->getBoard()) << std::endl;
		std::cout << move << ", " << solve(next.get(), LOSE, WIN, next->turn()) << std::endl;
	}
	delete g;

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
