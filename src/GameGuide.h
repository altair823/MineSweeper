/*
* GameGuide.h
* 
* 게임에 대한 간략한 소개와 
* 게임을 하는 방법을 설명하는 가이드 화면을 관리하는 클래스
*/

#pragma once

#include <bangtal>
#include <vector>
#include "resource.h"

using namespace bangtal;

class GameGuide {
private:

	// 가이드의 배경
	ScenePtr guideBackground;

	// 다시 돌아갈 배경
	ScenePtr previousBackground;

	// 이전 배경에서부터 재생한 배경음악
	SoundPtr currentMusic;
	
	// 음소거 버튼과 음소거 여부를 참조하는 포인터
	ObjectPtr muteButton;
	bool& isGameMute;

	// 가이드 페이지
	std::vector<ObjectPtr> guidePage;

	// 현재 보이는 페이지의 인덱스
	int currentPageIndex;

	// 페이지를 넘기고 닫을 버튼들
	ObjectPtr nextButton;
	ObjectPtr previousButton;
	ObjectPtr closeButton;

public:
	GameGuide(ScenePtr previousBackground, SoundPtr currentMusic, bool& isGameMute);

	/*
	* 가이드를 띄우는 함수
	*/
	void EnterGuide();

	/*
	* 가이드를 닫는 함수
	*/
	void CloseGuide();

	/*
	* 가이드 페이지들을 초기화하고 생성하는 함수
	*/
	void SetupPages();

	/*
	* 가이드 버튼들을 초기화하고 생성하는 함수
	*/
	void SetupButtons();

	/*
	* 음소거 버튼을 생성하는 함수
	*/
	void CreateMuteButton(ScenePtr background, SoundPtr music);
};

