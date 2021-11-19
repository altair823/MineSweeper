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
#include "BlockBreakHandler.h"
#include "Item.h"

using namespace bangtal;

static int boardCount = 0;

// ** 디버그를 위해 100으로 초기화 됨 **
constexpr auto LIFE_COUNT = 100;

// 셀 하나 한 변의 픽셀 길이
constexpr auto CELL_SIZE = 30;

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

	// 아이템 객체
	std::shared_ptr<Item> item;

	// 블럭 제거 이벤트 핸들러
	std::shared_ptr<BlockBreakHandler> OnBlockBreak;

	// 현재 보드의 상태
	BoardStatus status = BoardStatus::Playing;


public:
	Board(ScenePtr bg, int initLifeCount);

	/*
	* 보드를 주어진 크기로 초기화하고 생성하는 함수
	*/ 
	void RefreshBoard(int newRow, int newCol, int stageNum);

	/*
	* 현재 보드를 초기화하는 함수
	*/ 
	void Clear();

	/*
	* 보드를 주어진 크기로 새로 생성하는 함수
	*/ 
	void GenerateNewBoard(int newRow, int newCol, int stageNum);

	/*
	* 아이템 초기화 함수
	*/
	void InitItem(int initLifeCount);

	/*
	* 보드의 상태를 반환하는 함수
	*/ 
	BoardStatus getBoardStatus();

	/*
	* 보드의 가로 크기를 반환하는 함수
	*/ 
	int getRow();

	/*
	* 보드의 세로 크기를 반환하는 함수
	*/ 
	int getCol();

	/*
	* 보드의 상태를 설정하는 함수
	*/
	void setBoardStatus(BoardStatus status);
};