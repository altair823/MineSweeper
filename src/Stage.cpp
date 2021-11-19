#include "Stage.h"

Stage::Stage() {
	// 게임에 필요한 방탈 장면들을 생성한다.
	setTitle();
	setScriptBackground();
	setBackground();
	setEnding();

	// 스테이지의 이벤트 핸들러가 동작한다.
	EventHandler();
}

void Stage::setTitle() {
	// 타이틀 화면 및 타이틀 화면이 가지는 방탈 오브젝트 생성
	title = Scene::create("타이틀 화면", TitleResource::Title);

	// 게임 시작 버튼
	startButton = Object::create(TitleResource::StartButton, title, 480, 100);
	startButton->setOnMouseCallback([&](auto object, int x, int y, auto action)->bool {
		scriptBackground->enter();
		return true;
		});

	// 게임 방법 버튼
	howToPlayButton = Object::create(EndingResource::endButton, title, 480, 10);
	howToPlayButton->setOnMouseCallback([&](auto object, int x, int y, auto action)->bool {
		// ** 디버그용 **
		endGame();
		return true;
		});
}

void Stage::setScriptBackground() {
	// 게임 타이틀 및 스테이지 별 스크립트를 보이기 위한 방탈 장면
	// ** 코드 변경으로 스테이지 1 시작 이전 scriptBackground의 배경이 stage 1 clear가 표시된 테스트 이미지로 설정 됨 **
	scriptBackground = Scene::create("시작 화면", scriptBackgroundImage[clearedStageCount]);

	// scriptbackground에서 보여줄 스테이지 별 스크립트
	// scriptbackground가 보여줄 스크립트가 끝나면 background 장면으로 들어간다.
	script = Object::create(scriptImage[clearedStageCount], scriptBackground, 480, 10);
	script->setOnMouseCallback([&](auto object, int x, int y, auto action)->bool {
		// ~ 정해진 개수의 스트립트를 보이기 위해 이미지를 변경하는 코드가 필요할 수도 있음 ~
		background->enter();
		return true;
		});
}

void Stage::setBackground() {
	// 게임이 실행되는 방탈 장면
	background = Scene::create("배경", backgroundImage[clearedStageCount]);

	// 지뢰찾기 보드 생성
	board = new Board(background);
	board->GenerateNewBoard(INIT_BOARD_SIZE, INIT_BOARD_SIZE);

	// background에서 보여줄 탈출하기 버튼
	// 주어진 조건을 만족할 때만 보이기 위해 숨긴다.
	escapeButton = Object::create(CellResource::EMPTY, background, 0, 690);
	escapeButton->setOnMouseCallback([&](auto object, int x, int y, auto action)->bool {
		board->setBoardStatus(BoardStatus::Clear);
		escapeButton->hide();
		return true;
		});
	escapeButton->hide();
}

void Stage::setEnding() {
	// 엔딩 화면을 보이기 위한 방탈 장면
	ending = Scene::create("엔딩", EndingResource::Ending);

	// 엔딩 화면에 표시되는 스크립트
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
	// 타이머가 돌면서 board의 status를 체크한다.
	boardStatusChecker = Timer::create(REFRESH_TIME);
	boardStatusChecker->setOnTimerCallback([&](auto)->bool {
		// Playing -> 이벤트 없음

		// Escape -> 탈출하기 버튼 보이기
		if (board->getBoardStatus() == BoardStatus::Escape) {
			// 바로 탈출하지 않는 경우를 위해 보드 상태를 변경
			board->setBoardStatus(BoardStatus::Playing);
			escapeButton->show();
			showMessage("탈출구를 찾았습니다! 스테이지를 벗어나고 싶으면 탈출하기 버튼을 누르세요.\n지금 탈출하지 않고 남아있는 아이템을 획득하기 위해 게임을 계속 진행할 수 있습니다.");
		}

		// Claer -> 다음 스테이지
		if (board->getBoardStatus() == BoardStatus::Clear) {
			escapeButton->hide();
			NextStage();
		}

		// GameOver -> 보드 초기화?
		if (board->getBoardStatus() == BoardStatus::GameOver) {
			title->enter();
			showMessage("남은 목숨이 없어 게임 오버되었습니다.\n다시 도전해보세요.");
		}

		boardStatusChecker->set(REFRESH_TIME);
		boardStatusChecker->start();

		return true;
		});

	boardStatusChecker->start();
}

void Stage::NextStage() {
	// 스테이지 레벨을 갱신한다.
	clearedStageCount++;

	// 클리어 해야하는 스테이지 개수에 도달한 경우 스테이지의 이벤트 핸들러를 멈추고 엔딩 장면으로 진입한다
	if (clearedStageCount >= NUM_OF_STAGE_TO_BE_CLEARED) {
		boardStatusChecker->stop();
		ending->enter();
	}

	// 클리어 해야하는 스테이지 개수가 남은 경우 다음 스테이지로 진입한다
	else {
		// 스테이지 클리어 시 보여줄 스크립트를 갱신한다.
		scriptBackground->setImage(scriptBackgroundImage[clearedStageCount]);
		script->setImage(scriptImage[clearedStageCount]);

		// 스크립트를 가지고 있는 scriptBackground 장면으로 입장한다.
		scriptBackground->enter();

		// 다음 지뢰찾기 보드의 배경을 갱신한다.
		background->setImage(backgroundImage[clearedStageCount]);

		// 다음 지뢰찾기 보드로 갱신한다.
		int row = board->getRow();
		int col = board->getCol();
		board->RefreshBoard(row + 2, col + 4);
	}
}

