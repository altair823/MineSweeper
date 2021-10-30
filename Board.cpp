#include "Board.h"

Board::Board(ScenePtr bg) {
	// ĭ ���� �׽�Ʈ
	for (int i = 0; i < 5; i++) {
		std::vector<CellPtr> cellRow;
		for (int j = 0; j < 5; j++) {
			CellPtr cell = Cell::create(bg, false, i, j);
			cellRow.push_back(cell);
		}
		cells.push_back(cellRow);
	}
}
