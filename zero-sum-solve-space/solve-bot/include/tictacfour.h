#pragma once
#include <iostream>
#include "game.h"
#include "tictactoe.h"
#include "utils.h"





struct t4board : public board {

    t4board() = default;
    uint16_t xBoard = 0b0000000000000000;
    uint16_t oBoard = 0b0000000000000000;

    std::string serialize() const override {
        return std::to_string(xBoard) + "," + std::to_string(oBoard);
    };

};


const uint16_t winningPositions_tt4[] = {
    0b0000000000001111,
    0b0000000011110000,
    0b0000111100000000,
    0b1111000000000000,
    0b1000100010001000,
    0b0100010001000100,
    0b0010001000100010,
    0b0001000100010001,
    0b1000010000100001,
    0b0001001001001000
};

class tictacfour : public tictactoe {

	t4board state;
public:
	tictacfour(t4board initialState);
	std::vector<std::string> generateMoves() const override;
	game* doMove(const std::string& move) const override;
	gameResult primitiveValue() const override;
	void printState() const override;
	bool turn() const override;
	std::unique_ptr<board> getBoard() const override {
		return std::make_unique<t4board>(state);
	};

};
