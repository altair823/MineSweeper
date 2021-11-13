#include "Cell.h"

std::shared_ptr<_cell> Cell::Create(ScenePtr bg, FieldData fieldData, int x, int y) {
	// »õ·Î¿î Ä­ °´Ã¼ »ý¼º
	std::shared_ptr<_cell> newCell(new _cell(bg, fieldData, x, y));
	return newCell;
}

_cell::_cell(ScenePtr bg, FieldData fieldData, int x, int y) {
	cellObject = Object::create(CellResource::EMPTY, bg, x, y);
	// Áö·Ú ¶Ç´Â ¼ýÀÚ¿¡ µû¶ó ÀÌ¹ÌÁö º¯°æ
	ChangeNumImage(fieldData);

	//°¢°¢ÀÇ Ä­ÀÇ À§¸¦ µ¤À» ºí·° °´Ã¼ »ý¼º
	block = Block::Create(bg, x, y);
}

void _cell::ChangeNumImage(FieldData fieldData) {
	switch (fieldData.num) {

		// ¼ýÀÚÀÏ °æ¿ì
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

		// ºóÄ­ÀÏ °æ¿ì
	default:
		break;
	}

	switch (fieldData.cellValue) {
		// Áö·ÚÄ­ÀÏ °æ¿ì
	case CellValue::Mine:
		cellObject->setImage(CellResource::MINE);
		return;
		// Å»Ãâ±¸ÀÏ °æ¿ì
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