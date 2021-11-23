/*
* DiceRolling.h
* 
* 몬스터와 주사위 게임을 하는 전투 상황 클래스.
* 주어진 기회 동안 주사위를 굴려 몬스터보다 높은 숫자를 갖게되면 이긴다. 
*/

#pragma once

#include "../Combat.h"
#include "../resource.h"
#include <random>
#include <bangtal>
using namespace bangtal;

namespace DiceRollingConfig {

	//전투의 기회
	constexpr auto OPPORTUNITY = 5;

	// 컴퓨터와 플레이어의 선택을 화면에 표시할 시간
	constexpr auto VISIBLE_TIME = 1;
}

class BlockBreakHandler;

class DiceRolling : public Combat {
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

	// 결과 표시 중에 플레이어의 입력을 막을 lock
	bool inputLock;
	
	// 플레이어와 컴퓨터의 주사위
	ObjectPtr computerDice;
	ObjectPtr playerDice;

	// 플레이어와 컴퓨터의 주사위 값
	int computerDiceValue;
	int playerDiceValue;

	// 화면에 플레이어와 컴퓨터의 주사위를 에니메이션으로 출력하는 타이머
	TimerPtr computerDiceAnimation;
	TimerPtr playerDiceAnimation;
	TimerPtr resultDelayTimer;

	// 클릭하면 주사위를 굴리는 버튼
	ObjectPtr stopButton;

	// 게임 오버시 실행할 BlockBreakHandler의 멤버 함수 객체
	std::function<void(BlockBreakHandler&)> gameOverFunc;
	BlockBreakHandler& blockBreakHandler;

public:
	DiceRolling(ScenePtr previousScene, BlockBreakHandler& blockBreakHandler, std::function<void(BlockBreakHandler&)> gameOverFunc);
	~DiceRolling();

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
	void CompareDice();

	/*
	* 타이머를 중단하는 함수
	*/
	void StopTimerAnimation();
};