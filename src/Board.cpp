#include "Board.h"

Board::Board(ScenePtr bg) {
	status = Status::Playing;

	background = bg;
	// 행, 열 테스트 값
	row = BOARD_SIZE, col = BOARD_SIZE;

	// 지뢰 생성 테스트
	field.Resize(row, col);
	field.MountMine();
	field.setAdjacentNum();
	field.Print();

	// 칸 생성 테스트
	for (int i = 0; i < row; i++) {
		std::vector<CellPtr> cellRow;
		for (int j = 0; j < col; j++) {
			CellPtr cell = Cell::Create(bg, field[i][j], i, j, &hand);
			cellRow.push_back(cell);
		}
		cells.push_back(cellRow);
	}

	/*
	* 전투 상황 테스트를 위한 코드.
	*/
	/*
	ObjectPtr testObject = Object::create(CombatResource::MONSTER1, background, 30, 30);
	testObject->show();
	testObject->setOnMouseCallback([&](auto, auto, auto, auto)->bool {

		Combat* testCombat = new DiceRolling(background);
		testCombat->EnterBattle();
		return true;
		});
	*/

	// 핸드 컨트롤 객체
	handObject = Object::create(HandResource::PICKAX, background, 430, 430);
	handObject->setOnMouseCallback([&](auto object, int x, int y, auto action)->bool {
		HandChange();
		return true;
		});

	// ** 디버그용 ** 리셋 버튼 생성 및 마우스 콜백 등록
	resetButton = Object::create(BlockResource::BLOCK, background, 0, 0);
	resetButton->setOnMouseCallback([&](auto object, int x, int y, auto action)->bool {
		status = Status::Clear;
		RefreshBoard();
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

void Board::RefreshBoard() {
	// 이 함수가 불리는 경우는 반드시 새 게임이 시작되는 상으로 Playing 상황에서는 불릴 수 없다.
	if (status == Status::Playing) {
		std::cout << "예상치 못한 보드 초기화가 발생했습니다." << std::endl;
		exit(1);
	}

	// cell 초기화
	// cells 데이터 삭제
	for (int i = 0; i < row; i++) {
		cells[i].clear();
	}
	cells.clear();

	// int, row는 게임 클리어 시에 갱신된다.
	if (status == Status::Clear) {
		// ch를 갱신하는 방식은 임의로 새로운 씬을 생성하는 것으로 함. 이미지만을 변경하는 방식도 고려 가능
		row += 5;
		col += 5;
	}

	/*
	// 게임 오버 시에는 같은 스테이지를 다시 플레이하거나 타이틀로 돌아가는 방식도 고려 가능
	if (stat == Status::GameOver) {
	}
	*/

	// field 초기화
	field.Resize(row, col);
	field.MountMine();
	field.setAdjacentNum();
	field.Print();

	// cells에 새 데이터 저장
	for (int i = 0; i < row; i++) {
		std::vector<CellPtr> cellRow;
		for (int j = 0; j < col; j++) {
			CellPtr cell = Cell::Create(background, field[i][j], i, j, &hand);
			cellRow.push_back(cell);
		}
		cells.push_back(cellRow);
	}
}

