#include "Stage.h"

Stage::Stage() {
	// ���� Ÿ��Ʋ �� �������� �� ��ũ��Ʈ�� ���̱� ���� ��Ż ���
	frontground = Scene::create("���� ȭ��", CombatResource::BACKGROUND1);

	// ������ ����Ǵ� ��Ż ���
	background = Scene::create("���", BoardResource::BACKGROUND);

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

	// background���� ������ Ż���ϱ� ��ư
	// �־��� ������ ������ ���� ���̱� ���� �����.
	escapeButton = Object::create(CellResource::EMPTY, background, 0, 690);
	escapeButton->setOnMouseCallback([&](auto object, int x, int y, auto action)->bool {
		board->setBoardStatus(BoardStatus::Clear);
		escapeButton->hide();
		return true;
		});
	escapeButton->hide();

	// ���������� �̺�Ʈ �ڵ鷯�� �����Ѵ�.
	EventHandler();
}

ScenePtr Stage::getFrontground() {
	return frontground;
}

void Stage::EventHandler() {
	// Ÿ�̸Ӱ� ���鼭 board�� status�� üũ�Ѵ�.
	boardStatusChecker = Timer::create(REFRESH_TIME);
	boardStatusChecker->setOnTimerCallback([&](auto)->bool {
		// Playing -> �̺�Ʈ ����
		// Escape -> Ż���ϱ� ��ư ���̱�
		if (board->getBoardStatus() == BoardStatus::Escape) {
			board->setBoardStatus(BoardStatus::Playing);
			escapeButton->show();
			showMessage("Ż�ⱸ�� ã�ҽ��ϴ�! ���������� ����� ������ Ż���ϱ� ��ư�� ��������.\n���� Ż������ �ʰ� �����ִ� �������� ȹ���ϱ� ���� ������ ��� ������ �� �ֽ��ϴ�.");
		}
		// Claer -> ���� ��������
		if (board->getBoardStatus() == BoardStatus::Clear) {
			NextStage();
		}
		// GameOver -> ���� �ʱ�ȭ?
		if (board->getBoardStatus() == BoardStatus::GameOver) {
			// ** ����׿� ** ���� ����
			std::cout << "Game over!";
			endGame();
		}
		boardStatusChecker->set(REFRESH_TIME);
		boardStatusChecker->start();
		return true;
		});

	boardStatusChecker->start();
}

void Stage::NextStage() {
	// �������� ������ �����Ѵ�.
	currentStageLevel++;

	// ������ ���������� ��� Ŭ�����ߴٸ� ������ Ŭ������ ���̴�.
	if (currentStageLevel == STAGE_COUNT) {
		// ** ����׿� ** ���� ����
		std::cout << "Game Clear!";
		endGame();
	}

	// ���� Ŭ������ ���������� ���Ҵٸ� ������ �����Ѵ�.
	else {
		// ���� ���������� �Ѿ �� ������ ��ũ��Ʈ�� �����Ѵ�.
		// script->setImage();

		// ��ũ��Ʈ�� ������ �ִ� front ������� �����Ѵ�.
		frontground->enter();

		// ���� ����ã�� ����� �����Ѵ�.
		int row = board->getRow();
		int col = board->getCol();
		board->RefreshBoard(row + 2, col + 4);

		// ���� ����ã�� ������ ����� �����Ѵ�.
	}
}

