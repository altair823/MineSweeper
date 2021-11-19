#include "Board.h"

Board::Board(ScenePtr bg, int initLifeCount) {
	// ����� ���� �ϳ��� ��ü�� ��밡���ϴ�. 
	if (boardCount != 0) {
		std::cout << "�̱��� ���� Ŭ������ �� �ٸ� ��ü�� �����Ǿ����ϴ�!" << std::endl;
		exit(1);
	}
	boardCount++;
	background = bg;
	row = 0, col = 0;

	InitItem(initLifeCount);
}


void Board::RefreshBoard(int newRow, int newCol, int stageNum) {
	// �ݵ�� Ŭ���� �ÿ��� �� �Լ��� ȣ���� ��!
	if (status == BoardStatus::Playing) {
		std::cout << "Ŭ������� ���� ������ �ʱ�ȭ�� �߻��߽��ϴ�." << std::endl;
		exit(1);
	}
	else if (status == BoardStatus::GameOver) {
		std::cout << "���ӿ����� ������ �ʱ�ȭ�� �߻��߽��ϴ�." << std::endl;
		exit(1);
	}
	Clear();
	GenerateNewBoard(newRow, newCol, stageNum);
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

void Board::GenerateNewBoard(int newRow, int newCol, int stageNum) {
	if (row != 0 || col != 0) {
		std::cout << "A regeneration of the board that did not clear data has occurred!" << std::endl;
		exit(1);
	}

	row = newRow;
	col = newCol;

	// ���尡 ���� ������ ������ ���ο� �̺�Ʈ �ڵ鷯 ��ü ����
	OnBlockBreak = std::make_shared<BlockBreakHandler>(row, col, field, cells, item, background, status);

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
			CellPtr cell = Cell::Create(background, field[i][j], x, y, stageNum);
			

			// ���� hand�� ���� �ٸ� �۵��� �Ѵ�. 
			cell->getBlock()->setClickCallback([=](auto object, int x, int y, auto action)->bool {
				switch (item->getCurrentHand()) {
				case Hand::Pickax:
					cell->BreakBlock();
					break;
				case Hand::Flag:
					cell->getBlock()->SwapBlockImage();
					break;
				case Hand::Detector:
					item->UseDetector(i, j, cells, field);
					break;
				default:
					break;
				}
				
				return true;
				});


			cellRow.push_back(cell);
		}
		cells.push_back(cellRow);
	}

	// ���� ������ ����� �÷��� ���·� ��ȯ��.
	OnBlockBreak->setStatus(BoardStatus::Playing);

	// �� ���� ������ �Ϸ�Ǹ� �̺�Ʈ �ڵ鷯�� ���� ����
	OnBlockBreak->CheckNewCellOpened();
}

void Board::InitItem(int initLifeCount) {
	if (item != nullptr) {
		item.reset();
	}
	// ���ο� ������ ��ü ����
	item = std::make_shared<Item>(background, initLifeCount);
}

BoardStatus Board::getBoardStatus() {
	return status;
}

int Board::getRow() {
	return row;
}

int Board::getCol() {
	return col;
}

void Board::setBoardStatus(BoardStatus status) {
	this->status = status;
}

