#pragma once
#include <vector>
#include <string>
#include <memory>


// The general game result enums
enum gameResult { WIN = 1, LOSE = -1, TIE = 0, UNDECIDED = -2 };

// The generic board constructor for the game
struct board {
    virtual ~board() = default;
    virtual std::string serialize() const = 0;
};



// The game that gives the game it's structure and rules to be played out
class game {

public:

	virtual ~game() noexcept = default;

	virtual std::vector<std::string> generateMoves() const = 0;

	virtual game* doMove(const std::string& move) const = 0;

	virtual gameResult primitiveValue() const = 0;

	virtual bool turn() const = 0;

	virtual std::unique_ptr<board> getBoard() const = 0;

	virtual void printState() const = 0;

};
