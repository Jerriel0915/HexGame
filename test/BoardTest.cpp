//#include "../include/Board.h"
//#include <iostream>
//
//int main() {
//	Board board;
//
//	// ���Գ�ʼ������
//	board.initBoard();
//	std::cout << "���̳�ʼ����ɡ�" << std::endl;
//
//	// ���Ի�ʤ���
//	for (int i = 0; i < MAX_ROW; i++) {
//		board.setColor(i, 1, RED);
//	}
//
//	Camp winner = board.checkWin();
//
//	if (winner == EMPTY) {
//		std::cout << "��ǰ���˻�ʤ��" << std::endl;
//	}
//	else if (winner == RED) {
//		std::cout << "�췽��ʤ��" << std::endl;
//	}
//	else if (winner == BLUE) {
//		std::cout << "������ʤ��" << std::endl;
//	}
//
//	return 0;
//}