/*
* Board
* 
* 지뢰찾기 게임을 진행할 판을 구현하는 클래스.
* 각 스테이지마다 정해진 개수의 칸을 가지며
* 지뢰의 위치는 매 판마다 무직위적이어야 한다. 
* 
*/

#pragma once

#include "Cell.h"
#include <vector>
#include <bangtal>
using namespace bangtal;

static int boardCount = 0;

/*
* 지뢰찾기를 진행할 판 클래스
*/
class Board {
private:
	// 배경
	ScenePtr background;

	// 칸 객체를 저장하는 2차원 vector
	std::vector<std::vector<CellPtr>> cells;
public:

	Board(ScenePtr bg);
};

