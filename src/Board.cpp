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

	// �ڵ� ��Ʈ�� ��ü
	handObject = Object::create(HandResource::PICKAX, background, 1000, 600);
	handObject->setOnMouseCallback([&](auto object, int x, int y, auto action)->bool {
		HandChange();
		return true;
		});

	// ** ����׿� ** ���� ��ư ���� �� ���콺 �ݹ� ���
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

	row = newRow;
	col = newCol;

	// ���尡 ���� ������ ������ ���ο� �̺�Ʈ �ڵ鷯 ��ü ����
	OnBlockBreak = std::make_shared<BlockBreakHandler>(row, col, field, cells);

	// field �����
	field.Resize(row, col);
	field.MountMine();
	field.setAdjacentNum();
	field.Print();

	// cells�� �� ������ ����
	for (int i = 0; i < row; i++) {
		std::vector<CellPtr> cellRow;
		for (int j = 0; j < col; j++) {
			// cell�� x, y ��ǥ ���. 
			int x = (640 - row / 2 * CELL_SIZE) + j * CELL_SIZE;
			int y = (360 + col / 2 * CELL_SIZE) - (i + 1) * CELL_SIZE;
			CellPtr cell = Cell::Create(background, field[i][j], x, y, &hand);
			cellRow.push_back(cell);
		}
		cells.push_back(cellRow);
	}

	// ���� ������ ����� �÷��� ���·� ��ȯ��.
	status = Status::Playing;

	// �� ���� ������ �Ϸ�Ǹ� �̺�Ʈ �ڵ鷯�� ���� ����
	OnBlockBreak->CheckNewCellOpened();
}

