#include "OddOrEven.h"

OddOrEven::OddOrEven(ScenePtr previousScene, BlockBreakHandler& blockBreakHandler, std::function<void(BlockBreakHandler&)> gameOverFunc)
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
		monsters[i] = Object::create(CombatResource::MONSTER4, background, 200 * i + 30, 250);
		monsters[i]->setScale(0.4f);
	}

	// ��ȸ ǥ��
	opportunity.resize(OddOrEvenConfig::OPPORTUNITY);
	for (int i = 0; i < OddOrEvenConfig::OPPORTUNITY; i++) {
		opportunity[i] = Object::create(CombatResource::OddOrEven::OPPERTUNITY, background, 660, 0 + (70 * i));
	}
}

void OddOrEven::EnterBattle() {
	background->enter();
	showMessage("���Ͱ� �����߽��ϴ�!\n���Ϳ� Ȧ¦������ �ؼ� " + std::to_string(OddOrEvenConfig::MONSTER_COUNT) + "�� �̰ܾ� Ż���� �� �ֽ��ϴ�.\n��ȸ�� "
		+ std::to_string(OddOrEvenConfig::OPPORTUNITY) + "�� ���Դϴ�!");

	dice = Object::create(CombatResource::OddOrEven::ONE, background, 270, 150);

	diceAnimation = Timer::create(OddOrEvenConfig::DICE_ROLL_SPEED);
	diceAnimation->setOnTimerCallback([&](auto)->bool {
		ChangeDiceNumRandomly(&diceValue, dice);
		diceAnimation->set(OddOrEvenConfig::DICE_ROLL_SPEED);
		diceAnimation->start();
		return true;
		});

	resultDelayTimer = Timer::create(OddOrEvenConfig::VISIBLE_TIME);
	resultDelayTimer->setOnTimerCallback([&](auto)->bool {
		if (diceAnimation != nullptr) {
			diceAnimation->start();
		}
		// ����� ������ �Է� ����� Ǭ��. 
		inputLock = false;
		return true;
		});

	OddButton = Object::create(CombatResource::OddOrEven::ODD_BUTTON, background, 100, -100);
	EvenButton = Object::create(CombatResource::OddOrEven::EVEN_BUTTON, background, 380, -100);

	OddButton->setOnMouseCallback([&](auto, auto, auto, auto)->bool {
		return InputChoice(PlayerChoice::Odd);
		});

	EvenButton->setOnMouseCallback([&](auto, auto, auto, auto)->bool {
		return InputChoice(PlayerChoice::Even);
		});

	diceAnimation->start();
}

bool OddOrEven::InputChoice(PlayerChoice choice) {
#ifndef COMBAT_DEBUG
	// �Է� �Ұ��� ���¶�� �Է¹��� �ʴ´�. 
	if (inputLock == true) {
		return true;
	}
#endif // !COMBAT_DEBUG
	playerChoice = choice;
	diceAnimation->stop();
	CompareChoice();
	resultDelayTimer->set(OddOrEvenConfig::VISIBLE_TIME);
	resultDelayTimer->start();
	// ����� ������ ���� �Է��� ��ٴ�. 
	inputLock = true;
	return true;
}

void OddOrEven::ChangeDiceNumRandomly(int* value, ObjectPtr object) {

	// ���� ���� ���� �ʱ�ȭ
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<int> dis(1, 6);

	int newValue = -1;

	do {
		newValue = dis(gen);
	} while (newValue == *value);
	*value = newValue;

	switch (*value) {
	case 1:
		object->setImage(CombatResource::OddOrEven::ONE);
		break;
	case 2:
		object->setImage(CombatResource::OddOrEven::TWO);
		break;
	case 3:
		object->setImage(CombatResource::OddOrEven::THREE);
		break;
	case 4:
		object->setImage(CombatResource::OddOrEven::FOUR);
		break;
	case 5:
		object->setImage(CombatResource::OddOrEven::FIVE);
		break;
	case 6:
		object->setImage(CombatResource::OddOrEven::SIX);
		break;
	default:
		break;
	}

}

void OddOrEven::CompareChoice() {
	// �÷��̾ ����ٸ�
	if (((playerChoice == PlayerChoice::Odd) && ((diceValue == 1) || (diceValue == 3) || (diceValue == 5))) 
	|| ((playerChoice == PlayerChoice::Even) && ((diceValue == 2) || (diceValue == 4) || (diceValue == 6)))) {
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

OddOrEven::~OddOrEven() {
	diceAnimation->stop();
	diceAnimation.reset();
	resultDelayTimer->stop();
	resultDelayTimer.reset();
}