#include "../include/Board.h"
#include <iostream>

Board::Board() {
	initBoard();
}

void Board::initBoard() {
	// ��ʼ������
	board_map = std::vector<std::vector<Camp>>(MAX_ROW, std::vector<Camp>(MAX_COL, EMPTY));
	// �����±߽�����Ϊ��ɫ
	for (int i = 0; i < MAX_COL; i++) {
		board_map[0][i] = RED;
		board_map[MAX_ROW - 1][i] = RED;
	}
	// �����ұ߽�����Ϊ��ɫ
	for (int i = 0; i < MAX_ROW; i++) {
		board_map[i][0] = BLUE;
		board_map[i][MAX_COL - 1] = BLUE;
	}

	board_map[0][0] = EMPTY;
	board_map[0][MAX_COL - 1] = EMPTY;
	board_map[MAX_ROW - 1][0] = EMPTY;
	board_map[MAX_ROW - 1][MAX_COL - 1] = EMPTY;

}


bool Board::checkOutOfBounds(int _row, int _col) const {
	if (_row <= 0 || _row >= MAX_ROW - 1 ||
		_col <= 0 || _col >= MAX_COL - 1) {
		return true;
	}
	else {
		return false;
	}
}

bool Board::checkEmpty(int _row, int _col) const {
	return board_map[_row][_col] == EMPTY;
}

int Board::setColor(int _row, int _col, Camp _camp) {
	if (checkOutOfBounds(_row, _col) == true || checkEmpty(_row, _col) == false) {
		return -1;
	}
	else {
		board_map[_row][_col] = _camp;
		return 1;
	}
}

void Board::printTest() const {
	for (std::vector<Camp> row : board_map) {
		for (Camp camp : row) {
			std::cout << camp << ' ';
		}
		std::cout << '\n';
	}
}