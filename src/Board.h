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
#include "MineField.h"
#include <vector>
#include <bangtal>
#include "Combat.h"
#include "Combats/RockPaperScissor.h"
#include "Combats/DiceRolling.h"
#include "Combats/ShootTheMonster.h"
#include "Combats/OddOrEven.h"
#include "Combats/DiceMatching.h"

using namespace bangtal;

static int boardCount = 0;

/*
* 지뢰찾기를 진행할 판 클래스
*/
class Board {
private:
	// 배경
	ScenePtr background;

	// 보드의 가로 세로 크기
	int row, col;

	// 칸 객체를 저장하는 2차원 vector
	std::vector<std::vector<CellPtr>> cells;

	// 지뢰찾기 판 전체의 데이터를 관리하는 객체
	MineField field;

	// 현재 사용중인 도구
	Hand hand = Hand::Pickax;

	// 현재 사용중인 도구의 상태를 표시하기 위한 객체
	ObjectPtr handObject;

	// 현재 보드의 상황을 나타내는 변수
	Status status;

	// **디버그용** 보드를 초기화 하기 위한 버튼 객체
	ObjectPtr resetButton;

public:

	Board(ScenePtr bg);

	// 핸드컨트롤 객체의 상태를 바꾸는 함수
	void HandChange();

	// 보드를 초기화하는 함수
	void RefreshBoard();
};