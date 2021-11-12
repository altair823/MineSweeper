#pragma once

/*
*
*
*/

#pragma once

#include <iostream>
#include <bangtal>
#include "Board.h"

using namespace bangtal;

// 스테이지 갯수
constexpr auto STAGE_COUNT = 3;

class Stage {
private:
	// 지뢰찾기 게임이 진행되는 방탈 장면
	ScenePtr background;

	// 게임 타이틀 및 스테이지 별 스크립트를 보이기 위한 방탈 장면
	ScenePtr frontground;

	// 게임 타이틀 및 스테이지 별 스크립트를 나타내는 방탈 오브젝트
	ObjectPtr script;
	
	// 지뢰찾기 보드
	Board* board;

	// 현재 스테이지 레벨
	int currentStageLevel = 0;

	// 보드 진행 상황을 체크할 타이머
	TimerPtr boardStatusChecker;

public:
	Stage(ScenePtr background, ScenePtr frontground);

	// 보드 진행 상황 변경시 적절한 이벤트를 발생하는 함수
	void EventHandler();

	// 보드 클리어 시 다음 스테이지로 넘어가는 함수
	void NextStage();
};
