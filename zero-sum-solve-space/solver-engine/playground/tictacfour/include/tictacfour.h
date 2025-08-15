#pragma once
#include <iostream>
#include "game.h"




class t4board {

public:
    t4board() = default;
    uint16_t xBoard = 0b0000000000000000;
    uint16_t oBoard = 0b0000000000000000;

    std::string to_string() const {
        return "X: " + std::to_string(xBoard) + ", O: " + std::to_string(oBoard);
    };

};


const uint16_t winningPositions[] = {
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

class tictactoe : public game {

	t4board state;

public:

	tictactoe(t4board initialState); //initializes an empty board
	std::vector<std::string> generateMoves() const override;
	game* doMove(const std::string& move) const override;
	gameResult primitiveValue() const override;
	std::string getState() const override;

	void printState() const;

};