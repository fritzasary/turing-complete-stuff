#pragma once
#include <iostream>
#include "game.h"




class tictactoe : public game {

	std::string state;

private:
	int getRandomInt(int min, int max);
	bool turn(const std::string& state) const;
	void printState(std::string state);

public:

	tictactoe(std::string initialState); //initializes an empty board
	std::vector<int> generateMoves() const override;
	game* doMove(const std::string& move) const override;
	gameResult primitiveValue() const override;
	std::string getState() const override;


};