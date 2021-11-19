#include "Stage.h"

Stage::Stage() {
	// ���ӿ� �ʿ��� ��Ż ������ �����Ѵ�.
	setTitle();
	setScriptBackground();
	setBackground();
	setEnding();

	// ���������� �̺�Ʈ �ڵ鷯�� �����Ѵ�.
	EventHandler();
}

void Stage::setTitle() {
	// Ÿ��Ʋ ȭ�� �� Ÿ��Ʋ ȭ���� ������ ��Ż ������Ʈ ����
	title = Scene::create("Ÿ��Ʋ ȭ��", TitleResource::Title);

	// ���� ���� ��ư
	startButton = Object::create(TitleResource::StartButton, title, 480, 100);
	startButton->setOnMouseCallback([&](auto object, int x, int y, auto action)->bool {
		scriptBackground->enter();
		return true;
		});

	// ���� ��� ��ư
	howToPlayButton = Object::create(EndingResource::endButton, title, 480, 10);
	howToPlayButton->setOnMouseCallback([&](auto object, int x, int y, auto action)->bool {
		// ** ����׿� **
		endGame();
		return true;
		});
}

void Stage::setScriptBackground() {
	// ���� Ÿ��Ʋ �� �������� �� ��ũ��Ʈ�� ���̱� ���� ��Ż ���
	// ** �ڵ� �������� �������� 1 ���� ���� scriptBackground�� ����� stage 1 clear�� ǥ�õ� �׽�Ʈ �̹����� ���� �� **
	scriptBackground = Scene::create("���� ȭ��", scriptBackgroundImage[clearedStageCount]);

	// scriptbackground���� ������ �������� �� ��ũ��Ʈ
	// scriptbackground�� ������ ��ũ��Ʈ�� ������ background ������� ����.
	script = Object::create(scriptImage[clearedStageCount], scriptBackground, 480, 10);
	script->setOnMouseCallback([&](auto object, int x, int y, auto action)->bool {
		// ~ ������ ������ ��Ʈ��Ʈ�� ���̱� ���� �̹����� �����ϴ� �ڵ尡 �ʿ��� ���� ���� ~
		background->enter();
		return true;
		});
}

void Stage::setBackground() {
	// ������ ����Ǵ� ��Ż ���
	background = Scene::create("���", backgroundImage[clearedStageCount]);

	// ����ã�� ���� ����
	board = new Board(background);
	board->GenerateNewBoard(INIT_BOARD_SIZE, INIT_BOARD_SIZE);

	// background���� ������ Ż���ϱ� ��ư
	// �־��� ������ ������ ���� ���̱� ���� �����.
	escapeButton = Object::create(CellResource::EMPTY, background, 0, 690);
	escapeButton->setOnMouseCallback([&](auto object, int x, int y, auto action)->bool {
		board->setBoardStatus(BoardStatus::Clear);
		escapeButton->hide();
		return true;
		});
	escapeButton->hide();
}

void Stage::setEnding() {
	// ���� ȭ���� ���̱� ���� ��Ż ���
	ending = Scene::create("����", EndingResource::Ending);

	// ���� ȭ�鿡 ǥ�õǴ� ��ũ��Ʈ
	endingScript = Object::create(EndingResource::endButton, ending, 480, 10);
	endingScript->setOnMouseCallback([&](auto object, int x, int y, auto action)->bool {
		endGame();
		return true;
		});
}

ScenePtr Stage::getTitle() {
	std::cout << "now showing title" << std::endl;
	return title;
}

void Stage::EventHandler() {
	// Ÿ�̸Ӱ� ���鼭 board�� status�� üũ�Ѵ�.
	boardStatusChecker = Timer::create(REFRESH_TIME);
	boardStatusChecker->setOnTimerCallback([&](auto)->bool {
		// Playing -> �̺�Ʈ ����

		// Escape -> Ż���ϱ� ��ư ���̱�
		if (board->getBoardStatus() == BoardStatus::Escape) {
			// �ٷ� Ż������ �ʴ� ��츦 ���� ���� ���¸� ����
			board->setBoardStatus(BoardStatus::Playing);
			escapeButton->show();
			showMessage("Ż�ⱸ�� ã�ҽ��ϴ�! ���������� ����� ������ Ż���ϱ� ��ư�� ��������.\n���� Ż������ �ʰ� �����ִ� �������� ȹ���ϱ� ���� ������ ��� ������ �� �ֽ��ϴ�.");
		}

		// Claer -> ���� ��������
		if (board->getBoardStatus() == BoardStatus::Clear) {
			escapeButton->hide();
			NextStage();
		}

		// GameOver -> ���� �ʱ�ȭ?
		if (board->getBoardStatus() == BoardStatus::GameOver) {
			title->enter();
			showMessage("���� ����� ���� ���� �����Ǿ����ϴ�.\n�ٽ� �����غ�����.");
		}

		boardStatusChecker->set(REFRESH_TIME);
		boardStatusChecker->start();

		return true;
		});

	boardStatusChecker->start();
}

void Stage::NextStage() {
	// �������� ������ �����Ѵ�.
	clearedStageCount++;

	// Ŭ���� �ؾ��ϴ� �������� ������ ������ ��� ���������� �̺�Ʈ �ڵ鷯�� ���߰� ���� ������� �����Ѵ�
	if (clearedStageCount >= NUM_OF_STAGE_TO_BE_CLEARED) {
		boardStatusChecker->stop();
		ending->enter();
	}

	// Ŭ���� �ؾ��ϴ� �������� ������ ���� ��� ���� ���������� �����Ѵ�
	else {
		// �������� Ŭ���� �� ������ ��ũ��Ʈ�� �����Ѵ�.
		scriptBackground->setImage(scriptBackgroundImage[clearedStageCount]);
		script->setImage(scriptImage[clearedStageCount]);

		// ��ũ��Ʈ�� ������ �ִ� scriptBackground ������� �����Ѵ�.
		scriptBackground->enter();

		// ���� ����ã�� ������ ����� �����Ѵ�.
		background->setImage(backgroundImage[clearedStageCount]);

		// ���� ����ã�� ����� �����Ѵ�.
		int row = board->getRow();
		int col = board->getCol();
		board->RefreshBoard(row + 2, col + 4);
	}
}

