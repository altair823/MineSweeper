#include "Cell.h"

std::shared_ptr<_cell> Cell::Create(ScenePtr bg, FieldData fieldData, int x, int y) {
	// ���ο� ĭ ��ü ����
	std::shared_ptr<_cell> newCell(new _cell(bg, fieldData, x, y));
	return newCell;
}

_cell::_cell(ScenePtr bg, FieldData fieldData, int x, int y) {
	cellObject = Object::create(CellResource::EMPTY, bg, x, y);
	// ���� �Ǵ� ���ڿ� ���� �̹��� ����
	ChangeNumImage(fieldData);

	// ������ �̹��� ����
	switch (fieldData.itemValue) {
	case ItemValue::MineDetector:
		itemValue = ItemValue::MineDetector;
		itemObject = Object::create(ItemResource::DETECTOR, bg, x, y);
		itemObject->setScale(0.35f);
		break;
	case ItemValue::AvoidCombat:
		itemValue = ItemValue::AvoidCombat;
		itemObject = Object::create(ItemResource::SPRAY, bg, x+6, y);
		itemObject->setScale(0.35f);
		break;
	case ItemValue::AddLife:
		itemValue = ItemValue::AddLife;
		itemObject = Object::create(ItemResource::ADD_LIFE, bg, x+4, y);
		itemObject->setScale(0.02f);
		break;
	default:
		break;
	}

	//������ ĭ�� ���� ���� �� ��ü ����
	block = Block::Create(bg, x, y);
}

void _cell::ChangeNumImage(FieldData fieldData) {
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

}

void _cell::BreakBlock() {
	if (this->block->HideBlock()) {
		isOpened = true;
	}
}

bool _cell::getIsOpened(){
	return isOpened;
}

BlockPtr _cell::getBlock() {
	return block;
}

ItemValue _cell::getItemValue() {
	return itemValue;
}
