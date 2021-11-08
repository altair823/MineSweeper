#include "Cell.h"

std::shared_ptr<_cell> Cell::Create(ScenePtr bg, FieldData fieldData, int row, int col, Hand* handPtr)
{
	// x, y 좌표 계산. 
	// 스테이지 구현을 위해서는 보드의 크기에 따라 맨 뒤의 상수가 바뀌어야 한다. 
	int x = (col + 1) * CELL_SIZE + 100;
	int y = -(row + 1) * CELL_SIZE + 420;


	// 새로운 칸 객체 생성
	std::shared_ptr<_cell> newCell(new _cell(bg, fieldData, x, y, handPtr));
	return newCell;
}

_cell::_cell(ScenePtr bg, FieldData fieldData, int x, int y, Hand* handPtr) {
	cellObject = Object::create(CellResource::EMPTY, bg, x, y);
	// 지뢰 또는 숫자에 따라 이미지 변경
	ChangeNumImage(fieldData);

	//각각의 칸의 위를 덮을 블럭 객체 생성
	block = Block::Create(bg, x, y);

	//블럭객체에 대한 MouseCallback 함수 정의
	MakeBlockCallback(block);

	//핸드포인터
	this->handPtr = handPtr;
}

void _cell::ChangeNumImage(FieldData fieldData) {

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