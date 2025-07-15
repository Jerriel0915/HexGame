#ifndef HEXGAME_H
#define HEXGAME_H

#include "Board.h"
#include "HexRecord.h"
#include <stack>

class HexGame {
private:
	Board* board = new Board();			//< ����
	Camp camp = EMPTY;					//< ��ǰ��Ӫ
	int step = 0;						//< �Ѿ����Ĳ���
	std::stack<HexRecord*> records;		//< ��¼
public:
	HexGame() = default;
	~HexGame() = default;
	const Camp getCamp() const;
	const int getStep() const;
	/**
	 * @brief ����¼ջ�����һ����¼
	 * @param _record ���μ�¼
	 */
	void addRecord(HexRecord* _record);
	/**
	 * @brief ����¼ջ�����һ����¼
	 * @param _row ��
	 * @param _col ��
	 * @param _camp ��Ӫ
	 */
	void addRecord(int _row, int _col, Camp _camp);


public:
	void runTest();
};

#endif // !HEXGAME_H