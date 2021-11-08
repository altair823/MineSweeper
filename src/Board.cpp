#include "Board.h"

Board::Board(ScenePtr bg) {
	// ����� ���� �ϳ��� ��ü�� ��밡���ϴ�. 
	if (boardCount != 0) {
		std::cout << "�̱��� ���� Ŭ������ �� �ٸ� ��ü�� �����Ǿ����ϴ�!" << std::endl;
		exit(1);
	}
	boardCount++;
	status = Status::Clear;
	background = bg;
	row = 0, col = 0;

	

	/*
	* ���� ��Ȳ �׽�Ʈ�� ���� �ڵ�.
	*/
	/*
	ObjectPtr testObject = Object::create(CombatResource::MONSTER1, background, 30, 30);
	testObject->show();
	testObject->setOnMouseCallback([&](auto, auto, auto, auto)->bool {

		Combat* testCombat = new DiceMatching(background);
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
		RefreshBoard(row + 3, col + 3);
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
	// �ݵ�� Ŭ���� �ÿ��� �� �Լ��� ȣ���� ��!
	if (status == Status::Playing) {
		std::cout << "Ŭ������� ���� ������ �ʱ�ȭ�� �߻��߽��ϴ�." << std::endl;
		exit(1);
	}
	else if (status == Status::GameOver) {
		std::cout << "���ӿ����� ������ �ʱ�ȭ�� �߻��߽��ϴ�." << std::endl;
		exit(1);
	}
	Clear();
	GenerateNewBoard(newRow, newCol);
}

void Board::Clear() {

	// cell �ʱ�ȭ
	// cells �ʱ�ȭ
	for (int i = 0; i < row; i++) {
		cells[i].clear();
	}
	cells.clear();

	row = 0;
	col = 0;

	// ���尡 �ʱ�ȭ�� ������ �̺�Ʈ �ڵ鷯 ���� ����
	OnBlockBreak->StopCheckNewCellOpened();
	// ���尡 �ʱ�ȭ�� ������ �̺�Ʈ �ڵ鷯 ��ü ����
	OnBlockBreak.reset();
}

void Board::GenerateNewBoard(int newRow, int newCol) {
	if (row != 0 || col != 0) {
		std::cout << "���忡 �̹� �����Ͱ� �����մϴ�!" << std::endl;
		exit(1);
	}
	// int, row�� ���� Ŭ���� �ÿ� ���ŵȴ�.
	if (status == Status::Clear) {
		row = newRow;
		col = newCol;
		// ���尡 ���� ������ ������ ���ο� �̺�Ʈ �ڵ鷯 ��ü ����
		OnBlockBreak = std::make_shared<BlockBreakHandler>(row, col, field, cells);
	}

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

	// ���� ������ ����� �÷��� ���·� ��ȯ��.
	status = Status::Playing;

	OnBlockBreak->CheckNewCellOpened();
}

