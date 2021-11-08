#include "DiceMatching.h"

DiceMatching::DiceMatching(ScenePtr previousScene){
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
		opportunity[i] = Object::create(CombatResource::OddOrEven::Opportunity, background, 660, 0 + (70 * i));
	}
}

void DiceMatching::EnterBattle(){
	
}
