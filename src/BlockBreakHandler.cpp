#include "BlockBreakHandler.h"

BlockBreakHandler::BlockBreakHandler(int newRow, int newCol, MineField& newField, std::vector<std::vector<CellPtr>>& newCells)
	: row(newRow), col(newCol), field(newField), cells(newCells) {

	// ��� isCellOpen�� ����(false)�� �ʱ�ȭ
	isCellOpen.resize(row);
	for (auto& i : isCellOpen) {
		i.resize(col);
		for (auto j : i) {
			j = false;
		}
	}
}

void BlockBreakHandler::CheckNewCellOpened() {
	// �� Ÿ�̸Ӱ� ���鼭 ���� ���� ĭ�� �����ϴ��� üũ�Ѵ�. 
	// REFRESH_TIME�� �ʹ� ����ϸ� �������� ��������, 
	// �ʹ� ª���ϸ� ���ҽ��� ����ġ�� ��Ƹ��� �� �ִ�. 
	refreshTimer = Timer::create(REFRESH_TIME);
	refreshTimer->setOnTimerCallback([&](auto)->bool {
		for (int i = 0; i < row; i++) {
			for (int j = 0; j < col; j++) {
				if (cells[i][j]->getIsOpened() != isCellOpen[i][j]) {

					// ����׿� ���
					// �� �κп� Combat, �Ǵ� ��ĭ Ȯ�� �޼��带 ������ ��
					std::cout << "row: " << i << ", col: " << j << 
						"\ncellValue: " << field[i][j].cellValue << ", num: " << field[i][j].num << ", itemValue: " << field[i][j].itemValue << std::endl;
					isCellOpen[i][j] = true;
				}
			}
		}
		refreshTimer->set(REFRESH_TIME);
		refreshTimer->start();
		return true;
		});

	refreshTimer->start();
	// ����׿� Ÿ�̸� ���� �޼���
	std::cout << "Successfully maked a new handler loop" << std::endl;
}

void BlockBreakHandler::StopCheckNewCellOpened() {
	refreshTimer->stop();
}

BlockBreakHandler::~BlockBreakHandler() {
	// ��� �����͸� �����ϰ� ����
	for (auto& i : isCellOpen) {
		i.clear();
	}
	isCellOpen.clear();
}


