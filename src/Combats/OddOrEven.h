/*
* OddOrEven.h
* 
* 몬스터와 홀짝 게임을 하는 전투 상황 클래스.
*/

#pragma once

#include "../Combat.h"
#include "../resource.h"
#include <string>
#include <random>
#include <bangtal>
using namespace bangtal;

class BlockBreakHandler;

enum class PlayerChoice {
	Odd,
	Even,
};

namespace OddOrEvenConfig {
	// 몬스터의 숫자
	constexpr auto MONSTER_COUNT = 3;

	// 전투의 기회
	constexpr auto OPPORTUNITY = 5;

	// 컴퓨터와 플레이어의 선택을 화면에 표시할 시간
	constexpr auto VISIBLE_TIME = 1;

	// 주사위의 숫자 변경 속도
	constexpr auto DICE_ROLL_SPEED = 0.2;
}

class OddOrEven : public Combat {
private:

	// 전투로 진입하기 전 상황.
	// 전투가 끝나면 돌아가기 위함. 
	ScenePtr previousScene;

	// 배경
	ScenePtr background;

	// 몬스터 위치 배열
	std::vector<ObjectPtr> monsters;

	// 기회 오브젝트 배열
	std::vector<ObjectPtr> opportunity;

	// 플레이어와 컴퓨터의 주사위
	ObjectPtr dice;

	// 현재 주사위 값
	int diceValue;

	// 화면에 컴퓨터의 주사위를 에니메이션으로 출력하는 타이머
	TimerPtr diceAnimation;
	TimerPtr resultDelayTimer;

	// 홀, 짝 선택 버튼
	ObjectPtr OddButton;
	ObjectPtr EvenButton;

	// 플레이어의 선택
	PlayerChoice playerChoice;

	// 결과 표시 중에 플레이어의 입력을 막을 lock
	bool inputLock;

	// 게임 오버시 실행할 BlockBreakHandler의 멤버 함수 객체
	std::function<void(BlockBreakHandler&)> gameOverFunc;
	BlockBreakHandler& blockBreakHandler;

	/*
	* 플레이어의 선택을 처리하는 함수
	*/
	bool InputChoice(PlayerChoice choice);

public:
	OddOrEven(ScenePtr previousScene, BlockBreakHandler& blockBreakHandler, std::function<void(BlockBreakHandler&)> gameOverFunc);
	~OddOrEven();

	/*
	* 전투에 진입하는 함수
	*/
	void EnterBattle();

	/*
	* 주사위의 값과 이미지를 무작위로 바꾸는 함수
	*/
	void ChangeDiceNumRandomly(int* value, ObjectPtr object);

	/*
	* 결과를 비교하여 승패를 결정하는 함수
	*/
	void CompareChoice();

	/*
	* 타이머를 중단하는 함수
	*/
	void StopTimerAnimation();
};