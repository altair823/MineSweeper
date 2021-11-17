/*
* ShootTheMonster.h
* 
* 세 군데에서 나타나는 몬스터를 올바르게 선택하는 전투 상황 클래스.
* 몬스터는 세 군데에서 무작위로 나타나며 
* 플레이어는 타이밍에 맞게 해당 몬스터가 존재하는 방향에 있는
* 총을 선택하면 이긴다. 
* 만약 빗나갈 경우 기회(총알)가 차감된다. 
*/

#pragma once

#include "../Combat.h"
#include "../resource.h"
#include <string>
#include <random>
#include <bangtal>
using namespace bangtal;

enum Direction {
	Left,
	Center,
	Right
};

namespace ShootTheMonsterConfig {
	// 몬스터의 숫자
	constexpr auto MONSTER_COUNT = 3;

	// 전투의 기회
	constexpr auto OPPORTUNITY = 5;

	// 컴퓨터와 플레이어의 선택을 화면에 표시할 시간
	constexpr auto VISIBLE_TIME = 0.5;
}

class BlockBreakHandler;

class ShootTheMonster : public Combat {

private:

	// 전투로 진입하기 전 상황.
	// 전투가 끝나면 돌아가기 위함. 
	ScenePtr previousScene;

	// 배경
	ScenePtr background;

	// 몬스터 위치 배열
	std::vector<ObjectPtr> monsters;

	// 몬스터의 숫자
	int monsterRemainCount = ShootTheMonsterConfig::MONSTER_COUNT;

	// 몬스터를 화면에 일정 시간동안 노출시키는 타이머
	TimerPtr monsterShowTimer;

	// 기회 오브젝트 배열
	std::vector<ObjectPtr> opportunity;

	// 현재 몬스터의 위치와 위치에 해당하는 인덱스
	Direction monsterPosition;
	int dirNum;

	// 플레이어가 쏠 수 있는 방향들
	ObjectPtr leftShoot;
	ObjectPtr centerShoot;
	ObjectPtr rightShoot;

	// 플레이어가 쏜 방향
	Direction playerShootDir;

	// 결과 표시 중에 플레이어의 입력을 막을 lock
	bool inputLock;

	// 게임 오버시 실행할 BlockBreakHandler의 멤버 함수 객체
	std::function<void(BlockBreakHandler&)> gameOverFunc;
	BlockBreakHandler& blockBreakHandler;

public:
	ShootTheMonster(ScenePtr previousScene, BlockBreakHandler& blockBreakHandler, std::function<void(BlockBreakHandler&)> gameOverFunc);

	/*
	* 전투에 진입하는 함수
	*/
	void EnterBattle();

	/*
	* 몬스터가 무작위로 나타나도록 하는 함수
	*/
	void ShowMonsterRandomly();

	/*
	* 두 방향이 같은지 비교하고 그에 따라 처리하는 함수
	*/
	void CompareDirection(Direction playerDir, Direction monsterDir);

	/*
	* 주어진 방향에 몬스터가 보인다면 그 몬스터를 폭발 이미지로 바꾸어 보여주는 함수
	*/
	void ChangeMonsterToExplode(Direction direction);
};
