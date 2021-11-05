#include "RockPaperScissor.h"
std::string BattleBackground[] = {
	CombatResource::BACKGROUND1,
	CombatResource::BACKGROUND2,
	CombatResource::BACKGROUND3
};
RockPaperScissor::RockPaperScissor(ScenePtr previousScene) {
	this->previousScene = previousScene;

	// ���� ����� �������� ���������� ���ʹ� ������ �ִ�. 
	background = Scene::create("���� ���", BattleBackground[rand() % 3]);
	monsters.resize(3);
	for (int i = 0; i < 3; i++) {
		monsters[i] = Object::create(CombatResource::MONSTER1, background, 200 * i + 30, 250);
		monsters[i]->setScale(0.4f);
	}

	// ��ȸ ǥ��
	opportunity.resize(ROCK_SCISSORS_PAPER_OPPORTUNITY);
	for (int i = 0; i < ROCK_SCISSORS_PAPER_OPPORTUNITY; i++) {
		opportunity[i] = Object::create(CombatResource::RockPaperScissor::Opportunity, background, 650, 0 + (80 * i));
	}
}

void RockPaperScissor::EnterBattle() {
	background->enter();
	showMessage("���Ͱ� �����߽��ϴ�!\n������������ �� �� �̰ܾ� Ż���� �� �ֽ��ϴ�.\n��ȸ�� "+std::to_string(ROCK_SCISSORS_PAPER_OPPORTUNITY)+"�� ���Դϴ�!");

	rock = Object::create(CombatResource::RockPaperScissor::Rock, background, 100, -100);
	rock->setScale(0.2f);
	paper = Object::create(CombatResource::RockPaperScissor::Paper, background, 300, -100);
	paper->setScale(0.2f);
	scissor = Object::create(CombatResource::RockPaperScissor::Scissor, background, 500, -100);
	scissor->setScale(0.2f);

	// ���� ����
	rock->setOnMouseCallback([&](auto, auto, auto, auto)->bool {
		playerChoice = HandType::Rock;
		computerChoice = MakeComputerChoice();
		ShowChoices(playerChoice, computerChoice);
		CompareChoices(playerChoice, computerChoice);
		return true;
		});

	// �� ����
	paper->setOnMouseCallback([&](auto, auto, auto, auto)->bool {
		playerChoice = HandType::Paper;
		computerChoice = MakeComputerChoice();
		ShowChoices(playerChoice, computerChoice);
		CompareChoices(playerChoice, computerChoice);
		return true;
	});

	// ���� ����
	scissor->setOnMouseCallback([&](auto, auto, auto, auto)->bool {
		playerChoice = HandType::Scissors;
		computerChoice = MakeComputerChoice();
		ShowChoices(playerChoice, computerChoice);
		CompareChoices(playerChoice, computerChoice);
		return true;
		});
}

HandType RockPaperScissor::MakeComputerChoice(){
	// ���� ���� ���� �ʱ�ȭ
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<int> dis(0, 2);

	// ���� ����
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

void RockPaperScissor::CompareChoices(HandType playerChoice, HandType computerChoice) {
	// �÷��̾ �̰�ٸ�
	if ((playerChoice == HandType::Rock && computerChoice == HandType::Scissors)
		|| (playerChoice == HandType::Scissors && computerChoice == HandType::Paper)
		|| (playerChoice == HandType::Paper && computerChoice == HandType::Rock)) {
		monsters.back()->hide();
		monsters.pop_back();
		winCount++;
		// ���� ���Ͱ� ���ٸ�
		if (monsters.size() == 0) {
			showMessage("���͵��� �����ƽ��ϴ�!");
			this->previousScene->enter();
		}
		else {
			showMessage("�÷��̾ �̰���ϴ�!");
		}
	}
	// ����
	else if (playerChoice == computerChoice) {
		showMessage("�����ϴ�.");
	}
	// ��ǻ�Ͱ� �̰�ٸ�
	else {
		opportunity.back()->hide();
		opportunity.pop_back();
		looseCount++;
		// ���� ��ȸ�� ���ٸ� ���� ����
		if (opportunity.size() == 0) {
			showMessage("���� ����!");
			/*
			* 
			* ���ӿ����� Ÿ��Ʋ�� ���ư� ��!
			* 
			*/
		}
		else {
			showMessage("���Ͱ� �̰���ϴ�...");
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

	// ��ǻ���� ������ �߾ӿ� ���
	auto computerHand = Object::create(computerHandType, background, 300, 150);
	computerHand->setScale(0.2f);

	// �÷��̾��� ������ �߾ӿ� ���
	auto playerHand = Object::create(playerHandType, background, 300, 0);
	playerHand->setScale(0.2f);

	// �÷��̾�� ��ǻ���� ������ �ٽ� ����� Ÿ�̸�
	TimerPtr choicesHideTimer = Timer::create(VISIBLE_TIME);
	choicesHideTimer->setOnTimerCallback([=](auto)->bool {
		computerHand->hide();
		playerHand->hide();
		return true;
		});
	choicesHideTimer->start();
}

