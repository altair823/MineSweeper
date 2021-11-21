/*
* Stage
*
* 게임을 시작하고 스테이지 진행을 담당하는 클래스
* 
* 타이틀, 스크립트, 백그라운드, 엔딩 장면을 가지며
* 보드의 진행 상황을 참조해 각각의 장면을 적절하게 변경하고
* 조건에 맞는 장면으로 입장한다.
*/

#pragma once

#include <iostream>
#include <string>
#include <bangtal>
#include "Board.h"

#define DEBUG

using namespace bangtal;

// 스테이지 갯수
constexpr auto NUM_OF_STAGE_TO_BE_CLEARED = 3;

// 보드 초기 크기
constexpr auto STAGE1_ROW = 10, STAGE1_COL = 10;

// 초기 목숨 개수
constexpr auto INIT_LIFE_COUNT = 3;

// 해피 엔딩에 진입하기 위한 최대 전투 횟수
constexpr auto COMBAT_COUNT_FOR_HAPPY_ENDING = 8;


class Stage {
private:

	// 각 화면을 위한 배경
	ScenePtr titleBackground;
	ScenePtr scriptBackground;
	ScenePtr boardBackground;
	ScenePtr endingBackground;

	// 스테이지 별 스크립트
	ObjectPtr script;

	// 스크립트 화면을 넘기는 버튼
	ObjectPtr nextButton;

	// 음소거 버튼과 음소거 여부 변수
	ObjectPtr muteButton;
	bool isMusicMute;

	// 각 장면의 배경음악
	SoundPtr titleMusic;
	SoundPtr scriptMusic;
	SoundPtr boardMusic;
	SoundPtr endingMusic;

	// 탈출하기 버튼
	ObjectPtr escapeButton;

	// 지뢰찾기 보드
	Board* board;

	// 클리어한 스테이지의 개수
	int stageNum = 0;

	// 보드 진행 상황을 체크할 타이머
	TimerPtr boardStatusChecker;

	// 엔딩 스트립트
	ObjectPtr endingScript;

public:
	Stage();

	// tile 장면과 title 장면이 가지는 방탈 오브젝트들을 초기화하는 함수
	void StartGame();

	// scriptBackground 장면과 scriptBackground 장면이 가지는 방탈 오브젝트들을 초기화하는 함수
	void ShowScript(int stageNum);

	// background 장면과 background 장면이 가지는 방탈 오브젝트들을 초기화하는 함수
	void CreateBoard();

	// ending 장면과 ending 장면이 가지는 방탈 오브젝트들을 초기화하는 함수
	void EnterEnding();

	// 보드 진행 상황 변경시 적절한 이벤트를 발생하는 함수
	void StartStatusHandler();

	// 보드 클리어 시 다음 스테이지로 넘어가는 함수
	void EnterNextStage();

	/*
	* 음소거 버튼을 생성하는 함수
	*/
	void CreateMuteButton(ScenePtr background, SoundPtr music);

	/*
	* 게임을 재시작하는 함수
	*/
	void RestartGame();
};
