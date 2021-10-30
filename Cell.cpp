#include "Cell.h"

std::shared_ptr<_cell> Cell::create(ScenePtr bg, bool isThisMine, int row, int col)
{
	std::string imageName;

	// x, y 좌표 계산. 
	// 스테이지 구현을 위해서는 보드의 크기에 따라 맨 뒤의 상수가 바뀌어야 한다. 
	int x = (row + 1) * CELL_SIZE + 100;
	int y = (col + 1) * CELL_SIZE + 100;

	// 지뢰 여부에 따른 이미지 선택
	if (isThisMine) {
		imageName = CellResource::MINE;
	}
	else {
		imageName = CellResource::NORMAL;
	}

	// 새로운 칸 객체 생성
	std::shared_ptr<_cell> newCell(new _cell(bg, imageName, x, y));
	return newCell;
}

_cell::_cell(ScenePtr bg, const std::string resource, int x, int y) {
	cellObject = Object::create(resource, bg, x, y);
}
