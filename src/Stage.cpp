#include "Stage.h"

Stage::Stage() : isMusicMute(false), stageNum(0) {
	// Board�� Scene
	boardBackground = Scene::create("���� ���", BoardResource::BACKGROUND1);
	board = new Board(boardBackground, INIT_LIFE_COUNT);
}

void Stage::StartGame() {
	// Ÿ��Ʋ ȭ�� �� Ÿ��Ʋ ȭ���� ������ ��Ż ������Ʈ ����
	titleBackground = Scene::create("Ÿ��Ʋ", TitleResource::TITLE);

	// ���� ���� ��ư
	ObjectPtr startButton = Object::create(TitleResource::START_BUTTON, titleBackground, 480, 100);
	startButton->setOnMouseCallback([&](auto object, int x, int y, auto action)->bool {
		// �� ù ��ũ��Ʈ ���
		ShowScript(0);
		titleMusic->stop();

		scriptBackground->enter();
		return true;
		});

	// ���� ��� ��ư
	ObjectPtr howToPlayButton = Object::create(EndingResource::END_BUTTON, titleBackground, 480, 10);
	howToPlayButton->setOnMouseCallback([&](auto object, int x, int y, auto action)->bool {
		/*
		* 
		* TODO ���� �̹��� ����
		* 
		*/
		return true;
		});

	titleMusic = Sound::create(TitleResource::TITLE_MUSIC);
	CreateMuteButton(titleBackground, titleMusic);
	startGame(titleBackground);
}

void Stage::ShowScript(int stageNum) {
	// �������� �� ��ũ��Ʈ ���� ������� ����
	switch (stageNum) {
	case 0:
		scriptBackground = Scene::create("��ũ��Ʈ ���", ScriptResource::SCRIPT_BACKGROUND_1);
		script = Object::create(ScriptResource::SCRIPT_IMAGE_1, scriptBackground, 480, 200);
		scriptMusic = Sound::create(ScriptResource::SCRIPT_MUSIC_1);
		break;
	case 1:
		scriptBackground = Scene::create("��ũ��Ʈ ���", ScriptResource::SCRIPT_BACKGROUND_2);
		script = Object::create(ScriptResource::SCRIPT_IMAGE_2, scriptBackground, 480, 200);
		scriptMusic = Sound::create(ScriptResource::SCRIPT_MUSIC_2);
		break;
	case 2:
		scriptBackground = Scene::create("��ũ��Ʈ ���", ScriptResource::SCRIPT_BACKGROUND_3);
		script = Object::create(ScriptResource::SCRIPT_IMAGE_3, scriptBackground, 480, 200);
		scriptMusic = Sound::create(ScriptResource::SCRIPT_MUSIC_3);
		break;
	default:
		break;
	}

	nextButton = Object::create(ScriptResource::SCRIPT_IMAGE_1, scriptBackground, 480, 10);
	nextButton->setOnMouseCallback([=](auto object, int x, int y, auto action)->bool {
		/*
		* 
		* TODO ��ũ��Ʈ�� �������� ��� ���⼭ �ѱ� ��. 
		* 
		*/

		// �� ó���� ��� ���带 ���� ����
		if (stageNum == 0) {
			CreateBoard();
		}
		scriptMusic->stop();
		// ��������� �����Ѵ�. 
		switch (stageNum) {
		case 0:
			boardMusic = Sound::create(BoardResource::BOARD_MUSIC_1);
			break;
		case 1:
			boardMusic = Sound::create(BoardResource::BOARD_MUSIC_2);
			break;
		case 2:
			boardMusic = Sound::create(BoardResource::BOARD_MUSIC_3);
			break;
		default:
			break;
		}
		// ��Ʈ ��ư ����
		CreateMuteButton(boardBackground, boardMusic);
		boardBackground->enter();
		return true;
		});

	CreateMuteButton(scriptBackground, scriptMusic);

	scriptBackground->enter();
}

void Stage::CreateBoard() {
	board->GenerateNewBoard(STAGE1_ROW, STAGE1_COL, stageNum);

	// Ż���ϱ� ������
	// Ż�ⱸ�� �߰��ϸ� ���̰� �Ѵ�. 
	escapeButton = Object::create(BoardResource::ESCAPE_BUTTON, boardBackground, 0, 690, false);
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

	endingMusic = Sound::create(EndingResource::HAPPY_END_MUSIC);

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
			boardMusic->stop();
			EnterNextStage();
		}

		// GameOver -> �����
		if (board->getBoardStatus() == BoardStatus::GameOver) {
			RestartGame();
			boardMusic->stop();
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
	boardMusic->stop();

	// �������� ������ �����Ѵ�.
	stageNum++;

	// ������ ���������� Ŭ������ ��� ���������� �̺�Ʈ �ڵ鷯�� ���߰� ���� ������� �����Ѵ�
	if (stageNum >= NUM_OF_STAGE_TO_BE_CLEARED) {
		boardStatusChecker->stop();
		boardMusic->stop();
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
		board->RefreshBoard(board->getRow() + 2, board->getCol() + 4, stageNum);
	}
}

void Stage::CreateMuteButton(ScenePtr background, SoundPtr music) {

	// ���Ұ� ���� ����
	if (isMusicMute) {
		muteButton = Object::create(BoardResource::UNMUTE_BUTTON, background, 20, 630);
	}
	else {
		muteButton = Object::create(BoardResource::MUTE_BUTTON, background, 20, 630);
		music->play(true);
	}
	muteButton->setOnMouseCallback([=](auto, auto, auto, auto)->bool {
		// ���Ұ� ���¿��ٸ�
		if (isMusicMute) {
			isMusicMute = false;
			music->play(true);
			muteButton->setImage(BoardResource::MUTE_BUTTON);
		}
		// �Ҹ��� ���� ���¿��ٸ�
		else {
			isMusicMute = true;
			music->stop();
			muteButton->setImage(BoardResource::UNMUTE_BUTTON);
		}
		return true;
		});

}

void Stage::RestartGame() {
	board->Clear();
	board->InitItem(INIT_LIFE_COUNT);
	titleBackground->enter();
}

