#include "Board.h"

Board::Board(ScenePtr bg) {
	status = Status::Playing;

	background = bg;
	// ��, �� �׽�Ʈ ��
	row = BOARD_SIZE, col = BOARD_SIZE;

	// ���� ���� �׽�Ʈ
	field.Resize(row, col);
	field.MountMine();
	field.setAdjacentNum();
	field.Print();

	// ĭ ���� �׽�Ʈ
	for (int i = 0; i < row; i++) {
		std::vector<CellPtr> cellRow;
		for (int j = 0; j < col; j++) {
			CellPtr cell = Cell::Create(bg, field[i][j], i, j, &hand);
			cellRow.push_back(cell);
		}
		cells.push_back(cellRow);
	}

	/*
	* ���� ��Ȳ �׽�Ʈ�� ���� �ڵ�.
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

	// �ڵ� ��Ʈ�� ��ü
	handObject = Object::create(HandResource::PICKAX, background, 430, 430);
	handObject->setOnMouseCallback([&](auto object, int x, int y, auto action)->bool {
		HandChange();
		return true;
		});

	// ** ����׿� ** ���� ��ư ���� �� ���콺 �ݹ� ���
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
	// �� �Լ��� �Ҹ��� ���� �ݵ�� �� ������ ���۵Ǵ� ������ Playing ��Ȳ������ �Ҹ� �� ����.
	if (status == Status::Playing) {
		std::cout << "����ġ ���� ���� �ʱ�ȭ�� �߻��߽��ϴ�." << std::endl;
		exit(1);
	}

	// cell �ʱ�ȭ
	// cells ������ ����
	for (int i = 0; i < row; i++) {
		cells[i].clear();
	}
	cells.clear();

	// int, row�� ���� Ŭ���� �ÿ� ���ŵȴ�.
	if (status == Status::Clear) {
		// ch�� �����ϴ� ����� ���Ƿ� ���ο� ���� �����ϴ� ������ ��. �̹������� �����ϴ� ��ĵ� ��� ����
		row += 5;
		col += 5;
	}

	/*
	// ���� ���� �ÿ��� ���� ���������� �ٽ� �÷����ϰų� Ÿ��Ʋ�� ���ư��� ��ĵ� ��� ����
	if (stat == Status::GameOver) {
	}
	*/

	// field �ʱ�ȭ
	field.Resize(row, col);
	field.MountMine();
	field.setAdjacentNum();
	field.Print();

	// cells�� �� ������ ����
	for (int i = 0; i < row; i++) {
		std::vector<CellPtr> cellRow;
		for (int j = 0; j < col; j++) {
			CellPtr cell = Cell::Create(background, field[i][j], i, j, &hand);
			cellRow.push_back(cell);
		}
		cells.push_back(cellRow);
	}
}

