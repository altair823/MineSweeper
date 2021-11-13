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
	itemObject = new Item(background);

	// 아이템 객체에 대한 키보드 콜백
	bg -> setOnKeyboardCallback([&](auto bg, auto KeyCode, auto pressed)->bool {
		if (KeyCode == KeyCode::KEY_1 && pressed == true) {
			itemObject->ChangeHand(0);
		}
		if (KeyCode == KeyCode::KEY_2 && pressed == true) {
			itemObject->ChangeHand(1);
		}
		if (KeyCode == KeyCode::KEY_3 && pressed == true) {
			itemObject->ChangeHand(2);
		}
		if (KeyCode == KeyCode::KEY_4 && pressed == true) {
			itemObject->ChangeHand(3);
			if (itemObject->getItemNumber(Hand::Heart) > 0) {
				// 이곳에서 Heart 아이템의 효과를 호출한다.

				// Heart의 아이템 개수를 1개 줄인다.
				itemObject->ReduceItem(Hand::Heart);
			}
			else {
				showMessage("아이템이 없습니다.");
			}
		}
		if (KeyCode == KeyCode::KEY_5 && pressed == true) {
			itemObject->ChangeHand(4);
			if (itemObject->getItemNumber(Hand::Spray) > 0) {
				// 이곳에서 Spray 아이템의 효과를 호출한다.

				// Spray의 아이템 개수를 1개 줄인다.
				itemObject->ReduceItem(Hand::Spray);
			}
			else {
				showMessage("아이템이 없습니다.");
			}
		}
		if (KeyCode == KeyCode::KEY_6 && pressed == true) {
			itemObject->ChangeHand(5);
		}
		return true;
		});
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
	OnBlockBreak = std::make_shared<BlockBreakHandler>(row, col, field, cells, background);

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
			

			// Item의 정보를 셀이 참조하려면 셀을 생성함과 동시에 그 셀의 블록에 대한 마우스 콜백도 함께 생성해야함
			cell->getBlock()->setClickCallback([=](auto object, int x, int y, auto action)->bool {
				// 핸드가 곡괭이일 경우
				if (itemObject->getHand() == Hand::Pickax) {
					cell->BreakBlock();
				}
				// 핸드가 깃발일경우
				else if (itemObject->getHand() == Hand::Flag) {
					cell->getBlock()->ChangeBlockImage();
				}
				// 핸드가 TNT일 경우
				else if (itemObject->getHand() == Hand::Tnt) {
					if (itemObject->getItemNumber(Hand::Tnt) > 0) {
						// 이곳에서 아이템의 효과를 호출한다.

						// TNT의 아이템 개수를 1개 줄인다.
						itemObject->ReduceItem(Hand::Tnt);
					}
					else {
						showMessage("아이템이 없습니다.");
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

BoardStatus Board::getBoardStatus() {
	return OnBlockBreak->getStatus();
}

int Board::getRow() {
	return row;
}

int Board::getCol() {
	return col;
}

