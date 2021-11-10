#include "Board.h"

Board::Board(ScenePtr bg) {
	// 보드는 오직 하나의 객체만 허용가능하다. 
	if (boardCount != 0) {
		std::cout << "싱글톤 보드 클래스의 또 다른 객체가 생성되었습니다!" << std::endl;
		exit(1);
	}
	boardCount++;
	status = Status::Clear;
	background = bg;
	row = 0, col = 0;

	// 핸드 컨트롤 객체
	handObject = Object::create(HandResource::PICKAX, background, 1000, 600);
	handObject->setOnMouseCallback([&](auto object, int x, int y, auto action)->bool {
		HandChange();
		return true;
		});

	// ** 디버그용 ** 리셋 버튼 생성 및 마우스 콜백 등록
	resetButton = Object::create(BlockResource::BLOCK, background, 0, 0);
	resetButton->setOnMouseCallback([&](auto object, int x, int y, auto action)->bool {
		status = Status::Clear;
		RefreshBoard(row + 4, col + 4);
		return true;
		});
}


void Board::HandChange() {
	if (hand == Hand::Pickax) {
		handObject->setImage(HandResource::FLAG);
		hand = Hand::Flag;
	}
	else if (hand == Hand::Flag) {
		handObject->setImage(HandResource::PICKAX);
		hand = Hand::Pickax;
	}
}

void Board::RefreshBoard(int newRow, int newCol) {
	// 반드시 클리어 시에만 이 함수를 호출할 것!
	if (status == Status::Playing) {
		std::cout << "클리어되지 못한 보드의 초기화가 발생했습니다." << std::endl;
		exit(1);
	}
	else if (status == Status::GameOver) {
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
	OnBlockBreak = std::make_shared<BlockBreakHandler>(row, col, field, cells);

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
			int x = (640 - row / 2 * CELL_SIZE) + j * CELL_SIZE;
			int y = (360 + col / 2 * CELL_SIZE) - (i + 1) * CELL_SIZE;
			CellPtr cell = Cell::Create(background, field[i][j], x, y, &hand);
			cellRow.push_back(cell);
		}
		cells.push_back(cellRow);
	}

	// 새로 생성된 보드는 플레이 상태로 전환됨.
	status = Status::Playing;

	// 새 보드 생성이 완료되면 이벤트 핸들러의 루프 시작
	OnBlockBreak->CheckNewCellOpened();
}

