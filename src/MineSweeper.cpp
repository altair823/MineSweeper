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
	auto titleMusic = Sound::create("music/Stage3Board.mp3");
	titleMusic->play();
	Stage stage;
	stage.StartGame();
}