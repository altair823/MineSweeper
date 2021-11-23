#include "GameGuide.h"

GameGuide::GameGuide(ScenePtr previousBackground, SoundPtr currentMusic, bool& isGameMute)
	: previousBackground(previousBackground), currentMusic(currentMusic), isGameMute(isGameMute){
	guideBackground = Scene::create("가이드 배경", GuideResource::BACKGROUND);
	SetupPages();
	SetupButtons();
}

void GameGuide::EnterGuide() {
	guideBackground->enter();
}

void GameGuide::CloseGuide() {
	for (auto& page : guidePage) {
		page.reset();
	}
	guidePage.clear();
	nextButton.reset();
	previousButton.reset();
	closeButton.reset();
	guideBackground.reset();
	currentPageIndex = 0;
	previousBackground->enter();
	previousBackground = nullptr;
}

void GameGuide::SetupPages() {
	// 페이지들 초기화
	guidePage.resize(3);
	guidePage[0] = Object::create(GuideResource::GUIDE_PAGE_1, guideBackground, 249, 70);
	guidePage[0]->setScale(0.8f);
	guidePage[1] = Object::create(GuideResource::GUIDE_PAGE_2, guideBackground, 249, 70, false);
	guidePage[1]->setScale(0.8f);
	guidePage[2] = Object::create(GuideResource::GUIDE_PAGE_3, guideBackground, 249, 70, false);
	guidePage[2]->setScale(0.8f);

	currentPageIndex = 0;
}

void GameGuide::SetupButtons() {
	// 버튼 초기화
	nextButton = Object::create(GuideResource::NEXT_PAGE, guideBackground, 1000, 300);
	previousButton = Object::create(GuideResource::PREVIOUS_PAGE, guideBackground, 200, 300, false);
	closeButton = Object::create(GuideResource::CLOSE_GUIDE, guideBackground, 940, 550);

	nextButton->setOnMouseCallback([&](auto, auto, auto, auto)->bool {
		// 페이지 넘기기
		guidePage[currentPageIndex]->hide();
		guidePage[++currentPageIndex]->show();
		if (currentPageIndex == guidePage.size() - 1) {
			nextButton->hide();
		}
		if (currentPageIndex > 0) {
			previousButton->show();
		}
		return true;
		});

	previousButton->setOnMouseCallback([&](auto, auto, auto, auto)->bool {
		// 페이지 돌아오기
		guidePage[currentPageIndex]->hide();
		guidePage[--currentPageIndex]->show();
		if (currentPageIndex < guidePage.size() - 1) {
			nextButton->show();
		}
		if (currentPageIndex == 0) {
			previousButton->hide();
		}
		return true;
		});

	closeButton->setOnMouseCallback([&](auto, auto, auto, auto)->bool {
		CloseGuide();
		return true;
		});

	CreateMuteButton(guideBackground, currentMusic);
}

void GameGuide::CreateMuteButton(ScenePtr background, SoundPtr music) {
	// 음소거 여부 유지
	if (isGameMute) {
		muteButton = Object::create(BoardResource::UNMUTE_BUTTON, background, 20, 630);
	}
	else {
		muteButton = Object::create(BoardResource::MUTE_BUTTON, background, 20, 630);
	}
	muteButton->setOnMouseCallback([=](auto, auto, auto, auto)->bool {
		// 음소거 상태였다면
		if (isGameMute) {
			isGameMute = false;
			music->play(true);
			muteButton->setImage(BoardResource::MUTE_BUTTON);
		}
		// 소리가 나는 상태였다면
		else {
			isGameMute = true;
			music->stop();
			muteButton->setImage(BoardResource::UNMUTE_BUTTON);
		}
		return true;
		});

}
