#ifndef GLOBAL_H
#define GLOBAL_H

static const int MAX_ROW = 13;
static const int MAX_COL = 13;

/**
 * @brief 阵营信息 EMPTY=0; RED=1; BLUE=2
 */
enum Camp {
	EMPTY = 0,
	RED = 1,
	BLUE = 2
};

static const int D_X[6] = { 0, 1, 1, 0, -1, -1 };	//< 横向位移
static const int D_Y[6] = { -1, 0, -1, 1, 0, 1 };	//< 纵向位移

#endif // !GLOBAL_H