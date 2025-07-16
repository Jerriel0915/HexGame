#ifndef BOARD_H
#define BOARD_H

#include "GLOBAL.h"
#include <vector>

class Board {
private:
	/**
	 * @brief ���̣��������±߽�Ϊ�췽�����ұ߽�Ϊ����
	 */
	std::vector<std::vector<Camp>> board_map;
	/**
	 * @brief ��ʾ��ǰ������Ӫ
	 */
	Camp turn;
	/**
	 * @brief ��ʤ��Ӫ
	 */
	Camp winner;
	/**
	 * @brief �Ƿ�Ϊ��̬
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
 * @brief �����������Ƿ�Խ��
 * @param _row ������
 * @param _col ������
 * @return ture:����λ�÷Ƿ�
 */
bool checkOutOfBounds(int _row, int _col) const;

/**
 * @brief �������λ���Ƿ�Ϊ��
 * @param _row ������
 * @param _col ������
 * @return ����λ��Ϊ��
 */

/**
 * @brief ����ʤ
 * @return (Camp) EMPTY:���˻�ʤ RED:�췽��ʤ BLUE:������ʤ
 */
Camp checkWin(std::vector<std::vector<Camp>>& _board_map) const;

/**
 * @brief ִ���ƶ�
 * @param _row
 * @param _col
 * @return �µ�����״̬
 */
Board make_move(int _row, int _col) const;

/**
 * @brief ���ҵ�ǰ����״̬�������ӽڵ㣨�����п��ܵ���һ����
 * @return vector<Board>
 */
std::vector<Board> find_children() const;

/**
 * @brief
 * @return
 */
Board find_random_child() const;

/**
 * @brief ���㵱ǰ����״̬�Ľ���ֵ
 * @return ����ֵ
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
	 * @brief checkWin()����������ʹ��DFS
	 * @param _vis ��ʷ����
	 * @param _row ��
	 * @param _col ��
	 * @param _camp ��Ӫ
	 * @return �����ʤ����
	 */
	bool checkWinDFS(std::vector<std::vector<Camp>>& _board_map, bool(&_vis)[MAX_ROW][MAX_COL], int _row, int _col, Camp _camp) const;

public:
	void printTest() const;
};



#endif // !BOARD_H