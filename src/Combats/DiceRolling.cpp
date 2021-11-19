#include "DiceRolling.h"

std::string RDBattleBackground[] = {
	CombatResource::BACKGROUND1,
	CombatResource::BACKGROUND2,
	CombatResource::BACKGROUND3
};

DiceRolling::DiceRolling(ScenePtr previousScene, BlockBreakHandler& blockBreakHandler, std::function<void(BlockBreakHandler&)> gameOverFunc)
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
		monsters[i] = Object::create(CombatResource::MONSTER2, background, 200 * i + 30, 250);
		monsters[i]->setScale(0.4f);
	}

	// 기회 표시
	opportunity.resize(DiceRollingConfig::OPPORTUNITY);
	for (int i = 0; i < DiceRollingConfig::OPPORTUNITY; i++) {
		opportunity[i] = Object::create(CombatResource::DiceRolling::OPPORTUNITY, background, 650, 0 + (80 * i));
	}
}

void DiceRolling::EnterBattle() {
	background->enter();
	showMessage("몬스터가 등장했습니다!\n주사위 게임을 세 번 이겨야 탈출할 수 있습니다.\n기회는 " + std::to_string(DiceRollingConfig::OPPORTUNITY) + "번 뿐입니다!");

	// 주사위를 굴리는 버튼 생성
	stopButton = Object::create(CombatResource::DiceRolling::BUTTON, background, 260, -120);

	computerDice = Object::create(CombatResource::DiceRolling::ONE, background, 270, 150);
	playerDice = Object::create(CombatResource::DiceRolling::ONE, background, 270, 30);

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
		if (computerDiceAnimation != nullptr && playerDiceAnimation != nullptr) {
			computerDiceAnimation->start();
			playerDiceAnimation->start();
		}
		// 결과가 나오면 입력 잠금을 푼다. 
		inputLock = false;
		return true;
		});

	stopButton->setOnMouseCallback([&](auto, auto, auto, auto)->bool {
#ifndef COMBAT_DEBUG
		// 입력 불가능 상태라면 입력받지 않는다. 
		if (inputLock == true) {
			return true;
		}
#endif // !COMBAT_DEBUG
		computerDiceAnimation->stop();
		playerDiceAnimation->stop();

		CompareDice();

		resultDelayTimer->set(DiceRollingConfig::VISIBLE_TIME);
		resultDelayTimer->start();
		// 결과가 나오는 동안 입력을 잠근다. 
		inputLock = true;
		return true;
		});

	computerDiceAnimation->start();
	playerDiceAnimation->start();
}

void DiceRolling::ChangeDiceNumRandomly(int* value, ObjectPtr object) {

	// 난수 생성 엔진 초기화
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<int> dis(1, 6);

	*value = dis(gen);

	switch (*value) {
	case 1:
		object->setImage(CombatResource::DiceRolling::ONE);
		break;
	case 2:
		object->setImage(CombatResource::DiceRolling::TWO);
		break;
	case 3:
		object->setImage(CombatResource::DiceRolling::THREE);
		break;
	case 4:
		object->setImage(CombatResource::DiceRolling::FOUR);
		break;
	case 5:
		object->setImage(CombatResource::DiceRolling::FIVE);
		break;
	case 6:
		object->setImage(CombatResource::DiceRolling::SIX);
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
			showMessage("몬스터들을 물리쳤습니다!");
			this->previousScene->enter();
		}
		else {
			showMessage("플레이어가 이겼습니다!");
		}
	}
	else if (playerDiceValue == computerDiceValue) {
		showMessage("비겼습니다.");
	}
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

DiceRolling::~DiceRolling() {
	computerDiceAnimation->stop();
	computerDiceAnimation.reset();
	playerDiceAnimation->stop();
	playerDiceAnimation.reset();
	resultDelayTimer->stop();
	resultDelayTimer.reset();
}