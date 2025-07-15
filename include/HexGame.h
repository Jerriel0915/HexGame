#ifndef HEXGAME_H
#define HEXGAME_H

#include "Board.h"
#include "HexRecord.h"
#include <stack>

class HexGame {
private:
	Board* board = new Board();			//< 棋盘
	Camp camp = EMPTY;					//< 当前阵营
	int step = 0;						//< 已经过的步数
	std::stack<HexRecord*> records;		//< 记录
public:
	HexGame() = default;
	~HexGame() = default;
	const Camp getCamp() const;
	const int getStep() const;
	/**
	 * @brief 往记录栈中添加一条记录
	 * @param _record 本次记录
	 */
	void addRecord(HexRecord* _record);
	/**
	 * @brief 往记录栈中添加一条记录
	 * @param _row 行
	 * @param _col 列
	 * @param _camp 阵营
	 */
	void addRecord(int _row, int _col, Camp _camp);


public:
	void runTest();
};

#endif // !HEXGAME_H