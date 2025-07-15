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
	std::cout << "ѡ����Ӫ��1�췽��2����" << std::endl;
	std::cin >> camp;
	while (true) {
		std::cout << "��ǰ����Ϊ " << step << " ��ӪΪ ";
		if (camp == RED) {
			std::cout << "�췽" << std::endl;
		}
		else {
			std::cout << "����" << std::endl;
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
			std::cout << "���ӷǷ��������ԣ�" << std::endl;
		}
		system("cls");
	}
}