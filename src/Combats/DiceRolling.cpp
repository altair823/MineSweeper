#include "DiceRolling.h"

std::string RDBattleBackground[] = {
	CombatResource::BACKGROUND1,
	CombatResource::BACKGROUND2,
	CombatResource::BACKGROUND3
};

DiceRolling::DiceRolling(ScenePtr previousScene) {
	this->previousScene = previousScene;

	// 난수 생성 엔진 초기화
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<int> dis(0, 2);

	background = Scene::create("전투 배경", RDBattleBackground[dis(gen) % 3]);

	// 몬스터 표시
	monsters.resize(3);
	for (int i = 0; i < 3; i++) {
		monsters[i] = Object::create(CombatResource::MONSTER2, background, 200 * i + 30, 250);
		monsters[i]->setScale(0.4f);
	}

	// 기회 표시
	opportunity.resize(DiceRollingConfig::OPPORTUNITY);
	for (int i = 0; i < DiceRollingConfig::OPPORTUNITY; i++) {
		opportunity[i] = Object::create(CombatResource::RockPaperScissor::Opportunity, background, 650, 0 + (80 * i));
	}
}

void DiceRolling::EnterBattle() {
	background->enter();
	showMessage("몬스터가 등장했습니다!\n주사위 게임을 세 번 이겨야 탈출할 수 있습니다.\n기회는 " + std::to_string(DiceRollingConfig::OPPORTUNITY) + "번 뿐입니다!");

	// 주사위를 굴리는 버튼 생성
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

	// 난수 생성 엔진 초기화
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
			showMessage("게임 오버!");
			/*
			*
			* 게임오버시 타이틀로 돌아갈 것!
			*
			*/
		}
		else {
			showMessage("몬스터가 이겼습니다...");
		}
	}
}
