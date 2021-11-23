/*
* DiceRolling.h
* 
* ���Ϳ� �ֻ��� ������ �ϴ� ���� ��Ȳ Ŭ����.
* �־��� ��ȸ ���� �ֻ����� ���� ���ͺ��� ���� ���ڸ� ���ԵǸ� �̱��. 
*/

#pragma once

#include "../Combat.h"
#include "../resource.h"
#include <random>
#include <bangtal>
using namespace bangtal;

namespace DiceRollingConfig {

	//������ ��ȸ
	constexpr auto OPPORTUNITY = 5;

	// ��ǻ�Ϳ� �÷��̾��� ������ ȭ�鿡 ǥ���� �ð�
	constexpr auto VISIBLE_TIME = 1;
}

class BlockBreakHandler;

class DiceRolling : public Combat {
private:

	// ������ �����ϱ� �� ��Ȳ.
	// ������ ������ ���ư��� ����. 
	ScenePtr previousScene;

	// ���
	ScenePtr background;

	// ���� �迭
	std::vector<ObjectPtr> monsters;

	// ��ȸ ������Ʈ �迭
	std::vector<ObjectPtr> opportunity;

	// ��� ǥ�� �߿� �÷��̾��� �Է��� ���� lock
	bool inputLock;
	
	// �÷��̾�� ��ǻ���� �ֻ���
	ObjectPtr computerDice;
	ObjectPtr playerDice;

	// �÷��̾�� ��ǻ���� �ֻ��� ��
	int computerDiceValue;
	int playerDiceValue;

	// ȭ�鿡 �÷��̾�� ��ǻ���� �ֻ����� ���ϸ��̼����� ����ϴ� Ÿ�̸�
	TimerPtr computerDiceAnimation;
	TimerPtr playerDiceAnimation;
	TimerPtr resultDelayTimer;

	// Ŭ���ϸ� �ֻ����� ������ ��ư
	ObjectPtr stopButton;

	// ���� ������ ������ BlockBreakHandler�� ��� �Լ� ��ü
	std::function<void(BlockBreakHandler&)> gameOverFunc;
	BlockBreakHandler& blockBreakHandler;

public:
	DiceRolling(ScenePtr previousScene, BlockBreakHandler& blockBreakHandler, std::function<void(BlockBreakHandler&)> gameOverFunc);
	~DiceRolling();

	/*
	* ������ �����ϴ� �Լ�
	*/
	void EnterBattle();

	/*
	* �ֻ����� ���� �̹����� �������� �ٲٴ� �Լ�
	*/
	void ChangeDiceNumRandomly(int* value, ObjectPtr object);

	/*
	* ����� ���Ͽ� ���и� �����ϴ� �Լ�
	*/
	void CompareDice();

	/*
	* Ÿ�̸Ӹ� �ߴ��ϴ� �Լ�
	*/
	void StopTimerAnimation();
};