#include "BlockBreakHandler.h"

BlockBreakHandler::BlockBreakHandler(int& newRow, int& newCol, MineField& newField, std::vector<std::vector<CellPtr>>& newCells, 
	std::shared_ptr<Item> item, ScenePtr boardBackground, BoardStatus& status)
	: row(newRow), col(newCol), field(newField), cells(newCells), item(item), boardBackground(boardBackground), status(status) {

	// ��� isCellOpen�� ����(false)�� �ʱ�ȭ
	isCellOpen.resize(row);
	for (auto& i : isCellOpen) {
		i.resize(col);
		for (auto j : i) {
			j = false;
		}
	}
}

void BlockBreakHandler::setStatus(BoardStatus status) {
	this->status = status;
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
}

void BlockBreakHandler::CheckIsItemExist(int curRow, int curCol) {
	if (field[curRow][curCol].itemValue != ItemValue::None) {
		item->AddItem(field[curRow][curCol].itemValue);
		field[curRow][curCol].itemValue = ItemValue::None;
	}
}

void BlockBreakHandler::EnterRandomCombat(int curRow, int curCol) {
	// ��ĭ�̸�
	if (field[curRow][curCol].cellValue != CellValue::Mine) {
		return;
	}
	// �������̸� ������̸�
	else if (item->getIsSprayUsed()) {
		item->UseSpray();
		showMessage("���������� ȿ���� ���͸� ���߽��ϴ�!");
		return;
	}
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<int> dis(0, 4);

	// ���� ���ε��� �̿��� �������� ������Ȳ ����
	switch (dis(gen)) {
	case 0:
		newCombat = new RockPaperScissor(boardBackground, *this, &BlockBreakHandler::looseCombat);
		break;
	case 1:
		newCombat = new OddOrEven(boardBackground, *this, &BlockBreakHandler::looseCombat);
		break;
	case 2:
		newCombat = new DiceRolling(boardBackground, *this, &BlockBreakHandler::looseCombat);
		break;
	case 3:
		newCombat = new ShootTheMonster(boardBackground, *this, &BlockBreakHandler::looseCombat);
		break;
	case 4:
		newCombat = new DiceMatching(boardBackground, *this, &BlockBreakHandler::looseCombat);
		break;
	default:
		break;
	}
	if (newCombat != nullptr) {
		newCombat->EnterBattle();
	}
}
void BlockBreakHandler::looseCombat() {
	item->ReduceLifeCount();
	if (item->getLifeCount() > 0) {
		boardBackground->enter();
		showMessage("�������� �й��Ͽ� ����� �ϳ� �پ����ϴ�...");
	}
	else {
		setStatus(BoardStatus::GameOver);
	}
}
void BlockBreakHandler::ExpandBorder(int curRow, int curCol) {
	// ���� ���� ĭ�� ��ĭ�̶��, �� ���� ĭ�� Ȯ��� �� �ִ��� Ȯ���Ѵ�.
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
					// ���� ������ ���� ĭ�̰� ���ڰ� �ƴ� ĭ�̶�� ����.
					else if (cells[i][j]->getIsOpened() == false && field[i][j].cellValue != CellValue::Mine) {
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
	if (item->getLifeCount() == 0) {
		setStatus(BoardStatus::GameOver);
	}

	// Escape
	// ���� ���� ĭ�� Ż�ⱸ�̸� ���� ���¸� Escape�� �ٲ۴�.
	if (field[curRow][curCol].cellValue == CellValue::Escape) {
		setStatus(BoardStatus::Escape);
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
		setStatus(BoardStatus::Clear);
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
