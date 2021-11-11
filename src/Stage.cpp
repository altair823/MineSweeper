#include "Stage.h"

Stage::Stage(ScenePtr bg, ScenePtr fg) {
	background = bg;
	frontground = fg;

	// 지뢰찾기 보드 생성
	board = new Board(background);
	board->GenerateNewBoard(INIT_BOARD_SIZE, INIT_BOARD_SIZE);

	// frontground에서 보여줄 게임 타이틀 및 스테이지 별 스크립트
	// frontground가 보여줄 스크립트가 끝나면 backround로 입장한다.
	script = Object::create(CombatResource::MONSTER1, frontground, 0, 0);
	script->setOnMouseCallback([&](auto object, int x, int y, auto action)->bool {
		background->enter();
		return true;
	});

	// 스테이지의 이벤트 핸들러가 동작한다.
	EventHandler();
}

void Stage::EventHandler() {
	// 타이머가 돌면서 board의 status를 체크한다.
	boardStatusChecker = Timer::create(REFRESH_TIME);
	boardStatusChecker->setOnTimerCallback([&](auto)->bool {
		// Playing -> 이벤트 없음
		// Claer -> 다음 스테이지
		if (board->getBoardStatus() == Status::Clear) {
			NextStage();
		}
		// GameOver -> 보드 초기화?
		if (board->getBoardStatus() == Status::GameOver) {
			// ** 디버그용 ** 게임 종료
			endGame();
		}
		boardStatusChecker->set(REFRESH_TIME);
		boardStatusChecker->start();
		return true;
		});

	boardStatusChecker->start();

	// 디버그용 타이머 생성 메세지
	std::cout << ". . . Now Board Status Checker is working . . ." << std::endl;
}

void Stage::NextStage() {
	// 다음 스테이지로 넘어갈 때 보여줄 스크립트를 갱신한다.
	// script->setImage();

	// 스크립트를 가지고 있는 front 장면으로 입장한다.
	frontground->enter();

	// 스테이지 레벨을 갱신한다.
	currentStageLevel++;

	// 다음 지뢰찾기 보드로 갱신한다.
	int row = board->getRow();
	int col = board->getCol();
	board->RefreshBoard(row + 2, col + 4);
}

