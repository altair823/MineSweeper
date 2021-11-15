#include "Board.h"

Board::Board(ScenePtr bg) {
	// 보드는 오직 하나의 객체만 허용가능하다. 
	if (boardCount != 0) {
		std::cout << "싱글톤 보드 클래스의 또 다른 객체가 생성되었습니다!" << std::endl;
		exit(1);
	}
	boardCount++;
	background = bg;
	row = 0, col = 0;

	// 아이템 클래스의 아이템 객체
	item = std::make_shared<Item>(background, 3);
}


void Board::RefreshBoard(int newRow, int newCol) {
	// 반드시 클리어 시에만 이 함수를 호출할 것!
	if (OnBlockBreak->getStatus() == BoardStatus::Playing) {
		std::cout << "클리어되지 못한 보드의 초기화가 발생했습니다." << std::endl;
		exit(1);
	}
	else if (OnBlockBreak->getStatus() == BoardStatus::GameOver) {
		std::cout << "게임오버된 보드의 초기화가 발생했습니다." << std::endl;
		exit(1);
	}
	Clear();
	GenerateNewBoard(newRow, newCol);
}

void Board::Clear() {
	// cell 초기화
	// cells 초기화
	for (int i = 0; i < row; i++) {
		cells[i].clear();
	}
	cells.clear();

	row = 0;
	col = 0;

	// 보드가 초기화될 때마다 이벤트 핸들러 루프 정지
	OnBlockBreak->StopCheckNewCellOpened();
	// 보드가 초기화될 때마다 이벤트 핸들러 객체 제거
	OnBlockBreak.reset();
}

void Board::GenerateNewBoard(int newRow, int newCol) {
	if (row != 0 || col != 0) {
		std::cout << "보드에 이미 데이터가 존재합니다!" << std::endl;
		exit(1);
	}

	row = newRow;
	col = newCol;

	// 보드가 새로 생성될 때마다 새로운 이벤트 핸들러 객체 생성
	OnBlockBreak = std::make_shared<BlockBreakHandler>(row, col, field, cells, item, background);

	// field 재생성
	field.Resize(row, col);
	field.MountMine();
	field.setAdjacentNum();
	field.Print();

	// cells에 새 데이터 저장
	for (int i = 0; i < row; i++) {
		std::vector<CellPtr> cellRow;
		for (int j = 0; j < col; j++) {
			// cell의 x, y 좌표 계산. 
			int x = (640 - col / 2 * CELL_SIZE) + j * CELL_SIZE;
			int y = (360 + row / 2 * CELL_SIZE) - (i + 1) * CELL_SIZE;
			CellPtr cell = Cell::Create(background, field[i][j], x, y);
			

			// Item의 정보를 셀의 콜백 함수가 참조해야 함
			cell->getBlock()->setClickCallback([=](auto object, int x, int y, auto action)->bool {
				switch (item->getCurrentHand())
				{
				default:
					break;
				}
				// 핸드가 곡괭이일 경우
				if (item->getCurrentHand() == Hand::Pickax) {
					cell->BreakBlock();
				}
				// 핸드가 깃발일경우
				else if (item->getCurrentHand() == Hand::Flag) {
					cell->getBlock()->SwapBlockImage();
				}
				// 현재 선택한 아이템이 detector일 경우
				else if (item->getCurrentHand() == Hand::Detector) {
					if (item->getItemCount(Hand::Detector) > 0) {
						UseDetector(i, j);
						item->ReduceItem(Hand::Detector);
						item->ChangeHand(Hand::Pickax);
					}
				}
				
				return true;
				});


			cellRow.push_back(cell);
		}
		cells.push_back(cellRow);
	}

	// 새로 생성된 보드는 플레이 상태로 전환됨.
	OnBlockBreak->setStatus(BoardStatus::Playing);

	// 새 보드 생성이 완료되면 이벤트 핸들러의 루프 시작
	OnBlockBreak->CheckNewCellOpened();
}

void Board::UseDetector(int clickedCellRow, int clickedCellCol) {
	// 클릭한 칸의 주위 9칸을 확인
	for (int i = clickedCellRow - 1; i <= clickedCellRow + 1; i++) {
		if (i < 0 || i >= row) {
			continue;
		}
		for (int j = clickedCellCol - 1; j <= clickedCellCol + 1; j++) {
			if (j < 0 || j >= col) {
				continue;
			}
			switch (field[i][j].cellValue) {
			case CellValue::Mine:
				cells[i][j]->getBlock()->ChangeToFlagImage();
				break;
			default:
				cells[i][j]->BreakBlock();
				break;
			}
		}
	}
}

BoardStatus Board::getBoardStatus() {
	return OnBlockBreak->getStatus();
}

int Board::getRow() {
	return row;
}

int Board::getCol() {
	return col;
}

