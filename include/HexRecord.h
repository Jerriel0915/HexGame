#ifndef RECORD_H
#define RECORD_H

#include "GLOBAL.h"

class HexRecord {
private:
	int row;
	int col;
	Camp camp;

public:
	/**
	 * @brief 
	 * @param _row ÐÐ
	 * @param _col ÁÐ
	 * @param _camp ÕóÓª
	 */
	HexRecord(int _row, int _col, Camp _camp) : row(_row), col(_col), camp(_camp) {}

};

#endif // !RECORD_H