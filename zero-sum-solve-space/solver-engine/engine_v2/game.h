#pragma once
#include <vector>
#include <string>

enum gameResult { WIN = 1, LOSE = -1, TIE = 0, UNDECIDED = -2 };


class game {

public:

	virtual ~game() noexcept = default;

	virtual std::vector<std::string> generateMoves() const = 0;

	virtual game* doMove(const std::string& move) const = 0;

	virtual gameResult primitiveValue() const = 0;

	virtual std::string getState() const = 0;

};