#include "Stage.h"

Stage::Stage() {
	// 게임 타이틀 및 스테이지 별 스크립트를 보이기 위한 방탈 장면
	frontground = Scene::create("시작 화면", frontgroundImage[currentStageLevel]);

	// 게임이 실행되는 방탈 장면
	background = Scene::create("배경", BoardResource::BACKGROUND);

	// 지뢰찾기 보드 생성
	board = new Board(background);
	board->GenerateNewBoard(INIT_BOARD_SIZE, INIT_BOARD_SIZE);

	// frontground에서 보여줄 게임 타이틀 및 스테이지 별 스크립트
	// frontground가 보여줄 스크립트가 끝나면 backround로 입장하거나 게임을 종료한다.
	script = Object::create(scriptImage[currentStageLevel], frontground, 480, 10);
	script->setOnMouseCallback([&](auto object, int x, int y, auto action)->bool {
		if (currentStageLevel == STAGE_COUNT) {
			endGame();
		}
		else {
			background->enter();
		}
		return true;
	});

	// background에서 보여줄 탈출하기 버튼
	// 주어진 조건을 만족할 때만 보이기 위해 숨긴다.
	escapeButton = Object::create(CellResource::EMPTY, background, 0, 690);
	escapeButton->setOnMouseCallback([&](auto object, int x, int y, auto action)->bool {
		board->setBoardStatus(BoardStatus::Clear);
		escapeButton->hide();
		return true;
		});
	escapeButton->hide();

	// 스테이지의 이벤트 핸들러가 동작한다.
	EventHandler();
}

ScenePtr Stage::getFrontground() {
	return frontground;
}

void Stage::EventHandler() {
	// 타이머가 돌면서 board의 status를 체크한다.
	boardStatusChecker = Timer::create(REFRESH_TIME);
	boardStatusChecker->setOnTimerCallback([&](auto)->bool {
		// Playing -> 이벤트 없음
		// Escape -> 탈출하기 버튼 보이기
		if (board->getBoardStatus() == BoardStatus::Escape) {
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
			// ** 디버그용 ** 게임 종료
			std::cout << "Game Over!";
			endGame();
		}
		boardStatusChecker->set(REFRESH_TIME);
		boardStatusChecker->start();
		return true;
		});

	boardStatusChecker->start();
}

void Stage::NextStage() {
	// 스테이지 레벨을 갱신한다.
	currentStageLevel++;

	// 스테이지 클리어 시 보여줄 스크립트를 갱신한다.
	frontground->setImage(frontgroundImage[currentStageLevel]);
	script->setImage(scriptImage[currentStageLevel]);

	// 스크립트를 가지고 있는 front 장면으로 입장한다.
	frontground->enter();

	// 다음 지뢰찾기 보드로 갱신한다.
	int row = board->getRow();
	int col = board->getCol();
	board->RefreshBoard(row + 2, col + 4);

	// 다음 지뢰찾기 보드의 배경을 갱신한다.
}

