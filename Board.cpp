#include "Board.h"

Board::Board(ScenePtr bg) {
	// ��, �� �׽�Ʈ ��
	int row = 10, col = 10;

	// ���� ���� �׽�Ʈ
	field.Resize(row, col);
	field.MountMine();
	field.setAdjacentNum();
	field.Print();

	// ĭ ���� �׽�Ʈ
	for (int i = 0; i < row; i++) {
		std::vector<CellPtr> cellRow;
		for (int j = 0; j < col; j++) {
			CellPtr cell = Cell::Create(bg, field[i][j], i, j);
			cellRow.push_back(cell);
		}
		cells.push_back(cellRow);
	}

}
