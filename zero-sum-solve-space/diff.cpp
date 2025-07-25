#include <iostream>
#include <vector>
#include <string>
#include <random>
#include <algorithm>
#include <cassert>



class TicTacToe {
public:
    // Constructor initializes empty board
    TicTacToe() : board_(9, '-') {}

    // Return true if the game is over (win or draw)
    bool isGameOver() const {
        return hasWinner() || isDraw();
    }

    // Returns which player’s turn it is: true for 'x', false for 'o'
    bool isXTurn() const {
        size_t xCount = std::count(board_.begin(), board_.end(), 'x');
        size_t oCount = std::count(board_.begin(), board_.end(), 'o');
        return xCount == oCount;
    }

    // Returns vector of indices of empty squares
    std::vector<int> availableMoves() const {
        std::vector<int> moves;
        for (size_t i = 0; i < board_.size(); ++i) {
            if (board_[i] == '-') {
                moves.push_back(static_cast<int>(i));
            }
        }
        return moves;
    }

    // Make a move at index for the current player
    // Returns true if move was successful, false if invalid
    bool makeMove(int index) {
        if (index < 0 || index >= static_cast<int>(board_.size())) return false;
        if (board_[index] != '-') return false;
        board_[index] = isXTurn() ? 'x' : 'o';
        return true;
    }

    // Print the current board to stdout
    void printBoard() const {
        std::cout << "###########################\n";
        std::cout << "### Current board state ###\n";
        std::cout << "###########################\n\n";
        std::cout << "     -------------\n";
        for (int i = 0; i < 3; ++i) {
            std::cout << "     | " << board_[3*i] << " | " << board_[3*i + 1] << " | " << board_[3*i + 2] << " |\n";
            std::cout << "     -------------\n";
        }
        std::cout << std::endl;
    }

    // Returns 'x' or 'o' if a player has won, else returns '-'
    char winner() const {
        // Check rows and columns
        for (int i = 0; i < 3; ++i) {
            // Rows
            if (board_[3*i] != '-' && board_[3*i] == board_[3*i + 1] && board_[3*i] == board_[3*i + 2]) {
                return board_[3*i];
            }
            // Columns
            if (board_[i] != '-' && board_[i] == board_[i + 3] && board_[i] == board_[i + 6]) {
                return board_[i];
            }
        }
        // Diagonals
        if (board_[0] != '-' && board_[0] == board_[4] && board_[0] == board_[8]) {
            return board_[0];
        }
        if (board_[2] != '-' && board_[2] == board_[4] && board_[2] == board_[6]) {
            return board_[2];
        }
        return '-';
    }

private:
    std::string board_;

    // Returns true if board is full with no winner
    bool isDraw() const {
        return std::none_of(board_.begin(), board_.end(), [](char c){ return c == '-'; }) && winner() == '-';
    }

    // Returns true if there is a winner
    bool hasWinner() const {
        return winner() != '-';
    }
};

// Generates a random integer between min and max inclusive
int getRandomInt(int min, int max) {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(min, max);
    return dist(gen);
}

int main() {
    TicTacToe game;

    while (!game.isGameOver()) {
        game.printBoard();

        auto moves = game.availableMoves();
        if (moves.empty()) break; // no moves left, safety check

        int choice = moves[getRandomInt(0, static_cast<int>(moves.size()) - 1)];

        bool success = game.makeMove(choice);
        assert(success);  // move should always be valid here
    }

    game.printBoard();

    char win = game.winner();
    if (win == '-') {
        std::cout << "Game ended in a draw.\n";
    } else {
        std::cout << "Player '" << win << "' has won!\n";
    }

    return 0;
}
