#pragma once
#include "game.h"
#include <vector>
#include <string>


#define PILE1 3
#define PILE2 4
#define PILE3 5



class nim : public game {

	int state;

public:
	nim(int initialState);
	std::vector<int> generateMoves() const override;
	game* doMove(const std::string& move) const override;
	gameResult primitiveValue() const override;
	std::string getState() const override;
};