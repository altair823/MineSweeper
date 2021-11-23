#include "ShootTheMonster.h"

ShootTheMonster::ShootTheMonster(ScenePtr previousScene, BlockBreakHandler& blockBreakHandler, std::function<void(BlockBreakHandler&)> gameOverFunc)
	: inputLock(false), blockBreakHandler(blockBreakHandler), gameOverFunc(gameOverFunc) {
	this->previousScene = previousScene;
	// 난수 생성 엔진 초기화
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<int> dis(0, 2);
	
	switch (dis(gen)){
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
		monsters[i] = Object::create(CombatResource::MONSTER3, background, 200 * i + 30, 250);
		monsters[i]->setScale(0.4f);
	}

	// 기회 표시
	opportunity.resize(ShootTheMonsterConfig::OPPORTUNITY);
	for (int i = 0; i < ShootTheMonsterConfig::OPPORTUNITY; i++) {
		opportunity[i] = Object::create(CombatResource::ShootTheMonster::OPPORTUNITY, background, 660, 0 + (70 * i));
	}
}

void ShootTheMonster::EnterBattle() {
	background->enter();
	showMessage("몬스터가 등장했습니다!\n몬스터를 "+std::to_string(ShootTheMonsterConfig::MONSTER_COUNT)+"번 쏘아야 탈출할 수 있습니다.\n기회는 " 
		+ std::to_string(ShootTheMonsterConfig::OPPORTUNITY) + "번 뿐입니다!");

	leftShoot = Object::create(CombatResource::ShootTheMonster::PISTOL, background, 80, -100);
	centerShoot = Object::create(CombatResource::ShootTheMonster::PISTOL, background, 280, -100);
	rightShoot = Object::create(CombatResource::ShootTheMonster::PISTOL, background, 480, -100);

	monsterShowTimer = Timer::create(ShootTheMonsterConfig::VISIBLE_TIME);
	monsterShowTimer->setOnTimerCallback([&](auto)->bool {
		// 몬스터를 무작위로 한 번 보여줌
		ShowMonsterRandomly();
		// 일정 시간이 지나면 다른 위치에서 보여줌
		monsterShowTimer->set(ShootTheMonsterConfig::VISIBLE_TIME);
		monsterShowTimer->start();
		// 결과가 나오면 입력 잠금을 푼다. 
		inputLock = false;
		return true;
		});

	leftShoot->setOnMouseCallback([&](auto, auto, auto, auto)->bool {
		return InputChoice(Direction::Left);
	});
	centerShoot->setOnMouseCallback([&](auto, auto, auto, auto)->bool {
		return InputChoice(Direction::Center);
	});
	rightShoot->setOnMouseCallback([&](auto, auto, auto, auto)->bool {
		return InputChoice(Direction::Right);
	});
	monsterShowTimer->start();
}

bool ShootTheMonster::InputChoice(Direction direction) {
#ifndef COMBAT_DEBUG
	// 입력 불가능 상태라면 입력받지 않는다. 
	if (inputLock == true) {
		return true;
	}
#endif // !COMBAT_DEBUG
	playerShootDir = direction;
	CompareDirection(playerShootDir, monsterPosition);
	// 결과가 나오는 동안 입력을 잠근다. 
	inputLock = true;
	return true;
}

void ShootTheMonster::ShowMonsterRandomly() {
	TimerPtr showAllMonsterTimer = Timer::create(2);
	showAllMonsterTimer->setOnTimerCallback([&](auto)->bool {
		for (auto& monster : monsters) {
			monster->hide();
		}
		return true;
		});

REGENERATE:
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<int> dis(0, 2);

	switch (dis(gen)) {
	// 왼쪽
	case 0:
		if (Direction::Left == monsterPosition) {
			goto REGENERATE;
		}
		monsters[0]->show();
		monsters[1]->hide();
		monsters[2]->hide();
		monsterPosition = Direction::Left;
		break;
	// 중간
	case 1:
		if (Direction::Center == monsterPosition) {
			goto REGENERATE;
		}
		monsters[0]->hide();
		monsters[1]->show();
		monsters[2]->hide();
		monsterPosition = Direction::Center;
		break;
	// 오른쪽
	case 2:
		if (Direction::Right == monsterPosition) {
			goto REGENERATE;
		}
		monsters[0]->hide();
		monsters[1]->hide();
		monsters[2]->show();
		monsterPosition = Direction::Right;
		break;
	default:
		break;
	}


}

void ShootTheMonster::CompareDirection(Direction playerDir, Direction monsterDir) {
	// 총을 쏘면 총알 하나 제거
	if (opportunity.size() != 0) {
		opportunity.back()->hide();
		opportunity.pop_back();
	}
	
	if (playerDir == monsterDir) {
		monsterRemainCount--;
		if (monsterRemainCount == 0) {
			showMessage("몬스터들을 모두 물리쳤습니다!");
			this->previousScene->enter();
		}
		else {
			ChangeMonsterToExplode(playerDir);
		}
	}
	else if (opportunity.size() < monsterRemainCount) {
		gameOverFunc(blockBreakHandler);
	}
	else {
		if (opportunity.size() == 0) {
			gameOverFunc(blockBreakHandler);
		}
		else {
			showMessage("놓쳤습니다!");
		}
	}
}

void ShootTheMonster::ChangeMonsterToExplode(Direction direction) {
	TimerPtr monsterExplodeTimer = Timer::create(1);

	if (monsterPosition == direction) {
		switch (monsterPosition) {
		case Direction::Left:
			dirNum = 0;
			break;
		case Direction::Center:
			dirNum = 1;
			break;
		case Direction::Right:
			dirNum = 2;
			break;
		default:
			break;
		}
		monsterShowTimer->stop();
		monsters[dirNum]->setImage(CombatResource::ShootTheMonster::EXPLODE);
		monsterExplodeTimer->start();
	}

	monsterExplodeTimer->setOnTimerCallback([&](auto)->bool {
		if (monsterShowTimer != nullptr) {
			monsters[dirNum]->setImage(CombatResource::MONSTER3);
			monsterShowTimer->start();
		}
		return true;
		});
}

void ShootTheMonster::StopTimerAnimation() {
	monsterShowTimer->stop();
}

ShootTheMonster::~ShootTheMonster() {
	monsterShowTimer.reset();
}
