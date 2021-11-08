#include "DiceMatching.h"

DiceMatching::DiceMatching(ScenePtr previousScene){
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
		monsters[i] = Object::create(CombatResource::MONSTER5, background, 200 * i + 30, 250);
		monsters[i]->setScale(0.4f);
	}

	// 기회 표시
	opportunity.resize(DiceMatchingConfig::OPPORTUNITY);
	for (int i = 0; i < DiceMatchingConfig::OPPORTUNITY; i++) {
		opportunity[i] = Object::create(CombatResource::OddOrEven::Opportunity, background, 660, 0 + (70 * i));
	}
}

void DiceMatching::EnterBattle(){
	
}
