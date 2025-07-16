#include "../include/Board.h"
#include "../include/Utils.h"
#include "../include/MCTS.h"
#include <iostream>

int main() {
	Board board = Board(
		Utils::initBoard(),
		RED,
		EMPTY,
		false
	);
	MCTS tree;

	while (!board.is_terminal()) {
		if (board.getTurn() == RED) {
			int row, col;
		std::cout << "Now turn: " << board.getTurn() << '\n';
		std::cout << "Enter row and column: ";
		std::cin >> row >> col;

		board = board.make_move(row, col);
		}
		else {
			for (int i = 0; i < 1000; i++) {
				tree.do_rollout(board);
			}
			board = tree.choose(board);
		}
		
		board.printTest();

		if (board.is_terminal()) {
			std::cout << "Game over!" << std::endl;
			break;
		}
	}
	return 0;
}