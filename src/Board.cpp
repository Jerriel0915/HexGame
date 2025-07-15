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
	if (_camp == EMPTY) {
		return -1;
	}
	if (checkOutOfBounds(_row, _col) == true || checkEmpty(_row, _col) == false) {
		return -1;
	}
	else {
		board_map[_row][_col] = _camp;
		return 1;
	}
}

Camp Board::checkWin() {
	bool _vis[MAX_COL][MAX_ROW];
	memset(_vis, 0, sizeof(_vis)); // ��ʼ����������

	// ���췽����������DFS
	for (int i = 0; i < MAX_COL; i++) {
		if (board_map[0][i] == RED) {
			if (checkWinDFS(_vis, 0, i, RED)) {
				return RED; // �췽��ʤ
			}
		}
	}

	// �����������������DFS
	for (int i = 0; i < MAX_ROW; i++) {
		if (board_map[i][0] == BLUE) {
			if (checkWinDFS(_vis, i, 0, BLUE)) {
				return BLUE; // ������ʤ
			}
		}
	}

	return EMPTY; // ���˻�ʤ
}

bool Board::checkWinDFS(bool (&_vis)[MAX_ROW][MAX_COL], int _row, int _col, Camp _camp) {
	// ����Ѿ����ʹ���λ�ã��򷵻�false
	if (_vis[_row][_col]) {
		return false;
	}
	// �����λ�ò��ǵ�ǰ��Ӫ���򷵻�false
	if (board_map[_row][_col] != _camp) {
		return false;
	}

	_vis[_row][_col] = 1;	//< ��Ǹ�λ���ѷ���

	// �췽�����±߽�
	if (_camp == RED && _row == MAX_ROW - 2) {
		return true;
	}
	// ���������ұ߽�
	if (_camp == BLUE && _col == MAX_COL - 2) {
		return true;
	}

	// DFS
	for (int k = 0; k < 6; k++) {
		int next_row = _row + D_X[k];
		int next_col = _col + D_Y[k];
		// Խ����
		if (checkOutOfBounds(next_row, next_col)) {
			continue;
		}
		if (checkWinDFS(_vis, next_row, next_col, _camp)) {
			return true; // ����ҵ�һ����ͨ·�����򷵻�true
		}
	}
	return false;
}


void Board::printTest() const {
	for (int y = 1; y <= MAX_ROW - 2; ++y) {
		std::cout << std::string(y - 1, ' ');          // �������
		for (int x = 1; x <= MAX_COL - 2; ++x) {
			std::cout << " " << board_map[y][x];
		}
		std::cout << '\n';
	}
	std::cout << '\n';
}