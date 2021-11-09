/*
* OddOrEven.h
* 
* ���Ϳ� Ȧ¦ ������ �ϴ� ���� ��Ȳ Ŭ����.
*/

#pragma once

#include "../Combat.h"
#include "../resource.h"
#include <string>
#include <random>
#include <bangtal>
using namespace bangtal;

enum PlayerChoice {
	Odd,
	Even,
};

namespace OddOrEvenConfig {
	// ������ ����
	constexpr auto MONSTER_COUNT = 3;

	// ������ ��ȸ
	constexpr auto OPPORTUNITY = 5;

	// ��ǻ�Ϳ� �÷��̾��� ������ ȭ�鿡 ǥ���� �ð�
	constexpr auto VISIBLE_TIME = 1;

	// �ֻ����� ���� ���� �ӵ�
	constexpr auto DICE_ROLL_SPEED = 0.2;
}

class OddOrEven : public Combat {
private:

	// ������ �����ϱ� �� ��Ȳ.
	// ������ ������ ���ư��� ����. 
	ScenePtr previousScene;

	// ���
	ScenePtr background;

	// ���� ��ġ �迭
	std::vector<ObjectPtr> monsters;

	// ��ȸ ������Ʈ �迭
	std::vector<ObjectPtr> opportunity;

	// �÷��̾�� ��ǻ���� �ֻ���
	ObjectPtr dice;

	// ���� �ֻ��� ��
	int diceValue;

	// ȭ�鿡 ��ǻ���� �ֻ����� ���ϸ��̼����� ����ϴ� Ÿ�̸�
	TimerPtr diceAnimation;
	TimerPtr resultDelayTimer;

	// Ȧ, ¦ ���� ��ư
	ObjectPtr OddButton;
	ObjectPtr EvenButton;

	// �÷��̾��� ����
	PlayerChoice playerChoice;

public:
	OddOrEven(ScenePtr previousScene);

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
	void CompareChoice();
};