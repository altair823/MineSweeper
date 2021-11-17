/*
* ShootTheMonster.h
* 
* �� �������� ��Ÿ���� ���͸� �ùٸ��� �����ϴ� ���� ��Ȳ Ŭ����.
* ���ʹ� �� �������� �������� ��Ÿ���� 
* �÷��̾�� Ÿ�ֿ̹� �°� �ش� ���Ͱ� �����ϴ� ���⿡ �ִ�
* ���� �����ϸ� �̱��. 
* ���� ������ ��� ��ȸ(�Ѿ�)�� �����ȴ�. 
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
	// ������ ����
	constexpr auto MONSTER_COUNT = 3;

	// ������ ��ȸ
	constexpr auto OPPORTUNITY = 5;

	// ��ǻ�Ϳ� �÷��̾��� ������ ȭ�鿡 ǥ���� �ð�
	constexpr auto VISIBLE_TIME = 0.5;
}

class BlockBreakHandler;

class ShootTheMonster : public Combat {

private:

	// ������ �����ϱ� �� ��Ȳ.
	// ������ ������ ���ư��� ����. 
	ScenePtr previousScene;

	// ���
	ScenePtr background;

	// ���� ��ġ �迭
	std::vector<ObjectPtr> monsters;

	// ������ ����
	int monsterRemainCount = ShootTheMonsterConfig::MONSTER_COUNT;

	// ���͸� ȭ�鿡 ���� �ð����� �����Ű�� Ÿ�̸�
	TimerPtr monsterShowTimer;

	// ��ȸ ������Ʈ �迭
	std::vector<ObjectPtr> opportunity;

	// ���� ������ ��ġ�� ��ġ�� �ش��ϴ� �ε���
	Direction monsterPosition;
	int dirNum;

	// �÷��̾ �� �� �ִ� �����
	ObjectPtr leftShoot;
	ObjectPtr centerShoot;
	ObjectPtr rightShoot;

	// �÷��̾ �� ����
	Direction playerShootDir;

	// ��� ǥ�� �߿� �÷��̾��� �Է��� ���� lock
	bool inputLock;

	// ���� ������ ������ BlockBreakHandler�� ��� �Լ� ��ü
	std::function<void(BlockBreakHandler&)> gameOverFunc;
	BlockBreakHandler& blockBreakHandler;

public:
	ShootTheMonster(ScenePtr previousScene, BlockBreakHandler& blockBreakHandler, std::function<void(BlockBreakHandler&)> gameOverFunc);

	/*
	* ������ �����ϴ� �Լ�
	*/
	void EnterBattle();

	/*
	* ���Ͱ� �������� ��Ÿ������ �ϴ� �Լ�
	*/
	void ShowMonsterRandomly();

	/*
	* �� ������ ������ ���ϰ� �׿� ���� ó���ϴ� �Լ�
	*/
	void CompareDirection(Direction playerDir, Direction monsterDir);

	/*
	* �־��� ���⿡ ���Ͱ� ���δٸ� �� ���͸� ���� �̹����� �ٲپ� �����ִ� �Լ�
	*/
	void ChangeMonsterToExplode(Direction direction);
};
