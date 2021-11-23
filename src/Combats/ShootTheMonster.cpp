#include "ShootTheMonster.h"

ShootTheMonster::ShootTheMonster(ScenePtr previousScene, BlockBreakHandler& blockBreakHandler, std::function<void(BlockBreakHandler&)> gameOverFunc)
	: inputLock(false), blockBreakHandler(blockBreakHandler), gameOverFunc(gameOverFunc) {
	this->previousScene = previousScene;
	// ���� ���� ���� �ʱ�ȭ
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<int> dis(0, 2);
	
	switch (dis(gen)){
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
		monsters[i] = Object::create(CombatResource::MONSTER3, background, 200 * i + 30, 250);
		monsters[i]->setScale(0.4f);
	}

	// ��ȸ ǥ��
	opportunity.resize(ShootTheMonsterConfig::OPPORTUNITY);
	for (int i = 0; i < ShootTheMonsterConfig::OPPORTUNITY; i++) {
		opportunity[i] = Object::create(CombatResource::ShootTheMonster::OPPORTUNITY, background, 660, 0 + (70 * i));
	}
}

void ShootTheMonster::EnterBattle() {
	background->enter();
	showMessage("���Ͱ� �����߽��ϴ�!\n���͸� "+std::to_string(ShootTheMonsterConfig::MONSTER_COUNT)+"�� ��ƾ� Ż���� �� �ֽ��ϴ�.\n��ȸ�� " 
		+ std::to_string(ShootTheMonsterConfig::OPPORTUNITY) + "�� ���Դϴ�!");

	leftShoot = Object::create(CombatResource::ShootTheMonster::PISTOL, background, 80, -100);
	centerShoot = Object::create(CombatResource::ShootTheMonster::PISTOL, background, 280, -100);
	rightShoot = Object::create(CombatResource::ShootTheMonster::PISTOL, background, 480, -100);

	monsterShowTimer = Timer::create(ShootTheMonsterConfig::VISIBLE_TIME);
	monsterShowTimer->setOnTimerCallback([&](auto)->bool {
		// ���͸� �������� �� �� ������
		ShowMonsterRandomly();
		// ���� �ð��� ������ �ٸ� ��ġ���� ������
		monsterShowTimer->set(ShootTheMonsterConfig::VISIBLE_TIME);
		monsterShowTimer->start();
		// ����� ������ �Է� ����� Ǭ��. 
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
	// �Է� �Ұ��� ���¶�� �Է¹��� �ʴ´�. 
	if (inputLock == true) {
		return true;
	}
#endif // !COMBAT_DEBUG
	playerShootDir = direction;
	CompareDirection(playerShootDir, monsterPosition);
	// ����� ������ ���� �Է��� ��ٴ�. 
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
	// ����
	case 0:
		if (Direction::Left == monsterPosition) {
			goto REGENERATE;
		}
		monsters[0]->show();
		monsters[1]->hide();
		monsters[2]->hide();
		monsterPosition = Direction::Left;
		break;
	// �߰�
	case 1:
		if (Direction::Center == monsterPosition) {
			goto REGENERATE;
		}
		monsters[0]->hide();
		monsters[1]->show();
		monsters[2]->hide();
		monsterPosition = Direction::Center;
		break;
	// ������
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
	// ���� ��� �Ѿ� �ϳ� ����
	if (opportunity.size() != 0) {
		opportunity.back()->hide();
		opportunity.pop_back();
	}
	
	if (playerDir == monsterDir) {
		monsterRemainCount--;
		if (monsterRemainCount == 0) {
			showMessage("���͵��� ��� �����ƽ��ϴ�!");
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
			showMessage("���ƽ��ϴ�!");
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
