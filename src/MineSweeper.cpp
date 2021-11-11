/*
* MineSweeper.cpp
* 
* main 함수가 있는 파일. 
* 
* 게임에 필요한 모든 요소들을 종합하여 적절히 배치하고 
* 게임을 작동시키는 역할을 한다. 
* 
* 이 파일에서 정의된 그 어떤 요소도 다른 파일에서 참조해서는 안된다. 
*/

#include <iostream>
#include <bangtal>
#include "Stage.h"
#include "resource.h"

int main()
{
	setGameOption(GameOption::GAME_OPTION_INVENTORY_BUTTON, false);
	setGameOption(GameOption::GAME_OPTION_MESSAGE_BOX_BUTTON, false);
	setGameOption(GameOption::GAME_OPTION_ROOM_TITLE, false);

	// 게임 타이틀 및 스테이지 별 스크립트를 보이기 위한 방탈 장면
	ScenePtr frontground = Scene::create("시작 화면", CombatResource::BACKGROUND1);
	// 게임이 실행되는 방탈 장면
	ScenePtr background = Scene::create("배경", BoardResource::BACKGROUND);
	Stage stage(background, frontground);

	startGame(frontground);
}