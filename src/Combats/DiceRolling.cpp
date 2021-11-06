#include "DiceRolling.h"

std::string RDBattleBackground[] = {
	CombatResource::BACKGROUND1,
	CombatResource::BACKGROUND2,
	CombatResource::BACKGROUND3
};

DiceRolling::DiceRolling(ScenePtr previousScene) {
	this->previousScene = previousScene;

	// ���� ���� ���� �ʱ�ȭ
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<int> dis(0, 2);

	background = Scene::create("���� ���", RDBattleBackground[dis(gen) % 3]);

	// ���� ǥ��
	monsters.resize(3);
	for (int i = 0; i < 3; i++) {
		monsters[i] = Object::create(CombatResource::MONSTER2, background, 200 * i + 30, 250);
		monsters[i]->setScale(0.4f);
	}

	// ��ȸ ǥ��
	opportunity.resize(DiceRollingConfig::OPPORTUNITY);
	for (int i = 0; i < DiceRollingConfig::OPPORTUNITY; i++) {
		opportunity[i] = Object::create(CombatResource::RockPaperScissor::Opportunity, background, 650, 0 + (80 * i));
	}
}

void DiceRolling::EnterBattle() {
	background->enter();
	showMessage("���Ͱ� �����߽��ϴ�!\n�ֻ��� ������ �� �� �̰ܾ� Ż���� �� �ֽ��ϴ�.\n��ȸ�� " + std::to_string(DiceRollingConfig::OPPORTUNITY) + "�� ���Դϴ�!");

	// �ֻ����� ������ ��ư ����
	rollingButton = Object::create(CombatResource::DiceRolling::Button, background, 260, -120);

	computerDice = Object::create(CombatResource::DiceRolling::One, background, 270, 150);
	playerDice = Object::create(CombatResource::DiceRolling::One, background, 270, 30);

	computerDiceAnimation = Timer::create(0.2f);
	computerDiceAnimation->setOnTimerCallback([&](auto)->bool {
		ChangeDiceNumRandomly(&computerDiceValue, computerDice);
		computerDiceAnimation->set(0.2f);
		computerDiceAnimation->start();
		return true;
		});

	playerDiceAnimation = Timer::create(0.2f);
	playerDiceAnimation->setOnTimerCallback([&](auto)->bool {
		ChangeDiceNumRandomly(&playerDiceValue, playerDice);
		playerDiceAnimation->set(0.2f);
		playerDiceAnimation->start();
		return true;
		});
	
	resultDelayTimer = Timer::create(DiceRollingConfig::VISIBLE_TIME);
	resultDelayTimer->setOnTimerCallback([&](auto)->bool {
		computerDiceAnimation->start();
		playerDiceAnimation->start();
		return true;
		});

	rollingButton->setOnMouseCallback([&](auto, auto, auto, auto)->bool {
		computerDiceAnimation->stop();
		playerDiceAnimation->stop();

		CompareDice();

		resultDelayTimer->set(DiceRollingConfig::VISIBLE_TIME);
		resultDelayTimer->start();
		return true;
		});

	computerDiceAnimation->start();
	playerDiceAnimation->start();
}

void DiceRolling::ChangeDiceNumRandomly(int* value, ObjectPtr object) {

	// ���� ���� ���� �ʱ�ȭ
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<int> dis(1, 6);

	*value = dis(gen);

	switch (*value) {
	case 1:
		object->setImage(CombatResource::DiceRolling::One);
		break;
	case 2:
		object->setImage(CombatResource::DiceRolling::Two);
		break;
	case 3:
		object->setImage(CombatResource::DiceRolling::Three);
		break;
	case 4:
		object->setImage(CombatResource::DiceRolling::Four);
		break;
	case 5:
		object->setImage(CombatResource::DiceRolling::Five);
		break;
	case 6:
		object->setImage(CombatResource::DiceRolling::Six);
		break;
	default:
		break;
	}

}

void DiceRolling::CompareDice() {
	if (playerDiceValue > computerDiceValue) {
		monsters.back()->hide();
		monsters.pop_back();
		if (monsters.size() == 0) {
			showMessage("���͵��� �����ƽ��ϴ�!");
			this->previousScene->enter();
		}
		else {
			showMessage("�÷��̾ �̰���ϴ�!");
		}
	}
	else if (playerDiceValue == computerDiceValue) {
		showMessage("�����ϴ�.");
	}
	else {
		opportunity.back()->hide();
		opportunity.pop_back();
		// ���� ��ȸ�� ���ٸ� ���� ����
		if (opportunity.size() == 0) {
			showMessage("���� ����!");
			/*
			*
			* ���ӿ����� Ÿ��Ʋ�� ���ư� ��!
			*
			*/
		}
		else {
			showMessage("���Ͱ� �̰���ϴ�...");
		}
	}
}
