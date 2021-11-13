#include "Board.h"

Board::Board(ScenePtr bg) {
	// ����� ���� �ϳ��� ��ü�� ��밡���ϴ�. 
	if (boardCount != 0) {
		std::cout << "�̱��� ���� Ŭ������ �� �ٸ� ��ü�� �����Ǿ����ϴ�!" << std::endl;
		exit(1);
	}
	boardCount++;
	background = bg;
	row = 0, col = 0;

	// ������ Ŭ������ ������ ��ü
	itemObject = new Item(background);

	// ������ ��ü�� ���� Ű���� �ݹ�
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
		}
		if (KeyCode == KeyCode::KEY_5 && pressed == true) {
			itemObject->ChangeHand(4);
		}
		if (KeyCode == KeyCode::KEY_6 && pressed == true) {
			itemObject->ChangeHand(5);
		}
		return true;
		});
}


void Board::RefreshBoard(int newRow, int newCol) {
	// �ݵ�� Ŭ���� �ÿ��� �� �Լ��� ȣ���� ��!
	if (OnBlockBreak->getStatus() == Status::Playing) {
		std::cout << "Ŭ������� ���� ������ �ʱ�ȭ�� �߻��߽��ϴ�." << std::endl;
		exit(1);
	}
	else if (OnBlockBreak->getStatus() == Status::GameOver) {
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
			int x = (640 - col / 2 * CELL_SIZE) + j * CELL_SIZE;
			int y = (360 + row / 2 * CELL_SIZE) - (i + 1) * CELL_SIZE;
			CellPtr cell = Cell::Create(background, field[i][j], x, y);
			

			// Item�� ������ ���� �����Ϸ��� ���� �����԰� ���ÿ� �� ���� ��Ͽ� ���� ���콺 �ݹ鵵 �Բ� �����ؾ���
			cell->getBlock()->setClickCallback([=](auto object, int x, int y, auto action)->bool {
				if (itemObject->getHand() == Hand::Pickax) {
					cell->BreakBlock();
				}
				else if (itemObject->getHand() == Hand::Flag) {
					cell->getBlock()->ChangeBlockImage();
				}
				return true;
				});


			cellRow.push_back(cell);
		}
		cells.push_back(cellRow);
	}

	// ���� ������ ����� �÷��� ���·� ��ȯ��.
	OnBlockBreak->setStatus(Status::Playing);

	// ���� ������ ����� ������ ��� ������ �̾� ����
	OnBlockBreak->setLife(life);

	// �� ���� ������ �Ϸ�Ǹ� �̺�Ʈ �ڵ鷯�� ���� ����
	OnBlockBreak->CheckNewCellOpened();
}

Status Board::getBoardStatus() {
	return OnBlockBreak->getStatus();
}

int Board::getRow() {
	return row;
}

int Board::getCol() {
	return col;
}

