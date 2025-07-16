#ifndef BOARD_H
#define BOARD_H

#include "GLOBAL.h"
#include <vector>
#include <cstring>

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
	Board(std::vector<std::vector<Camp>> _board_map, Camp _turn, Camp _winner, bool _terminal) :
		board_map(_board_map), turn(_turn), winner(_winner), terminal(_terminal) {}
	~Board() = default;

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
	bool checkEmpty(int _row, int _col) const;

	/**
	 * @brief Ϊָ������λ���趨��Ӫ(��ɫ)
	 * @param row ������
	 * @param col ������
	 * @param camp ��Ӫ(ö������)
	 * @return -1:����ʧ�� 0:���óɹ�
	 */
	int setColor(int _row, int _col, Camp _camp);

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
	double reward() const;

	bool is_terminal() const;
	Camp getTurn() const;

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