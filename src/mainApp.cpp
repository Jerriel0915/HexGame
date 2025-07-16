#include "../include/Board.h"
#include "../include/Utils.h"
#include <iostream>

int main() {
	Board board = Board(
		Utils::initBoard(),
		RED,
		EMPTY,
		false
	);

	while (!board.is_terminal()) {
		int row, col;
		std::cout << "Now turn: " << board.getTurn() << '\n';
		std::cout << "Enter row and column: ";
		std::cin >> row >> col;

		board = board.make_move(row, col);
		board.printTest();

		if (board.is_terminal()) {
			std::cout << "Game over!" << std::endl;
			break;
		}
	}
}