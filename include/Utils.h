#ifndef UTILS_H
#define UTILS_H

#include "../include/GLOBAL.h"
#include <vector>

static class Utils {
public:
	static std::vector<std::vector<Camp>> initBoard() {
		// 初始化棋盘
		std::vector<std::vector<Camp>> new_board_map = std::vector<std::vector<Camp>>(MAX_ROW, std::vector<Camp>(MAX_COL, EMPTY));
		// 将上下边界设置为红色
		for (int i = 0; i < MAX_COL; i++) {
			new_board_map[0][i] = RED;
			new_board_map[MAX_ROW - 1][i] = RED;
		}
		// 将左右边界设置为蓝色
		for (int i = 0; i < MAX_ROW; i++) {
			new_board_map[i][0] = BLUE;
			new_board_map[i][MAX_COL - 1] = BLUE;
		}

		new_board_map[0][0] = EMPTY;
		new_board_map[0][MAX_COL - 1] = EMPTY;
		new_board_map[MAX_ROW - 1][0] = EMPTY;
		new_board_map[MAX_ROW - 1][MAX_COL - 1] = EMPTY;

		return new_board_map;
	}
};

#endif // !UTILS_H