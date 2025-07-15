//#include "../include/Board.h"
//#include <iostream>
//
//int main() {
//	Board board;
//
//	// 测试初始化棋盘
//	board.initBoard();
//	std::cout << "棋盘初始化完成。" << std::endl;
//
//	// 测试获胜检查
//	for (int i = 0; i < MAX_ROW; i++) {
//		board.setColor(i, 1, RED);
//	}
//
//	Camp winner = board.checkWin();
//
//	if (winner == EMPTY) {
//		std::cout << "当前无人获胜。" << std::endl;
//	}
//	else if (winner == RED) {
//		std::cout << "红方获胜！" << std::endl;
//	}
//	else if (winner == BLUE) {
//		std::cout << "蓝方获胜！" << std::endl;
//	}
//
//	return 0;
//}