#include "Stage.h"

Stage::Stage() {
	// Board�� Scene
	boardBackground = Scene::create("���� ���", BoardResource::BACKGROUND1);
	board = new Board(boardBackground, INIT_LIFE_COUNT);
}

void Stage::StartGame() {
	// Ÿ��Ʋ ȭ�� �� Ÿ��Ʋ ȭ���� ������ ��Ż ������Ʈ ����
	title = Scene::create("Ÿ��Ʋ", TitleResource::TITLE);

	// ���� ���� ��ư
	ObjectPtr startButton = Object::create(TitleResource::START_BUTTON, title, 480, 100);
	startButton->setOnMouseCallback([&](auto object, int x, int y, auto action)->bool {
		// �� ù ��ũ��Ʈ ���
		ShowScript(0);
		CreateBoard();
		scriptBackground->enter();
		return true;
		});

	// ���� ��� ��ư
	ObjectPtr howToPlayButton = Object::create(EndingResource::END_BUTTON, title, 480, 10);
	howToPlayButton->setOnMouseCallback([&](auto object, int x, int y, auto action)->bool {
		/*
		* 
		* TODO ���� �̹��� ����
		* 
		*/
		return true;
		});

	startGame(title);
}

void Stage::ShowScript(int stageNum) {
	// �������� �� ��ũ��Ʈ ��� ����
	switch (stageNum) {
	case 0:
		scriptBackground = Scene::create("��ũ��Ʈ ���", ScriptResource::SCRIPT_BACKGROUND_1);
		script = Object::create(ScriptResource::SCRIPT_IMAGE_1, scriptBackground, 480, 200);
		break;
	case 1:
		scriptBackground->setImage(ScriptResource::SCRIPT_BACKGROUND_2);
		script->setImage(ScriptResource::SCRIPT_IMAGE_2);
		break;
	case 2:
		scriptBackground->setImage(ScriptResource::SCRIPT_BACKGROUND_3);
		script->setImage(ScriptResource::SCRIPT_IMAGE_3);
		break;
	default:
		break;
	}

	nextButton = Object::create(ScriptResource::SCRIPT_IMAGE_1, scriptBackground, 480, 10);
	nextButton->setOnMouseCallback([&](auto object, int x, int y, auto action)->bool {
		/*
		* 
		* TODO ��ũ��Ʈ�� �������� ��� ���⼭ �ѱ� ��. 
		* 
		*/
		boardBackground->enter();
		return true;
		});

	scriptBackground->enter();
}

void Stage::CreateBoard() {
	board->GenerateNewBoard(STAGE1_ROW, STAGE1_COL);

	// Ż���ϱ� ������
	// Ż�ⱸ�� �߰��ϸ� ���̰� �Ѵ�. 
	escapeButton = Object::create(CellResource::EMPTY, boardBackground, 0, 690, false);
	escapeButton->setOnMouseCallback([&](auto object, int x, int y, auto action)->bool {
		board->setBoardStatus(BoardStatus::Clear);
		return true;
		});

	// ������ ���¸� ó���� �ڵ鷯 ���� ����
	StartStatusHandler();
}

void Stage::EnterEnding() {
	// ���� ȭ���� ���̱� ���� ��Ż ���
	ending = Scene::create("���� ���", EndingResource::ENDING);

	// ���� ȭ�鿡 ǥ�õǴ� ��ũ��Ʈ
	endingScript = Object::create(EndingResource::END_BUTTON, ending, 480, 10);
	endingScript->setOnMouseCallback([&](auto object, int x, int y, auto action)->bool {
		endGame();
		return true;
		});

	ending->enter();
}

void Stage::StartStatusHandler() {
	// Ÿ�̸Ӱ� ���鼭 board�� status�� üũ�Ѵ�.
	boardStatusChecker = Timer::create(REFRESH_TIME);
	boardStatusChecker->setOnTimerCallback([&](auto)->bool {
		// Escape -> Ż���ϱ� ��ư ���̱�
		if (board->getBoardStatus() == BoardStatus::Escape) {
			// �ٷ� Ż������ �ʴ� ��츦 ���� ���� ���¸� ����
			board->setBoardStatus(BoardStatus::Playing);
			escapeButton->show();
			showMessage("Ż�ⱸ�� ã�ҽ��ϴ�! ���������� ����� ������ Ż���ϱ� ��ư�� ��������.\n���� Ż������ �ʰ� �����ִ� �������� ȹ���ϱ� ���� ������ ��� ������ �� �ֽ��ϴ�.");
		}

		// Claer -> ���� ���������� �̵�
		if (board->getBoardStatus() == BoardStatus::Clear) {
			escapeButton->hide();
			EnterNextStage();
		}

		// GameOver -> �����
		if (board->getBoardStatus() == BoardStatus::GameOver) {
			RestartGame();
			showMessage("���� ����� ���� ���� �����Ǿ����ϴ�.\n�ٽ� �����غ�����.");
			return true;
		}

		boardStatusChecker->set(REFRESH_TIME);
		boardStatusChecker->start();

		return true;
		});

	boardStatusChecker->start();
}

void Stage::EnterNextStage() {
	// �������� ������ �����Ѵ�.
	stageNum++;

	// ������ ���������� Ŭ������ ��� ���������� �̺�Ʈ �ڵ鷯�� ���߰� ���� ������� �����Ѵ�
	if (stageNum == NUM_OF_STAGE_TO_BE_CLEARED) {
		boardStatusChecker->stop();
		EnterEnding();
	}

	// ���������� ���� ��� ���� ���������� �����Ѵ�
	else {
		ShowScript(stageNum);

		// ���� ����ã�� ������ ����� �����Ѵ�.
		switch (stageNum) {
		case 0:
			boardBackground->setImage(BoardResource::BACKGROUND1);
			break;
		case 1:
			boardBackground->setImage(BoardResource::BACKGROUND2);
			break;
		case 2:
			boardBackground->setImage(BoardResource::BACKGROUND3);
			break;
		default:
			break;
		}

		// ���� ����ã�� ����� �����Ѵ�.
		board->RefreshBoard(board->getRow() + 2, board->getCol() + 4);
	}
}

void Stage::RestartGame() {
	board->Clear();
	board->InitItem(INIT_LIFE_COUNT);
	title->enter();
}

