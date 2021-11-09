#include "BlockBreakHandler.h"

BlockBreakHandler::BlockBreakHandler(int newRow, int newCol, MineField& newField, std::vector<std::vector<CellPtr>>& newCells)
	: row(newRow), col(newCol), field(newField), cells(newCells) {

	// 모든 isCellOpen을 닫힘(false)로 초기화
	isCellOpen.resize(row);
	for (auto& i : isCellOpen) {
		i.resize(col);
		for (auto j : i) {
			j = false;
		}
	}
}

void BlockBreakHandler::CheckNewCellOpened() {
	// 이 타이머가 돌면서 새로 열린 칸이 존재하는지 체크한다. 
	// REFRESH_TIME을 너무 길게하면 반응성이 떨어지고, 
	// 너무 짧게하면 리소스를 지나치게 잡아먹을 수 있다. 
	refreshTimer = Timer::create(REFRESH_TIME);
	refreshTimer->setOnTimerCallback([&](auto)->bool {
		for (int i = 0; i < row; i++) {
			for (int j = 0; j < col; j++) {
				if (cells[i][j]->getIsOpened() != isCellOpen[i][j]) {

					// 디버그용 출력
					// 이 부분에 Combat, 또는 빈칸 확장 메서드를 연결할 것
					std::cout << "row: " << i << ", col: " << j << 
						"\ncellValue: " << field[i][j].cellValue << ", num: " << field[i][j].num << ", itemValue: " << field[i][j].itemValue << std::endl;
					isCellOpen[i][j] = true;
					//  빈 칸 확장 메서드
					// 새로 열린 칸이 빈칸이라면 이하의 빈칸 확장 과정을 진행한다.
					if (field[i][j].cellValue == CellValue::Empty && field[i][j].num == 0) { // itemValue와 관련된 조건 추가 필요!
						ExpandBorder(i, j);
					}
				}
			}
		}
		refreshTimer->set(REFRESH_TIME);
		refreshTimer->start();
		return true;
		});

	refreshTimer->start();
	// 디버그용 타이머 생성 메세지
	std::cout << "Successfully maked a new handler loop" << std::endl;
}

void BlockBreakHandler::ExpandBorder(int i, int j) {
	// k는 확장될 칸의 row 위치이다.
	for (int k = i - 1; k <= i + 1; k++) {
		// 위치가 범위를 벗어나면 진행하지 않는다.
		if (k < 0 || k >= row) {
			continue;
		}
		else {
			// l은 확장될 칸의 col 위치이다.
			for (int l = j - 1; l <= j + 1; l++) {
				// 위치가 범위를 벗어나면 진행하지 않는다.
				if (l < 0 || l >= col) {
					continue;
				}
				// 아직 열리지 않은 칸이고 숫자 칸이라면 연다.
				else if (cells[k][l]->getIsOpened() == false && field[k][l].cellValue == CellValue::Empty) {
					cells[k][l]->BreakBlock(cells[k][l]->getBlock());
				}
			}
		}
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
}
