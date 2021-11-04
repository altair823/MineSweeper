#include "Cell.h"

std::shared_ptr<_cell> Cell::Create(ScenePtr bg, int cellValue, int row, int col)
{
	// x, y ��ǥ ���. 
	// �������� ������ ���ؼ��� ������ ũ�⿡ ���� �� ���� ����� �ٲ��� �Ѵ�. 
	int x = (col + 1) * CELL_SIZE + 100;
	int y = -(row + 1) * CELL_SIZE + 420;


	// ���ο� ĭ ��ü ����
	std::shared_ptr<_cell> newCell(new _cell(bg, cellValue, x, y));
	return newCell;
}

_cell::_cell(ScenePtr bg, int cellValue, int x, int y) {
	cellObject = Object::create(CellResource::EMPTY, bg, x, y);
	// ���� �Ǵ� ���ڿ� ���� �̹��� ����
	ChangeNumImage(cellValue);

	//������ ĭ�� ���� ���� �� ��ü ����
	BlockPtr block = Block::Create(bg, cellValue, x, y);

	//����ü�� ���� MouseCallback �Լ� ����
	MakeBlockCallback(block);
}

void _cell::ChangeNumImage(int num) {
	if (isThisMine == true) {
		return;
	}

	switch (num) {
	// ����ĭ�� ���
	case CellValue::Mine:
		cellObject->setImage(CellResource::MINE);
		break;

	// ������ ���
	case 1:
		cellObject->setImage(CellResource::ONE);
		break;
	case 2:
		cellObject->setImage(CellResource::TWO);
		break;
	case 3:
		cellObject->setImage(CellResource::THREE);
		break;
	case 4:
		cellObject->setImage(CellResource::FOUR);
		break;
	case 5:
		cellObject->setImage(CellResource::FIVE);
		break;
	case 6:
		cellObject->setImage(CellResource::SIX);
		break;
	case 7:
		cellObject->setImage(CellResource::SEVEN);
		break;
	case 8:
		cellObject->setImage(CellResource::EIGHT);
		break;

	// ��ĭ�� ���
	default:
		break;
	}
}

void _cell::MakeBlockCallback(BlockPtr block) {
	block->setClickCallback([=](auto object, int x, int y, auto action)->bool {
		block->hideBlock();

		return true;
	});
}