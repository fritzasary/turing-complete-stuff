#include <string>
#include <utility>
#include <memory>
#include <iostream>
#include "game.h"
#include "tictacthree.h"
#include "tictacfour.h"
#include "solve.h"
#ifdef BUILD_PYTHON
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

namespace py = pybind11;

struct PyBoard : board {
    using board::board;  // Inherit constructors

    std::string serialize() const override {
        PYBIND11_OVERRIDE_PURE(
            std::string,   // Return type
            board,         // Parent class
            serialize,     // Name of function in C++
        );
    }
};





// For python wrapper from c++ backend
int py_solve(const std::string &game_name, game* g) {
    if (game_name != "tictactoe") {
        throw std::runtime_error("Unknown game type: " + game_name);
    }
    return solve(g, -100, 100, g->turn());
}


PYBIND11_MODULE(solver, m) {
    
    using namespace pybind11;
    //register_factories(); // this loads up the game factories
    m.def("solve", &py_solve, "Solve a generic game state",
	py::arg("game_name"), py::arg("state_blob"));

    // --- Expose enum gameResult ---
    py::enum_<gameResult>(m, "gameResult")
        .value("WIN", WIN)
        .value("LOSE", LOSE)
        .value("TIE", TIE)
        .value("UNDECIDED", UNDECIDED)
        .export_values();


    // --- Expose abstract base class ---
    py::class_<game>(m, "game")
        .def("generateMoves", &game::generateMoves)
        .def("doMove", &game::doMove)
        .def("primitiveValue", &game::primitiveValue)
	.def("printState", &game::printState)
	.def("getBoard", &game::getBoard);

    // --- Board structs ---

    py::class_<board, std::shared_ptr<board>>(m, "board")
	.def("serialize", &board::serialize);

    py::class_<t3board> t3(m, "t3board");
    t3.def(py::init<>())
      .def_readwrite("xBoard", &t3board::xBoard)
      .def_readwrite("oBoard", &t3board::oBoard)
      .def("serialize", &t3board::serialize);

    py::class_<t4board> t4(m, "t4board");
    t4.def(py::init<>())
      .def_readwrite("xBoard", &t4board::xBoard)
      .def_readwrite("oBoard", &t4board::oBoard)
      .def("serialize", &t4board::serialize);

    // --- TicTacToe implementation ---

    // Skeleton TicTac<X> implementation
    py::class_<tictactoe, game>(m, "tictactoe")
        /* .def(py::init<const t3board&>())
	.def(py::init<const t4board&>()) */
        .def("generateMoves", &tictactoe::generateMoves)
        .def("doMove", [](tictactoe &self, const std::string &move) {
            return std::unique_ptr<tictactoe>(
                static_cast<tictactoe*>(self.doMove(move))
            );
        })
        .def("primitiveValue", &tictactoe::primitiveValue)
	.def("printState", &tictactoe::printState)
	.def("getBoard", &tictactoe::getBoard);

    // TicTacThree instantiation
    py::class_<tictacthree, tictactoe>(m, "tictacthree")
	.def(py::init<const t3board&>());

    // TicTacFour instantiation
    py::class_<tictacfour, tictactoe>(m, "tictacfour")
	.def(py::init<const t4board&>());


    // --- Solver function ---
    m.def("solve", &py_solve,
          "Compute best outcome from provided state",
          py::arg("game_name"), py::arg("state"));
}
#endif
