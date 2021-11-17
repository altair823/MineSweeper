#include "RockPaperScissor.h"

RockPaperScissor::RockPaperScissor(ScenePtr previousScene, BlockBreakHandler& blockBreakHandler, std::function<void(BlockBreakHandler&)> gameOverFunc)
	: inputLock(false), blockBreakHandler(blockBreakHandler), gameOverFunc(gameOverFunc) {

	this->previousScene = previousScene;

	// 난수 생성 엔진 초기화
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<int> dis(0, 2);

	// 전투 배경은 무작위로 생성하지만 몬스터는 정해져 있다. 
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
	monsters.resize(3);
	for (int i = 0; i < 3; i++) {
		monsters[i] = Object::create(CombatResource::MONSTER1, background, 200 * i + 30, 250);
		monsters[i]->setScale(0.4f);
	}

	// 기회 표시
	opportunity.resize(RockPaperScissorConfig::OPPORTUNITY);
	for (int i = 0; i < RockPaperScissorConfig::OPPORTUNITY; i++) {
		opportunity[i] = Object::create(CombatResource::RockPaperScissor::Opportunity, background, 650, 0 + (80 * i));
	}
}

void RockPaperScissor::EnterBattle() {
	background->enter();
	showMessage("몬스터가 등장했습니다!\n가위바위보를 세 번 이겨야 탈출할 수 있습니다.\n기회는 "+std::to_string(RockPaperScissorConfig::OPPORTUNITY)+"번 뿐입니다!");

	rock = Object::create(CombatResource::RockPaperScissor::Rock, background, 100, -100);
	rock->setScale(0.2f);
	paper = Object::create(CombatResource::RockPaperScissor::Paper, background, 300, -100);
	paper->setScale(0.2f);
	scissor = Object::create(CombatResource::RockPaperScissor::Scissor, background, 500, -100);
	scissor->setScale(0.2f);

	// 바위 선택
	rock->setOnMouseCallback([&](auto, auto, auto, auto)->bool {
		return InputChoice(HandType::Rock);
		});

	// 보 선택
	paper->setOnMouseCallback([&](auto, auto, auto, auto)->bool {
		return InputChoice(HandType::Paper);
	});

	// 가위 선택
	scissor->setOnMouseCallback([&](auto, auto, auto, auto)->bool {
		return InputChoice(HandType::Scissors);
		});
}

bool RockPaperScissor::InputChoice(HandType handType) {
#ifndef COMBAT_DEBUG
	// 입력 불가능 상태라면 입력받지 않는다. 
	if (inputLock == true) {
		return true;
	}
#endif // !COMBAT_DEBUG
	playerChoice = handType;
	computerChoice = MakeComputerChoice();
	ShowChoices(playerChoice, computerChoice);
	CompareChoices();
	// 결과가 나오는 동안 입력을 잠근다. 
	inputLock = true;
	return true;
}

HandType RockPaperScissor::MakeComputerChoice(){
	// 난수 생성 엔진 초기화
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<int> dis(0, 2);

	// 난수 생성
	int choice = dis(gen);

	HandType result = HandType::NoChoice;
	switch (choice) {
	case 0:
		result = HandType::Rock;
		break;
	case 1:
		result = HandType::Paper;
		break;
	case 2:
		result = HandType::Scissors;
		break;
	}
	return result;
}

void RockPaperScissor::CompareChoices() {
	// 플레이어가 이겼다면
	if ((playerChoice == HandType::Rock && computerChoice == HandType::Scissors)
		|| (playerChoice == HandType::Scissors && computerChoice == HandType::Paper)
		|| (playerChoice == HandType::Paper && computerChoice == HandType::Rock)) {
		monsters.back()->hide();
		monsters.pop_back();
		// 남은 몬스터가 없다면
		if (monsters.size() == 0) {
			showMessage("몬스터들을 물리쳤습니다!");
			this->previousScene->enter();
		}
		else {
			showMessage("플레이어가 이겼습니다!");
		}
	}
	// 비기면
	else if (playerChoice == computerChoice) {
		showMessage("비겼습니다.");
	}
	// 컴퓨터가 이겼다면
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

void RockPaperScissor::ShowChoices(HandType playerChoice, HandType computerChoice) {
	std::string computerHandType;
	std::string playerHandType;

	switch (computerChoice)	{
	case HandType::Rock:
		computerHandType = CombatResource::RockPaperScissor::Rock;
		break;
	case HandType::Paper:
		computerHandType = CombatResource::RockPaperScissor::Paper;
		break;
	case HandType::Scissors:
		computerHandType = CombatResource::RockPaperScissor::Scissor;
		break;
	default:
		break;
	}

	switch (playerChoice) {
	case HandType::Rock:
		playerHandType = CombatResource::RockPaperScissor::Rock;
		break;
	case HandType::Paper:
		playerHandType = CombatResource::RockPaperScissor::Paper;
		break;
	case HandType::Scissors:
		playerHandType = CombatResource::RockPaperScissor::Scissor;
		break;
	default:
		break;
	}

	// 컴퓨터의 선택을 중앙에 출력
	auto computerHand = Object::create(computerHandType, background, 300, 150);
	computerHand->setScale(0.2f);

	// 플레이어의 선택을 중앙에 출력
	auto playerHand = Object::create(playerHandType, background, 300, 0);
	playerHand->setScale(0.2f);

	// 플레이어와 컴퓨터의 선택을 다시 지우는 타이머
	TimerPtr choicesHideTimer = Timer::create(RockPaperScissorConfig::VISIBLE_TIME);
	choicesHideTimer->setOnTimerCallback([=](auto)->bool {
		computerHand->hide();
		playerHand->hide();
		// 결과가 나오면 입력 잠금을 푼다. 
		inputLock = false;
		return true;
		});
	choicesHideTimer->start();
}

