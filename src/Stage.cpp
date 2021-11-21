#include "Stage.h"

Stage::Stage() : isMusicMute(false), stageNum(0) {
	// Board의 Scene
	boardBackground = Scene::create("보드 배경", BoardResource::BACKGROUND1);
	board = new Board(boardBackground, INIT_LIFE_COUNT);
}

void Stage::StartGame() {
	// 타이틀 화면 및 타이틀 화면이 가지는 방탈 오브젝트 생성
	titleBackground = Scene::create("타이틀", TitleResource::TITLE);

	// 게임 시작 버튼
	ObjectPtr startButton = Object::create(TitleResource::START_BUTTON, titleBackground, 480, 100);
	startButton->setOnMouseCallback([&](auto object, int x, int y, auto action)->bool {
		// 맨 첫 스크립트 출력
		ShowScript(0);
		titleMusic->stop();

		scriptBackground->enter();
		return true;
		});

	// 게임 방법 버튼
	ObjectPtr howToPlayButton = Object::create(EndingResource::END_BUTTON, titleBackground, 480, 10);
	howToPlayButton->setOnMouseCallback([&](auto object, int x, int y, auto action)->bool {
		/*
		* 
		* TODO 도움말 이미지 삽입
		* 
		*/
		return true;
		});

	titleMusic = Sound::create(TitleResource::TITLE_MUSIC);
	CreateMuteButton(titleBackground, titleMusic);
	startGame(titleBackground);
}

void Stage::ShowScript(int stageNum) {
	// 스테이지 별 스크립트 배경과 배경음악 생성
	switch (stageNum) {
	case 0:
		scriptBackground = Scene::create("스크립트 배경", ScriptResource::SCRIPT_BACKGROUND_1);
		script = Object::create(ScriptResource::SCRIPT_IMAGE_1, scriptBackground, 480, 200);
		scriptMusic = Sound::create(ScriptResource::SCRIPT_MUSIC_1);
		break;
	case 1:
		scriptBackground = Scene::create("스크립트 배경", ScriptResource::SCRIPT_BACKGROUND_2);
		script = Object::create(ScriptResource::SCRIPT_IMAGE_2, scriptBackground, 480, 200);
		scriptMusic = Sound::create(ScriptResource::SCRIPT_MUSIC_2);
		break;
	case 2:
		scriptBackground = Scene::create("스크립트 배경", ScriptResource::SCRIPT_BACKGROUND_3);
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
		* TODO 스크립트가 여러장일 경우 여기서 넘길 것. 
		* 
		*/

		// 맨 처음일 경우 보드를 새로 생성
		if (stageNum == 0) {
			CreateBoard();
		}
		scriptMusic->stop();
		// 배경음악을 갱신한다. 
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
		// 뮤트 버튼 생성
		CreateMuteButton(boardBackground, boardMusic);
		boardBackground->enter();
		return true;
		});

	CreateMuteButton(scriptBackground, scriptMusic);

	scriptBackground->enter();
}

void Stage::CreateBoard() {
	board->GenerateNewBoard(STAGE1_ROW, STAGE1_COL, stageNum);

	// 탈출하기 선택지
	// 탈출구를 발견하면 보이게 한다. 
	escapeButton = Object::create(BoardResource::ESCAPE_BUTTON, boardBackground, 0, 690, false);
	escapeButton->setOnMouseCallback([&](auto object, int x, int y, auto action)->bool {
		board->setBoardStatus(BoardStatus::Clear);
		return true;
		});


	// 보드의 상태를 처리할 핸들러 루프 시작
	StartStatusHandler();
}

void Stage::EnterEnding() {
	// 엔딩 화면을 보이기 위한 방탈 장면
	ending = Scene::create("엔딩 배경", EndingResource::ENDING);

	// 엔딩 화면에 표시되는 스크립트
	endingScript = Object::create(EndingResource::END_BUTTON, ending, 480, 10);
	endingScript->setOnMouseCallback([&](auto object, int x, int y, auto action)->bool {
		endGame();
		return true;
		});

	endingMusic = Sound::create(EndingResource::HAPPY_END_MUSIC);

	ending->enter();
}

void Stage::StartStatusHandler() {
	// 타이머가 돌면서 board의 status를 체크한다.
	boardStatusChecker = Timer::create(REFRESH_TIME);
	boardStatusChecker->setOnTimerCallback([&](auto)->bool {
		// Escape -> 탈출하기 버튼 보이기
		if (board->getBoardStatus() == BoardStatus::Escape) {
			// 바로 탈출하지 않는 경우를 위해 보드 상태를 변경
			board->setBoardStatus(BoardStatus::Playing);
			escapeButton->show();
			showMessage("탈출구를 찾았습니다! 스테이지를 벗어나고 싶으면 탈출하기 버튼을 누르세요.\n지금 탈출하지 않고 남아있는 아이템을 획득하기 위해 게임을 계속 진행할 수 있습니다.");
		}

		// Claer -> 다음 스테이지로 이동
		if (board->getBoardStatus() == BoardStatus::Clear) {
			escapeButton->hide();
			boardMusic->stop();
			EnterNextStage();
		}

		// GameOver -> 재시작
		if (board->getBoardStatus() == BoardStatus::GameOver) {
			RestartGame();
			boardMusic->stop();
			showMessage("남은 목숨이 없어 게임 오버되었습니다.\n다시 도전해보세요.");
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

	// 스테이지 레벨을 갱신한다.
	stageNum++;

	// 마지막 스테이지를 클리어한 경우 스테이지의 이벤트 핸들러를 멈추고 엔딩 장면으로 진입한다
	if (stageNum >= NUM_OF_STAGE_TO_BE_CLEARED) {
		boardStatusChecker->stop();
		boardMusic->stop();
		EnterEnding();
	}

	// 스테이지가 남은 경우 다음 스테이지로 진입한다
	else {
		ShowScript(stageNum);

		// 다음 지뢰찾기 보드의 배경을 갱신한다.
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

		// 다음 지뢰찾기 보드로 갱신한다.
		board->RefreshBoard(board->getRow() + 2, board->getCol() + 4, stageNum);
	}
}

void Stage::CreateMuteButton(ScenePtr background, SoundPtr music) {

	// 음소거 여부 유지
	if (isMusicMute) {
		muteButton = Object::create(BoardResource::UNMUTE_BUTTON, background, 20, 630);
	}
	else {
		muteButton = Object::create(BoardResource::MUTE_BUTTON, background, 20, 630);
		music->play(true);
	}
	muteButton->setOnMouseCallback([=](auto, auto, auto, auto)->bool {
		// 음소거 상태였다면
		if (isMusicMute) {
			isMusicMute = false;
			music->play(true);
			muteButton->setImage(BoardResource::MUTE_BUTTON);
		}
		// 소리가 나는 상태였다면
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

