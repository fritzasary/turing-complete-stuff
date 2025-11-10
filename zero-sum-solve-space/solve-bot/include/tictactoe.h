#pragma once
#include <iostream>
#include <random>
#include <cstdint>
#include <algorithm>
#include "game.h"




class tictactoe : public game {

public:
	virtual std::vector<std::string> generateMoves() const = 0;
	virtual game* doMove(const std::string& move) const = 0;
	virtual gameResult primitiveValue() const  = 0;

	virtual std::unique_ptr<board> getBoard() const = 0;
	virtual void printState() const = 0;
	virtual bool turn() const = 0;
	virtual ~tictactoe() {}


};
