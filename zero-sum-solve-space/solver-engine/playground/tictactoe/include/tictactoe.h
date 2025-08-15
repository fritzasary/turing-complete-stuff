#pragma once
#include "game.h"




class t3board {

public:
    t3board() = default;
    uint16_t xBoard = 0b000000000;
    uint16_t oBoard = 0b000000000;

    std::string to_string() const {
        return "X: " + std::to_string(xBoard) + ", O: " + std::to_string(oBoard);
    };
};


const uint16_t winningPositions[] = {
    0b000000111,
    0b000111000,
    0b111000000,
    0b100100100,
    0b010010010,
    0b001001001,
    0b100010001,
    0b001010100
};

class tictactoe : public game {

	t3board state;

public:

	tictactoe(t3board initialState); //initializes an empty board
	std::vector<std::string> generateMoves() const override;
	game* doMove(const std::string& move) const override;
	gameResult primitiveValue() const override;
	std::string getState() const override;

	void printState() const;

};