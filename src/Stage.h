#pragma once

/*
*
*
*/

#pragma once

#include <iostream>
#include <bangtal>
#include "CommonDeclarations.h"
#include "Board.h"

using namespace bangtal;

class Stage {
private:
	ScenePtr chapter;
	//Board board;

public:
	Stage(ScenePtr ch, Status stat);

	// 스테이지 진행 상황 변경시 적절한 이벤트를 발생하는 함수
	void EventHandler(); // 이벤트는 어디에서 발생할지?( 누가 이벤트 변수를 변경하나?)

	// 스테이지 진행 상황을 변경하는 함수
	void setChapterStatus();

	// 스테이지 진행 상황을 확인하는 함수
	void getChapterStatus();

	// 게임 오버 시 해당 스테이지를 다시 시작하는 함수
	void RestartStage();

	// 스테이지 클리어 시 다음 스테이지로 넘어가는 함수
	void NextStage();
};
