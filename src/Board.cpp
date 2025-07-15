#include "../include/Board.h"
#include <iostream>

Board::Board() {
	initBoard();
}

void Board::initBoard() {
	// 初始化棋盘
	board_map = std::vector<std::vector<Camp>>(MAX_ROW, std::vector<Camp>(MAX_COL, EMPTY));
	// 将上下边界设置为红色
	for (int i = 0; i < MAX_COL; i++) {
		board_map[0][i] = RED;
		board_map[MAX_ROW - 1][i] = RED;
	}
	// 将左右边界设置为蓝色
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
	memset(_vis, 0, sizeof(_vis)); // 初始化访问数组

	// 检查红方，从上至下DFS
	for (int i = 0; i < MAX_COL; i++) {
		if (board_map[0][i] == RED) {
			if (checkWinDFS(_vis, 0, i, RED)) {
				return RED; // 红方获胜
			}
		}
	}

	// 检查蓝方，从左至右DFS
	for (int i = 0; i < MAX_ROW; i++) {
		if (board_map[i][0] == BLUE) {
			if (checkWinDFS(_vis, i, 0, BLUE)) {
				return BLUE; // 蓝方获胜
			}
		}
	}

	return EMPTY; // 无人获胜
}

bool Board::checkWinDFS(bool (&_vis)[MAX_ROW][MAX_COL], int _row, int _col, Camp _camp) {
	// 如果已经访问过该位置，则返回false
	if (_vis[_row][_col]) {
		return false;
	}
	// 如果该位置不是当前阵营，则返回false
	if (board_map[_row][_col] != _camp) {
		return false;
	}

	_vis[_row][_col] = 1;	//< 标记该位置已访问

	// 红方到达下边界
	if (_camp == RED && _row == MAX_ROW - 2) {
		return true;
	}
	// 蓝方到达右边界
	if (_camp == BLUE && _col == MAX_COL - 2) {
		return true;
	}

	// DFS
	for (int k = 0; k < 6; k++) {
		int next_row = _row + D_X[k];
		int next_col = _col + D_Y[k];
		// 越界检查
		if (checkOutOfBounds(next_row, next_col)) {
			continue;
		}
		if (checkWinDFS(_vis, next_row, next_col, _camp)) {
			return true; // 如果找到一条连通路径，则返回true
		}
	}
	return false;
}


void Board::printTest() const {
	for (int y = 1; y <= MAX_ROW - 2; ++y) {
		std::cout << std::string(y - 1, ' ');          // 左侧缩进
		for (int x = 1; x <= MAX_COL - 2; ++x) {
			std::cout << " " << board_map[y][x];
		}
		std::cout << '\n';
	}
	std::cout << '\n';
}