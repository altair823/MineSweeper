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
	item = std::make_shared<Item>(background, 3);
}


void Board::RefreshBoard(int newRow, int newCol) {
	// �ݵ�� Ŭ���� �ÿ��� �� �Լ��� ȣ���� ��!
	if (OnBlockBreak->getStatus() == BoardStatus::Playing) {
		std::cout << "Ŭ������� ���� ������ �ʱ�ȭ�� �߻��߽��ϴ�." << std::endl;
		exit(1);
	}
	else if (OnBlockBreak->getStatus() == BoardStatus::GameOver) {
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
	OnBlockBreak = std::make_shared<BlockBreakHandler>(row, col, field, cells, item, background);

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
			

			// Item�� ������ ���� �ݹ� �Լ��� �����ؾ� ��
			cell->getBlock()->setClickCallback([=](auto object, int x, int y, auto action)->bool {
				switch (item->getCurrentHand())
				{
				default:
					break;
				}
				// �ڵ尡 ����� ���
				if (item->getCurrentHand() == Hand::Pickax) {
					cell->BreakBlock();
				}
				// �ڵ尡 ����ϰ��
				else if (item->getCurrentHand() == Hand::Flag) {
					cell->getBlock()->SwapBlockImage();
				}
				// ���� ������ �������� detector�� ���
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

	// ���� ������ ����� �÷��� ���·� ��ȯ��.
	OnBlockBreak->setStatus(BoardStatus::Playing);

	// �� ���� ������ �Ϸ�Ǹ� �̺�Ʈ �ڵ鷯�� ���� ����
	OnBlockBreak->CheckNewCellOpened();
}

void Board::UseDetector(int clickedCellRow, int clickedCellCol) {
	// Ŭ���� ĭ�� ���� 9ĭ�� Ȯ��
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

