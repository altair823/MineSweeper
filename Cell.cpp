#include "Cell.h"

std::shared_ptr<_cell> Cell::create(ScenePtr bg, bool isThisMine, int row, int col)
{
	std::string imageName;

	// x, y ��ǥ ���. 
	// �������� ������ ���ؼ��� ������ ũ�⿡ ���� �� ���� ����� �ٲ��� �Ѵ�. 
	int x = (row + 1) * CELL_SIZE + 100;
	int y = (col + 1) * CELL_SIZE + 100;

	// ���� ���ο� ���� �̹��� ����
	if (isThisMine) {
		imageName = CellResource::MINE;
	}
	else {
		imageName = CellResource::NORMAL;
	}

	// ���ο� ĭ ��ü ����
	std::shared_ptr<_cell> newCell(new _cell(bg, imageName, x, y));
	return newCell;
}

_cell::_cell(ScenePtr bg, const std::string resource, int x, int y) {
	cellObject = Object::create(resource, bg, x, y);
}
