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

public:
	Board();
	~Board() = default;
	/**
	 * @brief ��ʼ������
	 */
	void initBoard();
	/**
	 * @brief �����������Ƿ�Խ��
	 * @param _row ������
	 * @param _col ������
	 * @return ����λ�÷Ƿ�
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
	Camp checkWin();



private:
	/**
	 * @brief checkWin()����������ʹ��DFS
	 * @param _vis ��ʷ����
	 * @param _row ��
	 * @param _col ��
	 * @param _camp ��Ӫ
	 * @return �����ʤ����
	 */
	bool checkWinDFS(bool (&_vis)[MAX_ROW][MAX_COL], int _row, int _col, Camp _camp);

public:
	void printTest() const ;
};



#endif // !BOARD_H