/*
* RockPaperScissor.h
* 
* 몬스터와 가위바위보를 하는 전투 상황 클래스.
*/

#pragma once

#include "../Combat.h"
#include "../resource.h"
#include <string>
#include <bangtal>
#include <vector>
#include <random>
using namespace bangtal;

namespace RockPaperScissorConfig {
	// 가위바위보 전투의 기회
	constexpr auto OPPORTUNITY = 5;

	// 컴퓨터와 플레이어의 선택을 화면에 표시할 시간
	constexpr auto VISIBLE_TIME = 1;
}

/*
* 가위바위보 게임의 선택 종류. 
*/
enum HandType {
	Rock,
	Paper,
	Scissors,
	NoChoice,
};

class RockPaperScissor : public Combat {
private:

	// 전투로 진입하기 전 상황.
	// 전투가 끝나면 돌아가기 위함. 
	ScenePtr previousScene;

	// 배경
	ScenePtr background;

	// 몬스터 배열
	std::vector<ObjectPtr> monsters;

	// 기회 오브젝트 배열
	std::vector<ObjectPtr> opportunity;

	// 화면에 출력할 플레이어의 선택지
	ObjectPtr rock;
	ObjectPtr paper;
	ObjectPtr scissor;

	// 플레이어의 선택
	HandType playerChoice = HandType::NoChoice;;

	// 컴퓨터의 선택
	HandType computerChoice = HandType::NoChoice;;

public:
	RockPaperScissor(ScenePtr previousScene);

	/*
	* 전투에 진입하는 함수
	*/
	void EnterBattle();

	/*
	* 컴퓨터가 가위, 바위, 보 중에서 하나를 선택하게 하는 함수
	*/
	HandType MakeComputerChoice();

	/*
	* 플레이어와 컴퓨터의 선택을 비교하는 함수. 
	* 그 결과에 따라 몬스터 또는 기회 오브젝트를 제거한다. 
	* 몬스터가 남아있지 않다면 다시 보드로 돌아가고, 
	* 기회가 남아있지 않다면 게임 오버.
	*/
	void CompareChoices();

	/*
	* 플레이어와 컴퓨터의 선택을 화면에 출력하는 함수
	*/
	void ShowChoices(HandType playerChoice, HandType computerChoice);
};