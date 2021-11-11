#include "Stage.h"

Stage::Stage(ScenePtr bg, ScenePtr fg) {
	background = bg;
	frontground = fg;

	// ����ã�� ���� ����
	board = new Board(background);
	board->GenerateNewBoard(INIT_BOARD_SIZE, INIT_BOARD_SIZE);

	// frontground���� ������ ���� Ÿ��Ʋ �� �������� �� ��ũ��Ʈ
	// frontground�� ������ ��ũ��Ʈ�� ������ backround�� �����Ѵ�.
	script = Object::create(CombatResource::MONSTER1, frontground, 0, 0);
	script->setOnMouseCallback([&](auto object, int x, int y, auto action)->bool {
		background->enter();
		return true;
	});

	// ���������� �̺�Ʈ �ڵ鷯�� �����Ѵ�.
	EventHandler();
}

void Stage::EventHandler() {
	// Ÿ�̸Ӱ� ���鼭 board�� status�� üũ�Ѵ�.
	boardStatusChecker = Timer::create(REFRESH_TIME);
	boardStatusChecker->setOnTimerCallback([&](auto)->bool {
		// Playing -> �̺�Ʈ ����
		// Claer -> ���� ��������
		if (board->getBoardStatus() == Status::Clear) {
			NextStage();
		}
		// GameOver -> ���� �ʱ�ȭ?
		if (board->getBoardStatus() == Status::GameOver) {
			// ** ����׿� ** ���� ����
			endGame();
		}
		boardStatusChecker->set(REFRESH_TIME);
		boardStatusChecker->start();
		return true;
		});

	boardStatusChecker->start();

	// ����׿� Ÿ�̸� ���� �޼���
	std::cout << ". . . Now Board Status Checker is working . . ." << std::endl;
}

void Stage::NextStage() {
	// ���� ���������� �Ѿ �� ������ ��ũ��Ʈ�� �����Ѵ�.
	// script->setImage();

	// ��ũ��Ʈ�� ������ �ִ� front ������� �����Ѵ�.
	frontground->enter();

	// �������� ������ �����Ѵ�.
	currentStageLevel++;

	// ���� ����ã�� ����� �����Ѵ�.
	int row = board->getRow();
	int col = board->getCol();
	board->RefreshBoard(row + 2, col + 4);
}

