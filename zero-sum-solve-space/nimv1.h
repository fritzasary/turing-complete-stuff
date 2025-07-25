#pragma once
#include "game.h"
#include <vector>
#include <string>




class nim : public game {

	int state;

public:
	nim(int initialState);
	std::vector<int> generateMoves() const override;
	game* doMove(const std::string& move) const override;
	gameResult primitiveValue() const override;
	std::string getState() const override;

};