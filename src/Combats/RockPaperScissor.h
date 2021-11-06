/*
* RockPaperScissor.h
* 
* ���Ϳ� ������������ �ϴ� ���� ��Ȳ Ŭ����.
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
	// ���������� ������ ��ȸ
	constexpr auto OPPORTUNITY = 5;

	// ��ǻ�Ϳ� �÷��̾��� ������ ȭ�鿡 ǥ���� �ð�
	constexpr auto VISIBLE_TIME = 1;
}

/*
* ���������� ������ ���� ����. 
*/
enum HandType {
	Rock,
	Paper,
	Scissors,
	NoChoice,
};

class RockPaperScissor : public Combat {
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

	// ȭ�鿡 ����� �÷��̾��� ������
	ObjectPtr rock;
	ObjectPtr paper;
	ObjectPtr scissor;

	// �÷��̾��� ����
	HandType playerChoice = HandType::NoChoice;;

	// ��ǻ���� ����
	HandType computerChoice = HandType::NoChoice;;

public:
	RockPaperScissor(ScenePtr previousScene);

	/*
	* ������ �����ϴ� �Լ�
	*/
	void EnterBattle();

	/*
	* ��ǻ�Ͱ� ����, ����, �� �߿��� �ϳ��� �����ϰ� �ϴ� �Լ�
	*/
	HandType MakeComputerChoice();

	/*
	* �÷��̾�� ��ǻ���� ������ ���ϴ� �Լ�. 
	* �� ����� ���� ���� �Ǵ� ��ȸ ������Ʈ�� �����Ѵ�. 
	* ���Ͱ� �������� �ʴٸ� �ٽ� ����� ���ư���, 
	* ��ȸ�� �������� �ʴٸ� ���� ����.
	*/
	void CompareChoices();

	/*
	* �÷��̾�� ��ǻ���� ������ ȭ�鿡 ����ϴ� �Լ�
	*/
	void ShowChoices(HandType playerChoice, HandType computerChoice);
};