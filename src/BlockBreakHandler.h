/*
* BlockBreakHandler.h
* 
* 블럭을 클릭해서 깨졌을 때, 깨졌음을 체크하고 이벤트를 처리하는 클래스. 
* 지뢰 칸이라면 전투 상황으로 이동하고,
* 빈칸이라면 확장을 하며, 숫자 칸이라면 아무것도 하지 않는다. 
*/

#pragma once

#include <vector>
#include "MineField.h"
#include "Cell.h"
#include <bangtal>

#include "Combat.h"
#include "Combats/DiceMatching.h"
#include "Combats/DiceRolling.h"
#include "Combats/OddOrEven.h"
#include "Combats/RockPaperScissor.h"
#include "Combats/RockPaperScissor.h"
#include "Combats/ShootTheMonster.h"

using namespace bangtal;

// 이벤트 핸들러의 갱신 간격
constexpr auto REFRESH_TIME = 0.1f;

/*
* 스테이지 진행 상황을 정의하는 enum.
*/
enum class BoardStatus {
	// 게임이 진행중임
	Playing,
	// 게임이 플레이어의 패배로 끝남
	GameOver,
	// 탈출구를 찾음
	Escape,
	// 지뢰를 제외한 모든 칸을 열음
	Clear
};

class BlockBreakHandler {
private:
	// 현재 보드의 크기
	int& row, col;

	// 현재 보드의 상태
	BoardStatus status = BoardStatus::Playing;

	// 현재 보드의 배경
	ScenePtr boardBackground;

	// 셀들이 열렸는지를 체크하는 2차원 벡터
	std::vector<std::vector<bool>> isCellOpen;

	// 모든 칸들의 데이터를 참조
	MineField& field;

	// 모든 셀의 2차원 벡터를 참조
	std::vector<std::vector<CellPtr>>& cells;

	// 새로 열린 cell이 있는지 체크할 타이머
	TimerPtr refreshTimer;

	// 지뢰를 밟을 때 진입할 전투 상황 포인터
	Combat* newCombat = nullptr;

public:
	BlockBreakHandler(int& newRow, int& newCol, MineField& newField, std::vector<std::vector<CellPtr>>& newCells, ScenePtr boardBackground);
	~BlockBreakHandler();


	/*
	* 새로 열린 cell이 있는지 확인하는 함수
	*/
	void CheckNewCellOpened();

	/*
	* 무작위적 전투 상황으로 진입하는 함수
	*/
	void EnterRandomCombat(int curRow, int curCol);

	/*
	* 빈 칸의 경계에 있는 cell들을 열어 확장하는 함수
	*/
	void ExpandBorder(int curRow, int curCol);

	/*
	* 조건을 만족하면 보드의 상태를 갱신하는 함수
	*/
	void RefreshBoardStatus(int curRow, int curCol);

	/*
	* cell 확인을 중단하는 함수
	* Timer를 초기화하기 위해 필요함.
	*/
	void StopCheckNewCellOpened();

	/*
	* 보드의 상태를 반환하는 함수
	*/
	BoardStatus getStatus();

	/*
	* 보드의 상태를 갱신하는 함수
	*/
	void setStatus(BoardStatus stat);
};

