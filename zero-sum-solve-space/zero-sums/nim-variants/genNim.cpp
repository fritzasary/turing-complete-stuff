#include <iostream>
#include "genNim.h"



// The constructor
nim::nim(int initialState) : state(initialState) {}



std::string nim::getState() const {
	return std::to_string(state);
}


/////////////////////////////////////////////////////////////////
////////////////////// Core Function Begin //////////////////////
/////////////////////////////////////////////////////////////////


std::vector<int> nim::generateMoves() const {
	std::vector<int> moves;
	for (int i = 1; i < TAKE; i++) {
		if (i == 3) continue;
		if (state >= i) {
			moves.push_back(i);
		}
	}
	return moves;
}


// Generates a new game object with the move that is applied
game* nim::doMove(const std::string& move) const {
	int i = std::stoi(move);
	return new nim(state - i);
}


// Return -1 if not primitive, 1 if win, 0 if lose, by construction and simplicity of game, there is no tie
gameResult nim::primitiveValue() const {
	if (state == 0 || state < 0) {
		return LOSE;
	}
	return UNDECIDED;
}


///////////////////////////////////////////////////////////////
////////////////////// Core Function End //////////////////////
///////////////////////////////////////////////////////////////


//// main fn is primarily for debugging purposes. but removed for duplication compiling purposes