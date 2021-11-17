#pragma once

#include "../Combat.h"
#include "../resource.h"
#include <random>
#include <bangtal>
using namespace bangtal;

class BlockBreakHandler;

namespace DiceMatchingConfig {

	// ������ ����
	constexpr auto MONSTER_COUNT = 3;

	//������ ��ȸ
	constexpr auto OPPORTUNITY = 5;

	// ��ǻ�Ϳ� �÷��̾��� ������ ȭ�鿡 ǥ���� �ð�
	constexpr auto VISIBLE_TIME = 1;

	// �ֻ����� ���� ���� �ӵ�
	constexpr auto DICE_ROLL_SPEED = 0.2;
}

class DiceMatching : public Combat {
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

	// ��ǻ���� �ֻ���
	ObjectPtr dice;

	// ���� �ֻ��� ��
	int diceValue;

	// ȭ�鿡 ��ǻ���� �ֻ����� ���ϸ��̼����� ����ϴ� Ÿ�̸�
	TimerPtr diceAnimation;
	TimerPtr resultDelayTimer;

	// ���� ��ư
	ObjectPtr oneButton;
	ObjectPtr twoButton;
	ObjectPtr threeButton;
	ObjectPtr fourButton;
	ObjectPtr fiveButton;
	ObjectPtr sixButton;

	// �÷��̾��� ����
	int playerChoice;

	// ��� ǥ�� �߿� �÷��̾��� �Է��� ���� lock
	bool inputLock;

	// ���� ������ ������ BlockBreakHandler�� ��� �Լ� ��ü
	std::function<void(BlockBreakHandler&)> gameOverFunc;
	BlockBreakHandler& blockBreakHandler;

public:
	DiceMatching(ScenePtr previousScene, BlockBreakHandler& blockBreakHandler, std::function<void(BlockBreakHandler&)> gameOverFunc);

	/*
	* ������ �����ϴ� �Լ�
	*/
	void EnterBattle();

	/*
	* �ֻ����� ���� �̹����� �������� �ٲٴ� �Լ�
	*/
	void ChangeDiceNumRandomly();

	/*
	* ������� �Է��� ��� ���� �Լ��� �Ѱ��ִ� �Լ�
	*/
	bool InputPlayerChoice(int num);

	/*
	* ����� ���Ͽ� ���и� �����ϴ� �Լ�
	*/
	void CompareChoice();

};