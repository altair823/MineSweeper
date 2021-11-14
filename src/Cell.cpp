#include "Cell.h"

std::shared_ptr<_cell> Cell::Create(ScenePtr bg, FieldData fieldData, int x, int y) {
	// 새로운 칸 객체 생성
	std::shared_ptr<_cell> newCell(new _cell(bg, fieldData, x, y));
	return newCell;
}

_cell::_cell(ScenePtr bg, FieldData fieldData, int x, int y) {
	cellObject = Object::create(CellResource::EMPTY, bg, x, y);
	// 지뢰 또는 숫자에 따라 이미지 변경
	ChangeNumImage(fieldData);

	// 아이템 이미지 생성
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

	//각각의 칸의 위를 덮을 블럭 객체 생성
	block = Block::Create(bg, x, y);
}

void _cell::ChangeNumImage(FieldData fieldData) {
	switch (fieldData.num) {

		// 숫자일 경우
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

		// 빈칸일 경우
	default:
		break;
	}

	switch (fieldData.cellValue) {
		// 지뢰칸일 경우
	case CellValue::Mine:
		cellObject->setImage(CellResource::MINE);
		return;
		// 탈출구일 경우
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
