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
	memset(_vis, 0, sizeof(_vis)); // ��ʼ����������

	// ���췽����������DFS
	for (int i = 0; i < MAX_COL; i++) {
		if (_board_map[0][i] == RED) {
			if (checkWinDFS(_board_map, _vis, 0, i, RED)) {
				return RED; // �췽��ʤ
			}
		}
	}

	// �����������������DFS
	for (int i = 0; i < MAX_ROW; i++) {
		if (_board_map[i][0] == BLUE) {
			if (checkWinDFS(_board_map, _vis, i, 0, BLUE)) {
				return BLUE; // ������ʤ
			}
		}
	}

	return EMPTY; // ���˻�ʤ
}

bool Board::checkWinDFS(std::vector<std::vector<Camp>>& _board_map, bool(&_vis)[MAX_ROW][MAX_COL], int _row, int _col, Camp _camp) const {
	// ����Ѿ����ʹ���λ�ã��򷵻�false
	if (_vis[_row][_col]) {
		return false;
	}
	// �����λ�ò��ǵ�ǰ��Ӫ���򷵻�false
	if (_board_map[_row][_col] != _camp) {
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
		if (checkWinDFS(_board_map, _vis, next_row, next_col, _camp)) {
			return true; // ����ҵ�һ����ͨ·�����򷵻�true
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

	return Board(new_board_map, next_turn, winner, is_terminal); // �����µ�����״̬
}

std::vector<Board> Board::find_children() const {
	std::vector<Board> children;
	if (terminal) {
		return children; // �������̬�����ؿ�����
	}
	
	for (int _row = 1; _row <= MAX_ROW - 2; _row++) {
		for (int _col = 1; _col <= MAX_ROW - 2; _col++) {
			if (board_map[_row][_col] == EMPTY) {
				children.emplace_back(make_move(_row, _col));
			}
		}
	}
	return children; // ���������ӽڵ�
}


Board Board::find_random_child() const {
	if (terminal) {
		return *this; // �������̬�����ص�ǰ״̬
	}
	// �����
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
	return make_move(_row, _col); // ��������ӽڵ�
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
				return false; // ֻҪ��һ���ո񣬾Ͳ���ȫ���
			}
		}
	}
	return true; // ȫ�����Ӷ������
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