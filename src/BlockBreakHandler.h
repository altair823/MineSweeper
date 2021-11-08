/*
* BlockBreakHandler.h
* 
* 블럭을 클릭해서 깨졌을 때, 그 이벤트를 처리하는 클래스. 
* 지뢰 칸이라면 전투 상황으로 이동하고,
* 빈칸이라면 확장을 하며, 숫자 칸이라면 아무것도 하지 않는다. 
*/

#pragma once

#include <vector>
#include "MineField.h"
#include "Cell.h"
#include <bangtal>
using namespace bangtal;

class BlockBreakHandler {
private:

	// 보드의 크기
	int row, col;

	// 셀들이 열렸는지를 체크하는 2차원 벡터
	std::vector<std::vector<bool>> isCellOpen;

	// 모든 칸들의 데이터
	MineField& field;

	// 모든 셀
	std::vector<std::vector<CellPtr>>& cells;

	// 새로 열린 cell이 있는지 체크할 타이머
	TimerPtr refreshTimer;

public:
	BlockBreakHandler(int newRow, int newCol, MineField& newField, std::vector<std::vector<CellPtr>>& newCells);

	/*
	* 새로 열린 cell이 있는지 확인하는 함수
	*/
	void CheckNewCellOpened();

	void StopCheckNewCellOpened();
};

