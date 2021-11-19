#include "BlockBreakHandler.h"

BlockBreakHandler::BlockBreakHandler(int& newRow, int& newCol, MineField& newField, std::vector<std::vector<CellPtr>>& newCells, 
	std::shared_ptr<Item> item, ScenePtr boardBackground, BoardStatus& status)
	: row(newRow), col(newCol), field(newField), cells(newCells), item(item), boardBackground(boardBackground), status(status) {

	// 모든 isCellOpen을 닫힘(false)로 초기화
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
	// 이 타이머가 돌면서 새로 열린 칸이 존재하는지 체크한다. 
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
	// 빈칸이면
	if (field[curRow][curCol].cellValue != CellValue::Mine) {
		return;
	}
	// 스프레이를 사용중이면
	else if (item->getIsSprayUsed()) {
		item->UseSpray();
		showMessage("스프레이의 효과로 몬스터를 피했습니다!");
		return;
	}
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<int> dis(0, 4);

	// 동적 바인딩을 이용해 무작위로 전투상황 진입
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
		showMessage("전투에서 패배하여 목숨이 하나 줄었습니다...");
	}
	else {
		setStatus(BoardStatus::GameOver);
	}
}
void BlockBreakHandler::ExpandBorder(int curRow, int curCol) {
	// 새로 열린 칸이 빈칸이라면, 그 주위 칸이 확장될 수 있는지 확인한다.
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
					// 아직 열리지 않은 칸이고 지뢰가 아닌 칸이라면 연다.
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
	// 남은 목숨이 없다면 보드의 상태를 GameOver로 바꾼다.
	if (item->getLifeCount() == 0) {
		setStatus(BoardStatus::GameOver);
	}

	// Escape
	// 새로 열린 칸이 탈출구이면 보드 상태를 Escape로 바꾼다.
	if (field[curRow][curCol].cellValue == CellValue::Escape) {
		setStatus(BoardStatus::Escape);
	}

	// Clear
	// 지뢰 칸을 제외한 모든 칸이 열렸으면 보드 상태를 Clear로 바꾼다.
	bool isCleared = true;
	for (int i = 0; (i < row) && (isCleared == true); i++) {
		for (int j = 0; (j < col) && (isCleared == true); j++) {
			// 지뢰 칸을 제외한 칸 중 열리지 않은 칸이 있다면 
			// 아직 Clear 상태가 아니다. 
			if (field[i][j].cellValue != CellValue::Mine && isCellOpen[i][j] == false) {
				isCleared = false;
				break;
			}
		}
	}
	// 순회가 끝난 후에도 보드가 Clear조건을 만족하면 보드의 상태를 갱신한다.
	if (isCleared == true) {
		setStatus(BoardStatus::Clear);
	}
}

void BlockBreakHandler::StopCheckNewCellOpened() {
	refreshTimer->stop();
}

BlockBreakHandler::~BlockBreakHandler() {
	// 모든 데이터를 안전하게 제거
	for (auto& i : isCellOpen) {
		i.clear();
	}
	isCellOpen.clear();
	delete newCombat;
}
