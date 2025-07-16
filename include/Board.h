#ifndef BOARD_H
#define BOARD_H

#include "GLOBAL.h"
#include <vector>

class Board {
private:
	/**
	 * @brief 棋盘，其中上下边界为红方，左右边界为蓝方
	 */
	std::vector<std::vector<Camp>> board_map;
	/**
	 * @brief 表示当前持子阵营
	 */
	Camp turn;
	/**
	 * @brief 获胜阵营
	 */
	Camp winner;
	/**
	 * @brief 是否为终态
	 */
	bool terminal;

public:
	Board() : board_map(), turn(EMPTY), winner(EMPTY), terminal(false) {}
	Board(std::vector<std::vector<Camp>> _board_map, Camp _turn, Camp _winner, bool _terminal) :
		board_map(_board_map), turn(_turn), winner(_winner), terminal(_terminal) {}
	~Board() = default;
	bool operator==(const Board& other) const {
		return board_map == other.board_map &&
			turn == other.turn;
	}
/**
 * @brief 检查数组访问是否越界
 * @param _row 行坐标
 * @param _col 列坐标
 * @return ture:访问位置非法
 */
bool checkOutOfBounds(int _row, int _col) const;

/**
 * @brief 检查棋盘位置是否为空
 * @param _row 行坐标
 * @param _col 列坐标
 * @return 访问位置为空
 */

/**
 * @brief 检查获胜
 * @return (Camp) EMPTY:无人获胜 RED:红方获胜 BLUE:蓝方获胜
 */
Camp checkWin(std::vector<std::vector<Camp>>& _board_map) const;

/**
 * @brief 执行移动
 * @param _row
 * @param _col
 * @return 新的棋盘状态
 */
Board make_move(int _row, int _col) const;

/**
 * @brief 查找当前棋盘状态的所有子节点（即所有可能的下一步）
 * @return vector<Board>
 */
std::vector<Board> find_children() const;

/**
 * @brief
 * @return
 */
Board find_random_child() const;

/**
 * @brief 计算当前棋盘状态的奖励值
 * @return 奖励值
 */
float reward(Camp perspective) const;

bool is_terminal() const;
Camp getTurn() const;
bool all_filled(const std::vector<std::vector<Camp>>& _board_map) const;

struct Hash {
	size_t operator()(const Board& _board) const {
		size_t h = 0;
		for (const auto& row : _board.board_map) {
			for (const auto& cell : row) {
				h ^= std::hash<int>()(cell) + 0x9e3779b9 + (h << 6) + (h >> 2);
			}
		}
		return h ^ std::hash<int>()(_board.turn);
	}
};

private:
	/**
	 * @brief checkWin()辅助函数，使用DFS
	 * @param _vis 历史访问
	 * @param _row 行
	 * @param _col 列
	 * @param _camp 阵营
	 * @return 满足获胜条件
	 */
	bool checkWinDFS(std::vector<std::vector<Camp>>& _board_map, bool(&_vis)[MAX_ROW][MAX_COL], int _row, int _col, Camp _camp) const;

public:
	void printTest() const;
};



#endif // !BOARD_H