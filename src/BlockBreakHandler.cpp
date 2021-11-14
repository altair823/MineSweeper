#include "BlockBreakHandler.h"

BlockBreakHandler::BlockBreakHandler(int& newRow, int& newCol, MineField& newField, std::vector<std::vector<CellPtr>>& newCells, 
	std::shared_ptr<Item> item, ScenePtr boardBackground)
	: row(newRow), col(newCol), field(newField), cells(newCells), item(item), boardBackground(boardBackground) {

	// ��� isCellOpen�� ����(false)�� �ʱ�ȭ
	isCellOpen.resize(row);
	for (auto& i : isCellOpen) {
		i.resize(col);
		for (auto j : i) {
			j = false;
		}
	}
}

BoardStatus BlockBreakHandler::getStatus() {
	return status;
}

void BlockBreakHandler::setStatus(BoardStatus stat) {
	status = stat;
}

void BlockBreakHandler::CheckNewCellOpened() {
	// �� Ÿ�̸Ӱ� ���鼭 ���� ���� ĭ�� �����ϴ��� üũ�Ѵ�. 
	refreshTimer = Timer::create(REFRESH_TIME);
	refreshTimer->setOnTimerCallback([&](auto)->bool {
		for (int i = 0; i < row; i++) {
			for (int j = 0; j < col; j++) {
				if (cells[i][j]->getIsOpened() != isCellOpen[i][j]) {

					isCellOpen[i][j] = true;
#ifndef DEBUG
					EnterRandomCombat(i, j);
#endif // !DEBUG
					CheckIsItemExist(i, j);

					RefreshBoardStatus(i, j);
					
					ExpandBorder(i, j);
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

void BlockBreakHandler::CheckIsItemExist(int curRow, int curCol) {
	if (field[curRow][curCol].itemValue != ItemValue::None) {
		item->AddItem(field[curRow][curCol].itemValue);
	}
}

void BlockBreakHandler::EnterRandomCombat(int curRow, int curCol) {
	if (field[curRow][curCol].cellValue != CellValue::Mine) {
		return;
	}
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<int> dis(0, 4);

	// ���� ���ε��� �̿��� ������������ ������Ȳ ����
	switch (dis(gen)) {
	case 0:
		newCombat = new RockPaperScissor(boardBackground);
		break;
	case 1:
		newCombat = new OddOrEven(boardBackground);
		break;
	case 2:
		newCombat = new DiceRolling(boardBackground);
		break;
	case 3:
		newCombat = new ShootTheMonster(boardBackground);
		break;
	case 4:
		newCombat = new DiceMatching(boardBackground);
		break;
	default:
		break;
	}
	if (newCombat != nullptr) {
		newCombat->EnterBattle();
	}
}
void BlockBreakHandler::ExpandBorder(int curRow, int curCol) {
	// itemValue�� ���õ� ���� �߰� �ʿ�!
	// ���� ���� ĭ�� ��ĭ�̶��, �� ���� ĭ�� ��ĭ �Ǵ� ����ĭ���� Ȯ���Ѵ�. 
	if (field[curRow][curCol].cellValue == CellValue::Empty && field[curRow][curCol].num == 0) {
		for (int i = curRow - 1; i <= curRow + 1; i++) {
			if (i < 0 || i >= row) {
				continue;
			}
			else {
				for (int j = curCol - 1; j <= curCol + 1; j++) {
					if (j < 0 || j >= col) {
						continue;
					}
					// ���� ������ ���� ĭ�̰� ��ĭ �Ǵ� ���� ĭ�̶�� ����.
					else if (cells[i][j]->getIsOpened() == false && field[i][j].cellValue == CellValue::Empty) {
						cells[i][j]->BreakBlock();
						CheckIsItemExist(i, j);
					}
				}
			}
		}
	}
}

void BlockBreakHandler::RefreshBoardStatus(int curRow, int curCol) {
	// GameOver
	// ���� ����� ���ٸ� ������ ���¸� GameOver�� �ٲ۴�.


	// Escape
	// ���� ���� ĭ�� Ż�ⱸ�̸� ���� ���¸� Escape�� �ٲ۴�.
	if (field[curRow][curCol].cellValue == CellValue::Escape) {
		status = BoardStatus::Escape;
	}

	// Clear
	// ���� ĭ�� ������ ��� ĭ�� �������� ���� ���¸� Clear�� �ٲ۴�.
	bool isCleared = true;
	for (int i = 0; (i < row) && (isCleared == true); i++) {
		for (int j = 0; (j < col) && (isCleared == true); j++) {
			// ���� ĭ�� ������ ĭ �� ������ ���� ĭ�� �ִٸ� 
			// ���� Clear ���°� �ƴϴ�. 
			if (field[i][j].cellValue != CellValue::Mine && isCellOpen[i][j] == false) {
				isCleared = false;
				break;
			}
		}
	}
	// ��ȸ�� ���� �Ŀ��� ���尡 Clear������ �����ϸ� ������ ���¸� �����Ѵ�.
	if (isCleared == true) {
		status = BoardStatus::Clear;
	}
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
	delete newCombat;
}
