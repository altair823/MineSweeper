#include "Cell.h"

std::shared_ptr<_cell> Cell::Create(ScenePtr bg, int cellValue, int row, int col)
{
	std::string imageName;

	// x, y 좌표 계산. 
	// 스테이지 구현을 위해서는 보드의 크기에 따라 맨 뒤의 상수가 바뀌어야 한다. 
	int x = (col + 1) * CELL_SIZE + 100;
	int y = -(row + 1) * CELL_SIZE + 420;


	// 새로운 칸 객체 생성
	std::shared_ptr<_cell> newCell(new _cell(bg, cellValue, x, y));
	return newCell;
}

_cell::_cell(ScenePtr bg, int cellValue, int x, int y) {
	cellObject = Object::create(CellResource::EMPTY, bg, x, y);
	// 지뢰 또는 숫자에 따라 이미지 변경
	ChangeNumImage(cellValue);
}

void _cell::ChangeNumImage(int num) {
	if (isThisMine == true) {
		return;
	}

	switch (num) {
	// 지뢰칸일 경우
	case CellValue::Mine:
		cellObject->setImage(CellResource::MINE);
		break;

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
