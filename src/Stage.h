#pragma once

/*
*
*
*/

#pragma once

#include <iostream>
#include <string>
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

	// frontground의 스테이지 별 이미지를 저장하고 있는 벡터
	std::vector<std::string> frontgroundImage = {StageResource::FG_IMAGE_0, StageResource::FG_IMAGE_1, StageResource::FG_IMAGE_2, StageResource::FG_IMAGE_3};

	// 게임 타이틀 및 스테이지 별 스크립트를 나타내는 방탈 오브젝트
	ObjectPtr script;

	// script의 스테이지 별 이미지를 저장하고 있는 벡터
	std::vector<std::string> scriptImage = { StageResource::SCRIPT_IMAGE_0, StageResource::SCRIPT_IMAGE_1, StageResource::SCRIPT_IMAGE_2, StageResource::SCRIPT_IMAGE_3 };

	// 탈출하기 버튼을 나타내는 방탈 오브젝트
	ObjectPtr escapeButton;
	
	// 지뢰찾기 보드
	Board* board;

	// 현재 스테이지 레벨
	int currentStageLevel = 0;

	// 보드 진행 상황을 체크할 타이머
	TimerPtr boardStatusChecker;

public:
	Stage();

	// 시작 장면을 반환하는 함수
	ScenePtr getFrontground();

	// 보드 진행 상황 변경시 적절한 이벤트를 발생하는 함수
	void EventHandler();

	// 보드 클리어 시 다음 스테이지로 넘어가는 함수
	void NextStage();
};
