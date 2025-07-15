#ifndef GLOBAL_H
#define GLOBAL_H

static const int MAX_ROW = 13;
static const int MAX_COL = 13;

/**
 * @brief ��Ӫ��Ϣ EMPTY=0; RED=1; BLUE=2
 */
enum Camp {
	EMPTY = 0,
	RED = 1,
	BLUE = 2
};

static const int D_X[6] = { 0, 1, 1, 0, -1, -1 };	//< ����λ��
static const int D_Y[6] = { -1, 0, -1, 1, 0, 1 };	//< ����λ��

#endif // !GLOBAL_H