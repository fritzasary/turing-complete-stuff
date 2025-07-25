#pragma once
#include <vector>
#include <string>

enum gameResult { WIN = 1, LOSE = 0, TIE = 2, UNDECIDED = -1 };


class game {

public:

	virtual ~game() noexcept = default;

	virtual std::vector<int> generateMoves() const = 0;

	virtual game* doMove(const std::string& move) const = 0;

	virtual gameResult primitiveValue() const = 0;

	virtual std::string getState() const = 0;

};