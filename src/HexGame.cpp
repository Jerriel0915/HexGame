#include "../include/HexGame.h"
#include <iostream>

const Camp HexGame::getCamp() const {
	return this->camp;
}

const int HexGame::getStep() const {
	return this->step;
}

void HexGame::addRecord(HexRecord* _record) {
	records.push(_record);
}

void HexGame::addRecord(int _row, int _col, Camp _camp) {
	HexRecord* record = new HexRecord(_row, _col, _camp);
	addRecord(record);
}


void HexGame::runTest() {
	int camp = EMPTY;
	step++;
	std::cout << "选择阵营：1红方；2蓝方" << std::endl;
	std::cin >> camp;
	while (true) {
		std::cout << "当前步数为 " << step << " 阵营为 ";
		if (camp == RED) {
			std::cout << "红方" << std::endl;
		}
		else {
			std::cout << "蓝方" << std::endl;
		}

		board->printTest();

		int row, col;
		std::cin >> row >> col;
		if (board->setColor(row, col, Camp(camp)) != -1) {
			camp == RED ? camp = BLUE : camp = RED;
			step++;
			records.push(new HexRecord(row, col, (Camp)camp));
		}
		else {
			std::cout << "落子非法！请重试！" << std::endl;
		}
		system("cls");
	}
}