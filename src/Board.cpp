#include "Board.h"

Board::Board(ScenePtr bg) {
	background = bg;
	// 행, 열 테스트 값
	int row = 10, col = 10;

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
