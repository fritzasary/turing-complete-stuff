#pragma once
#include <iostream>
#include "game.h"
#include "tictactoe.h"
#include "utils.h"




struct t3board : public board {

    t3board() = default;
    uint16_t xBoard = 0b000000000;
    uint16_t oBoard = 0b000000000;

    std::string serialize() const override {
        return std::to_string(xBoard) + "," + std::to_string(oBoard);
    }

};


const uint16_t winningPositions_tt3[] = {
    0b000000111,
    0b000111000,
    0b111000000,
    0b100100100,
    0b010010010,
    0b001001001,
    0b100010001,
    0b001010100
};

class tictacthree : public tictactoe {

public:

	tictacthree(t3board initialState); //initializes an empty board
	std::vector<std::string> generateMoves() const override;
	game* doMove(const std::string& move) const override;
	gameResult primitiveValue() const override;
	void printState() const override;
	bool turn() const override;
	std::unique_ptr<board> getBoard() const override {
		return std::make_unique<t3board>(state);
	};
private:

	t3board state;

};
