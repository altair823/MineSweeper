#include "OddOrEven.h"

OddOrEven::OddOrEven(ScenePtr previousScene, BlockBreakHandler& blockBreakHandler, std::function<void(BlockBreakHandler&)> gameOverFunc)
	: inputLock(false), blockBreakHandler(blockBreakHandler), gameOverFunc(gameOverFunc) {
	this->previousScene = previousScene;
	// 난수 생성 엔진 초기화
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<int> dis(0, 2);

	switch (dis(gen)) {
	case 0:
		background = Scene::create("전투 배경", CombatResource::BACKGROUND1);
		break;
	case 1:
		background = Scene::create("전투 배경", CombatResource::BACKGROUND2);
		break;
	case 2:
		background = Scene::create("전투 배경", CombatResource::BACKGROUND3);
		break;
	default:
		break;
	}

	// 몬스터 표시
	monsters.resize(3);
	for (int i = 0; i < 3; i++) {
		monsters[i] = Object::create(CombatResource::MONSTER4, background, 200 * i + 30, 250);
		monsters[i]->setScale(0.4f);
	}

	// 기회 표시
	opportunity.resize(OddOrEvenConfig::OPPORTUNITY);
	for (int i = 0; i < OddOrEvenConfig::OPPORTUNITY; i++) {
		opportunity[i] = Object::create(CombatResource::OddOrEven::OPPORTUNITY, background, 660, 0 + (70 * i));
	}
}

void OddOrEven::EnterBattle() {
	background->enter();
	showMessage("몬스터가 등장했습니다!\n몬스터와 홀짝게임을 해서 " + std::to_string(OddOrEvenConfig::MONSTER_COUNT) + "번 이겨야 탈출할 수 있습니다.\n기회는 "
		+ std::to_string(OddOrEvenConfig::OPPORTUNITY) + "번 뿐입니다!");

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
		// 결과가 나오면 입력 잠금을 푼다. 
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
	// 입력 불가능 상태라면 입력받지 않는다. 
	if (inputLock == true) {
		return true;
	}
#endif // !COMBAT_DEBUG
	playerChoice = choice;
	diceAnimation->stop();
	CompareChoice();
	resultDelayTimer->set(OddOrEvenConfig::VISIBLE_TIME);
	resultDelayTimer->start();
	// 결과가 나오는 동안 입력을 잠근다. 
	inputLock = true;
	return true;
}

void OddOrEven::ChangeDiceNumRandomly(int* value, ObjectPtr object) {

	// 난수 생성 엔진 초기화
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
	// 플레이어가 맞췄다면
	if (((playerChoice == PlayerChoice::Odd) && ((diceValue == 1) || (diceValue == 3) || (diceValue == 5))) 
	|| ((playerChoice == PlayerChoice::Even) && ((diceValue == 2) || (diceValue == 4) || (diceValue == 6)))) {
		monsters.back()->hide();
		monsters.pop_back();
		if (monsters.size() == 0) {
			showMessage("몬스터들을 물리쳤습니다!");
			this->previousScene->enter();
		}
		else {
			showMessage("플레이어가 이겼습니다!");
		}
	}
	// 플레이어가 맞추지 못했다면
	else {
		opportunity.back()->hide();
		opportunity.pop_back();
		// 남은 기회가 없다면 게임 오버
		if (opportunity.size() == 0) {
			gameOverFunc(blockBreakHandler);
		}
		else {
			showMessage("몬스터가 이겼습니다...");
		}
	}
}

void OddOrEven::StopTimerAnimation() {
	diceAnimation->stop();
	resultDelayTimer->stop();
}

OddOrEven::~OddOrEven() {
	diceAnimation.reset();
	resultDelayTimer.reset();
}