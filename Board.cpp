#include "Board.h"

Board::Board(ScenePtr bg) {
	// 행, 열 테스트 값
	int row = 10, col = 10;

	// 지뢰 생성 테스트
	field.Resize(row, col);
	field.MountMine();
	field.setAdjacentNum();
	field.Print();

	// 칸 생성 테스트
	for (int i = 0; i < row; i++) {
		std::vector<CellPtr> cellRow;
		for (int j = 0; j < col; j++) {
			CellPtr cell = Cell::Create(bg, field[i][j], i, j);
			cellRow.push_back(cell);
		}
		cells.push_back(cellRow);
	}

}
