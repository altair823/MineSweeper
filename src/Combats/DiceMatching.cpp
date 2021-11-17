#include "DiceMatching.h"

DiceMatching::DiceMatching(ScenePtr previousScene, BlockBreakHandler& blockBreakHandler, std::function<void(BlockBreakHandler&)> gameOverFunc)
	: inputLock(false), blockBreakHandler(blockBreakHandler), gameOverFunc(gameOverFunc) {
	this->previousScene = previousScene;
	// ���� ���� ���� �ʱ�ȭ
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<int> dis(0, 2);

	switch (dis(gen)) {
	case 0:
		background = Scene::create("���� ���", CombatResource::BACKGROUND1);
		break;
	case 1:
		background = Scene::create("���� ���", CombatResource::BACKGROUND2);
		break;
	case 2:
		background = Scene::create("���� ���", CombatResource::BACKGROUND3);
		break;
	default:
		break;
	}

	// ���� ǥ��
	monsters.resize(3);
	for (int i = 0; i < 3; i++) {
		monsters[i] = Object::create(CombatResource::MONSTER5, background, 200 * i + 30, 250);
		monsters[i]->setScale(0.4f);
	}

	// ��ȸ ǥ��
	opportunity.resize(DiceMatchingConfig::OPPORTUNITY);
	for (int i = 0; i < DiceMatchingConfig::OPPORTUNITY; i++) {
		opportunity[i] = Object::create(CombatResource::DiceMatching::Opportunity, background, 660, 0 + (70 * i));
	}
}

void DiceMatching::EnterBattle(){
	background->enter();
	showMessage("���Ͱ� �����߽��ϴ�!\n������ �ֻ��� ���� " + std::to_string(DiceMatchingConfig::MONSTER_COUNT) + "�� ����� Ż���� �� �ֽ��ϴ�.\n��ȸ�� "
		+ std::to_string(DiceMatchingConfig::OPPORTUNITY) + "�� ���Դϴ�!");

	dice = Object::create(CombatResource::DiceMatching::One, background, 270, 150);

	diceAnimation = Timer::create(DiceMatchingConfig::DICE_ROLL_SPEED);
	diceAnimation->setOnTimerCallback([&](auto)->bool {
		ChangeDiceNumRandomly();
		diceAnimation->set(DiceMatchingConfig::DICE_ROLL_SPEED);
		diceAnimation->start();
		return true;
		});

	resultDelayTimer = Timer::create(DiceMatchingConfig::VISIBLE_TIME);
	resultDelayTimer->setOnTimerCallback([&](auto)->bool {
		diceAnimation->start();
		// ����� ������ �Է� ����� Ǭ��. 
		inputLock = false;
		return true;
		});

	// �ֻ��� �� ���� ��ư ����
	oneButton = Object::create(CombatResource::DiceMatching::One, background, 0, -100);
	twoButton = Object::create(CombatResource::DiceMatching::Two, background, 110, -100);
	threeButton = Object::create(CombatResource::DiceMatching::Three, background, 220, -100);
	fourButton = Object::create(CombatResource::DiceMatching::Four, background, 330, -100);
	fiveButton = Object::create(CombatResource::DiceMatching::Five, background, 440, -100);
	sixButton = Object::create(CombatResource::DiceMatching::Six, background, 550, -100);

	oneButton->setOnMouseCallback([&](auto, auto, auto, auto)->bool {
		return InputPlayerChoice(1);
		});
	twoButton->setOnMouseCallback([&](auto, auto, auto, auto)->bool {
		return InputPlayerChoice(2);
		});
	threeButton->setOnMouseCallback([&](auto, auto, auto, auto)->bool {
		return InputPlayerChoice(3);
		});
	fourButton->setOnMouseCallback([&](auto, auto, auto, auto)->bool {
		return InputPlayerChoice(4);
		});
	fiveButton->setOnMouseCallback([&](auto, auto, auto, auto)->bool {
		return InputPlayerChoice(5);
		});
	sixButton->setOnMouseCallback([&](auto, auto, auto, auto)->bool {
		return InputPlayerChoice(6);
		});


	diceAnimation->start();
}

void DiceMatching::ChangeDiceNumRandomly() {
	// ���� ���� ���� �ʱ�ȭ
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<int> dis(1, 6);

	int newValue = -1;

	do {
		newValue = dis(gen);
	} while (newValue == diceValue);
	diceValue = newValue;

	switch (diceValue) {
	case 1:
		dice->setImage(CombatResource::DiceMatching::One);
		break;
	case 2:
		dice->setImage(CombatResource::DiceMatching::Two);
		break;
	case 3:
		dice->setImage(CombatResource::DiceMatching::Three);
		break;
	case 4:
		dice->setImage(CombatResource::DiceMatching::Four);
		break;
	case 5:
		dice->setImage(CombatResource::DiceMatching::Five);
		break;
	case 6:
		dice->setImage(CombatResource::DiceMatching::Six);
		break;
	default:
		break;
	}
}

bool DiceMatching::InputPlayerChoice(int num) {
#ifndef COMBAT_DEBUG
	// �Է� �Ұ��� ���¶�� �Է¹��� �ʴ´�. 
	if (inputLock == true) {
		return true;
	}
#endif // !COMBAT_DEBUG
	playerChoice = num;
	diceAnimation->stop();
	CompareChoice();
	resultDelayTimer->set(DiceMatchingConfig::VISIBLE_TIME);
	resultDelayTimer->start();
	inputLock = true;
	return true;
}

void DiceMatching::CompareChoice() {
	// �÷��̾ ����ٸ�
	if (playerChoice == diceValue) {
		monsters.back()->hide();
		monsters.pop_back();
		if (monsters.size() == 0) {
			showMessage("���͵��� �����ƽ��ϴ�!");
			diceAnimation->stop();
			this->previousScene->enter();
		}
		else {
			showMessage("�÷��̾ �̰���ϴ�!");
		}
	}
	// �÷��̾ ������ ���ߴٸ�
	else {
		opportunity.back()->hide();
		opportunity.pop_back();
		// ���� ��ȸ�� ���ٸ� ���� ����
		if (opportunity.size() == 0) {
			gameOverFunc(blockBreakHandler);
		}
		else {
			showMessage("���Ͱ� �̰���ϴ�...");
		}
	}
}
