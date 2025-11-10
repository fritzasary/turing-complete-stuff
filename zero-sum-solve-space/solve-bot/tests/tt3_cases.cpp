#define CATCH_CONFIG_MAIN
#include "catch_amalgamated.hpp"

#include "../include/game.h"
#include "../include/tictacthree.h"
#include "../include/solve.h"

int countOnes_cpy(uint16_t num) {
    int cnt = 0;
    for (int i = 0; i < 9; i++) {
        if ((num & 1) == 1) cnt++;
        num >>= 1;
    }
    return cnt;
}

bool turn_cpy(t3board board) {
    return countOnes_cpy(board.xBoard) == countOnes_cpy(board.oBoard);
} 



 TEST_CASE("TicTacToe primitive positions") {
    SECTION("Empty board is undecided") {
        t3board board;
        board.xBoard = 0b000000000;
        board.oBoard = 0b000000000;
        game* g = new tictacthree(board);
        REQUIRE(g->primitiveValue() == UNDECIDED);
        delete g;
    }

    SECTION("X wins row") {
        t3board board;
        board.xBoard = 0b100100100;
        board.oBoard = 0b010010000;
        game* g = new tictacthree(board);
        REQUIRE(g->primitiveValue() == WIN);
        delete g;
    }

    SECTION("Full board is tie") {
        t3board board;
        board.xBoard = 0b001110011;
        board.oBoard = 0b110001100;
        game* g = new tictacthree(board);
        REQUIRE(g->primitiveValue() == TIE);
        delete g;
    }
}



TEST_CASE("Solver finds correct results") {
    SECTION("Trivial tie") {
        t3board board;
        game* g = new tictacthree(board);
        REQUIRE(solve(g, -100, 100, turn_cpy(board)) == TIE);
        delete g;
    }

    SECTION("Immediate win") {
        t3board board;
        board.xBoard = 0b100100000;
        board.oBoard = 0b010010000;
        game* g = new tictacthree(board);
        REQUIRE(solve(g, -100, 100, turn_cpy(board)) == WIN);
        delete g;
    }

    SECTION("Forced win #1 for X via fork position") {
        t3board board;
        board.xBoard = 0b110000000;
        board.oBoard = 0b000100001;
        game* g = new tictactoe(board);
        REQUIRE(solve(g, -100, 100, turn_cpy(board)) == WIN);
        delete g;
    }

    SECTION("Forced win #2 for X via fork position") {
        t3board board;
        board.xBoard = 0b011010000;
        board.oBoard = 0b000001100;
        game* g = new tictactoe(board);
        REQUIRE(solve(g, -100, 100, turn_cpy(board)) == WIN);
        delete g;
    }

    SECTION("Forced win #3 for X via fork position") {
        t3board board;
        board.xBoard = 0b001010000;
        board.oBoard = 0b000001100;
        game* g = new tictacthree(board);
        REQUIRE(solve(g, -100, 100, turn_cpy(board)) == WIN);
        delete g;
    }

    SECTION("Forced win for O") {
        t3board board;
        board.xBoard = 0b100001010;
        board.oBoard = 0b001010000;
        game* g = new tictacthree(board);
        REQUIRE(solve(g, -100, 100, turn_cpy(board)) == LOSE); // this means that it's min's player and the result for the person should be LOSE from X's perspective.
        delete g;
    }

    SECTION("Forced win for X") {
        t3board board;
        board.xBoard = 0b001010001;
        board.oBoard = 0b010101000;
        game* g = new tictacthree(board);
        REQUIRE(solve(g, -100, 100, turn_cpy(board)) == WIN); // this means that it's min's player and the result for the person should be LOSE from X's perspective.
        delete g;
    }

    SECTION("Drawn position") {
	t3board b;
	b.xBoard = 0b100000001;
	b.oBoard = 0b000010000;
	game* g = new tictacthree(b);
	REQUIRE(solve(g, -100, 100, turn_cpy(b)) == TIE);
	delete g;
    }

    SECTION("Drawn Position") {
	t3board b;
	b.xBoard = 0b000000100000001;
	b.oBoard = 0b000000000010000;
	game* g = new tictacthree(b);
	REQUIRE(solve(g, -100, 100, turn_cpy(b)) == TIE);
	delete g;
    }

    SECTION("Debugging misinterpreted position") {
        t3board b;
        b.xBoard = 0b110001000;
	b.oBoard = 0b1010000;
        game* g = new tictacthree(b);
        REQUIRE(turn_cpy(b) == false);
        REQUIRE(solve(g, -2, 2, turn_cpy(b)) == LOSE);
        delete g;
    }

}

