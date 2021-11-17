#pragma once

#include "../Combat.h"
#include "../resource.h"
#include <random>
#include <bangtal>
using namespace bangtal;

class BlockBreakHandler;

namespace DiceMatchingConfig {

	// 몬스터의 숫자
	constexpr auto MONSTER_COUNT = 3;

	//전투의 기회
	constexpr auto OPPORTUNITY = 5;

	// 컴퓨터와 플레이어의 선택을 화면에 표시할 시간
	constexpr auto VISIBLE_TIME = 1;

	// 주사위의 숫자 변경 속도
	constexpr auto DICE_ROLL_SPEED = 0.2;
}

class DiceMatching : public Combat {
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

	// 컴퓨터의 주사위
	ObjectPtr dice;

	// 현재 주사위 값
	int diceValue;

	// 화면에 컴퓨터의 주사위를 에니메이션으로 출력하는 타이머
	TimerPtr diceAnimation;
	TimerPtr resultDelayTimer;

	// 숫자 버튼
	ObjectPtr oneButton;
	ObjectPtr twoButton;
	ObjectPtr threeButton;
	ObjectPtr fourButton;
	ObjectPtr fiveButton;
	ObjectPtr sixButton;

	// 플레이어의 선택
	int playerChoice;

	// 결과 표시 중에 플레이어의 입력을 막을 lock
	bool inputLock;

	// 게임 오버시 실행할 BlockBreakHandler의 멤버 함수 객체
	std::function<void(BlockBreakHandler&)> gameOverFunc;
	BlockBreakHandler& blockBreakHandler;

public:
	DiceMatching(ScenePtr previousScene, BlockBreakHandler& blockBreakHandler, std::function<void(BlockBreakHandler&)> gameOverFunc);

	/*
	* 전투에 진입하는 함수
	*/
	void EnterBattle();

	/*
	* 주사위의 값과 이미지를 무작위로 바꾸는 함수
	*/
	void ChangeDiceNumRandomly();

	/*
	* 사용자의 입력을 결과 결정 함수에 넘겨주는 함수
	*/
	bool InputPlayerChoice(int num);

	/*
	* 결과를 비교하여 승패를 결정하는 함수
	*/
	void CompareChoice();

};