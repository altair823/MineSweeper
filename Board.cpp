#include "Board.h"

Board::Board(ScenePtr bg) {
	// ���� ���� �׽�Ʈ
	field.Resize(10, 20);
	field.MountMine();
	field.setAdjacentNum();
	field.Print();

	// ĭ ���� �׽�Ʈ
	for (int i = 0; i < 10; i++) {
		std::vector<CellPtr> cellRow;
		for (int j = 0; j < 20; j++) {
			CellPtr cell = Cell::Create(bg, field[i][j], i, j);
			cellRow.push_back(cell);
		}
		cells.push_back(cellRow);
	}

}
