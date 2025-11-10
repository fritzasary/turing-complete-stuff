#define CATCH_CONFIG_MAIN
#include <chrono>
#include "catch_amalgamated.hpp"

#include "../include/game.h"
#include "../include/tictacfour.h"
#include "../include/solve.h"



using namespace std::chrono;

 TEST_CASE("TicTacToe primitive positions") {
    SECTION("Empty board is undecided") {
	auto start = high_resolution_clock::now();
        t4board b;
        b.xBoard = 0;
        b.oBoard = 0;
        game* g = new tictacfour(b);
        REQUIRE(g->primitiveValue() == UNDECIDED);
        delete g;
	auto end = high_resolution_clock::now();
	duration<double> elapsed = end - start;
	std::cout << "Total wall time: " << elapsed.count() << " seconds\n";
    }
    SECTION("X wins on main diagonal") {
        t4board b;
        b.xBoard = 0b1000010000100001;
        b.oBoard = 0b0101001000000100;
        game* g = new tictacfour(b);
        REQUIRE(g->primitiveValue() == WIN);
        delete g;
    }
    SECTION("Full board is tie") {
        t4board b;
        b.xBoard = 0b0100011111000011;
        b.oBoard = 0b1011100000111100;
        game* g = new tictacfour(b);
        REQUIRE(g->primitiveValue() == TIE);
        delete g;
    }
    SECTION("O wins on the opposite diagonal") {
	t4board b;
	b.oBoard = 0b0001001001001000;
	b.xBoard = 0b1100110000000000;
	game* g = new tictacfour(b);
	REQUIRE(g->primitiveValue() == LOSE);
	delete g;
    }
}


TEST_CASE("TicTacToe position evaluations") {
    SECTION("Empty board is a draw") {
	auto start = high_resolution_clock::now();
	t4board b;
	b.xBoard = 0;
	b.oBoard = 0;
	game* g = new tictacfour(b);
	std::cout << "### Solving position ###" << std::endl;
	g->printState();
	REQUIRE(solve(g, -100, 100, true) == TIE);
	delete g;
	auto end = high_resolution_clock::now();
	duration<double> elapsed = end - start;
	std::cout << "Test lasted: " << elapsed.count() << " seconds\n";
    }
    SECTION("Trivial win for X") {
	auto start = high_resolution_clock::now();
	t4board b;
	b.xBoard = 0b1000010000100000;
	b.oBoard = 0b0100101000000000;
	game* g = new tictacfour(b);
	std::cout << "### Solving position ###" << std::endl;
	g->printState();
	REQUIRE(solve(g, -100, 100, true) == WIN);
	delete g;
	auto end = high_resolution_clock::now();
	duration<double> elapsed = end - start;
	std::cout << "Test lasted: " << elapsed.count() << " seconds\n";
    }
    SECTION("Trivial win for O") {
	auto start = high_resolution_clock::now();
	t4board b;
	b.xBoard = 0b1011000000100000;;
	b.oBoard = 0b0100010000000100;
	game* g = new tictacfour(b);
	std::cout << "### Solving position ###" << std::endl;
	g->printState();
	REQUIRE(solve(g, -100, 100, false) == LOSE);
	delete g;
	auto end = high_resolution_clock::now();
	duration<double> elapsed = end - start;
	std::cout << "Test lasted: " << elapsed.count() << " seconds\n";
    }
    SECTION("More obscure position that should be win for X") {
	auto start = high_resolution_clock::now();
	t4board b;
	b.oBoard = 0b0100000101000100;
	b.xBoard = 0b0000110010100000;
	game* g = new tictacfour(b);
	std::cout << "### Solving position ###" << std::endl;
	g->printState();
	REQUIRE(solve(g, -100, 100, true) == WIN);
	delete g;
	auto end = high_resolution_clock::now();
	duration<double> elapsed = end - start;
	std::cout << "Test lasted: " << elapsed.count() << " seconds\n";
    }
    SECTION("Same obscure position up to one different O move, should be win for X to achieve the same fork") {
	auto start = high_resolution_clock::now();
	t4board b;
	b.xBoard = 0b0000110010100000;
	b.oBoard = 0b0100000101000010;
	game* g = new tictacfour(b);
	std::cout << "### Solving position ###" << std::endl;
	g->printState();
	REQUIRE(solve(g, -100, 100, true) == WIN);
	delete g;
	auto end = high_resolution_clock::now();
	duration<double> elapsed = end - start;
	std::cout << "Test lasted: " << elapsed.count() << " seconds\n";
    }
    SECTION ("Symmetric position obscure position, win for O via fork") {
	auto start = high_resolution_clock::now();
	t4board b;
	b.xBoard = 0b0010010000110100;
	b.oBoard = 0b0000101011000000;
	game* g = new tictacfour(b);
	std::cout << "### Solving position ###" << std::endl;
	g->printState();
	REQUIRE(solve(g, -100, 100, false) == LOSE);
	delete g;
	auto end = high_resolution_clock::now();
	duration<double> elapsed = end - start;
	std::cout << "Test lasted: " << elapsed.count() << " seconds\n";
    }
}
