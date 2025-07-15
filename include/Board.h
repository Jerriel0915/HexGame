#ifndef BOARD_H
#define BOARD_H

#include "GLOBAL.h"
#include <vector>
#include <cstring>

class Board {
private:
	std::vector<std::vector<Camp>> board_map;		// 棋盘

public:
	Board();
	~Board() = default;
	/**
	 * @brief 初始化棋盘
	 */
	void initBoard();
	/**
	 * @brief 检查数组访问是否越界
	 * @param _row 行坐标
	 * @param _col 列坐标
	 * @return 访问位置非法
	 */
	bool checkOutOfBounds(int _row, int _col) const;
	/**
	 * @brief 检查棋盘位置是否为空
	 * @param _row 行坐标
	 * @param _col 列坐标
	 * @return 访问位置为空
	 */
	bool checkEmpty(int _row, int _col) const;

	/**
	 * @brief 为指定棋盘位置设定阵营(颜色)
	 * @param row 行坐标
	 * @param col 列坐标
	 * @param camp 阵营(枚举类型)
	 * @return -1:设置失败 0:设置成功
	 */
	int setColor(int _row, int _col, Camp _camp);

public:
	void printTest() const ;
};



#endif // !BOARD_H