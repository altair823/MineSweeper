#include "Board.h"

Board::Board(ScenePtr bg) {
	// 칸 생성 테스트
	for (int i = 0; i < 5; i++) {
		std::vector<CellPtr> cellRow;
		for (int j = 0; j < 5; j++) {
			CellPtr cell = Cell::create(bg, false, i, j);
			cellRow.push_back(cell);
		}
		cells.push_back(cellRow);
	}
}
