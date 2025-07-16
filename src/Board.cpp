#include "../include/Board.h"
#include <iostream>
#include <random>
#include <stdexcept>
#include <algorithm>

bool Board::checkOutOfBounds(int _row, int _col) const {
	if (_row <= 0 || _row >= MAX_ROW - 1 ||
		_col <= 0 || _col >= MAX_COL - 1) {
		return true;
	}
	else {
		return false;
	}
}

Camp Board::checkWin(std::vector<std::vector<Camp>>& _board_map) const {
	bool _vis[MAX_COL][MAX_ROW];
	memset(_vis, 0, sizeof(_vis)); // 初始化访问数组

	// 检查红方，从上至下DFS
	for (int i = 0; i < MAX_COL; i++) {
		if (_board_map[0][i] == RED) {
			if (checkWinDFS(_board_map, _vis, 0, i, RED)) {
				return RED; // 红方获胜
			}
		}
	}

	// 检查蓝方，从左至右DFS
	for (int i = 0; i < MAX_ROW; i++) {
		if (_board_map[i][0] == BLUE) {
			if (checkWinDFS(_board_map, _vis, i, 0, BLUE)) {
				return BLUE; // 蓝方获胜
			}
		}
	}

	return EMPTY; // 无人获胜
}

bool Board::checkWinDFS(std::vector<std::vector<Camp>>& _board_map, bool(&_vis)[MAX_ROW][MAX_COL], int _row, int _col, Camp _camp) const {
	// 如果已经访问过该位置，则返回false
	if (_vis[_row][_col]) {
		return false;
	}
	// 如果该位置不是当前阵营，则返回false
	if (_board_map[_row][_col] != _camp) {
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
		if (checkWinDFS(_board_map, _vis, next_row, next_col, _camp)) {
			return true; // 如果找到一条连通路径，则返回true
		}
	}
	return false;
}

Board Board::make_move(int _row, int _col) const {
	if (checkOutOfBounds(_row, _col)) {
		return *this;
	}

	std::vector<std::vector<Camp>> new_board_map = board_map;
	new_board_map[_row][_col] = turn;
	Camp next_turn = (turn == RED) ? BLUE : RED;
	Camp winner = checkWin(new_board_map);
	bool is_terminal = (winner != EMPTY) || all_filled(new_board_map);

	return Board(new_board_map, next_turn, winner, is_terminal); // 返回新的棋盘状态
}

std::vector<Board> Board::find_children() const {
	std::vector<Board> children;
	if (terminal) {
		return children; // 如果是终态，返回空向量
	}
	
	for (int _row = 1; _row <= MAX_ROW - 2; _row++) {
		for (int _col = 1; _col <= MAX_ROW - 2; _col++) {
			if (board_map[_row][_col] == EMPTY) {
				children.emplace_back(make_move(_row, _col));
			}
		}
	}
	return children; // 返回所有子节点
}


Board Board::find_random_child() const {
	if (terminal) {
		return *this; // 如果是终态，返回当前状态
	}
	// 随机数
	std::random_device rd;
	std::mt19937 gen(rd());

	std::vector<std::pair<int, int>> positions;
	for (int _row = 1; _row <= MAX_ROW - 2; _row++) {
		for (int _col = 1; _col <= MAX_COL - 2; _col++) {
			if (board_map[_row][_col] == EMPTY) {
				positions.emplace_back(_row, _col);
			}
		}
	}
	std::uniform_int_distribution<> dist(0, positions.size() - 1);
	int random_index = dist(gen);
	int _row = positions[random_index].first;
	int _col = positions[random_index].second;
	return make_move(_row, _col); // 返回随机子节点
}

float Board::reward(Camp perspective) const {
	if (!terminal) {
		throw std::runtime_error("reward called on non-terminal board!");
	}
	if (winner == perspective) {
		return 1.0;
	}
	else if (winner == EMPTY) {
		return 0.5;
	}
	else {
		return 0.0;
	}
}

bool Board::is_terminal() const {
	return terminal;
}

Camp Board::getTurn() const {
	return turn;
}

bool Board::all_filled(const std::vector<std::vector<Camp>>& _board_map) const {
	for (const auto& row : _board_map) {
		for (const auto& cell : row) {
			if (cell == EMPTY) {
				return false; // 只要有一个空格，就不是全填充
			}
		}
	}
	return true; // 全部格子都被填充
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