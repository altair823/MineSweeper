#include "Cell.h"

std::shared_ptr<_cell> Cell::Create(ScenePtr bg, FieldData fieldData, int row, int col, Hand* handPtr)
{
	// x, y ��ǥ ���. 
	// �������� ������ ���ؼ��� ������ ũ�⿡ ���� �� ���� ����� �ٲ��� �Ѵ�. 
	int x = (col + 1) * CELL_SIZE + 100;
	int y = -(row + 1) * CELL_SIZE + 420;


	// ���ο� ĭ ��ü ����
	std::shared_ptr<_cell> newCell(new _cell(bg, fieldData, x, y, handPtr));
	return newCell;
}

_cell::_cell(ScenePtr bg, FieldData fieldData, int x, int y, Hand* handPtr) {
	cellObject = Object::create(CellResource::EMPTY, bg, x, y);
	// ���� �Ǵ� ���ڿ� ���� �̹��� ����
	ChangeNumImage(fieldData);

	//������ ĭ�� ���� ���� �� ��ü ����
	block = Block::Create(bg, x, y);

	//����ü�� ���� MouseCallback �Լ� ����
	MakeBlockCallback(block);

	//�ڵ�������
	this->handPtr = handPtr;
}

void _cell::ChangeNumImage(FieldData fieldData) {

	switch (fieldData.cellValue) {
		// ����ĭ�� ���
	case CellValue::Mine:
		cellObject->setImage(CellResource::MINE);
		return;
		// Ż�ⱸ�� ���
	case CellValue::Escape:
		cellObject->setImage(CellResource::ESCAPE);
		return;
	default:
		break;
	}

	switch (fieldData.num) {

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
		if (*handPtr == Hand::Pickax) {
			BreakBlock(block);
		}
		else if (*handPtr == Hand::Flag) {
			block->ChangeBlockImage();
		}
		return true;
		});
}

void _cell::BreakBlock(BlockPtr block) {
	block->hideBlock();
	isOpened = true;
}