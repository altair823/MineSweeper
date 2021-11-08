#include "Stage.h"

Stage::Stage(ScenePtr ch, Status stat) {
	// 스테이지는 시작 화면과 게임 화면을 가진다
	// ch.시작화면
	// 마우스 콜백 -> ch.배경화면
	// 보드는 ch.배경화면으로 변경될 때 보인다.
	// 보드가 초기화되면 스테이지 진행 상황은 Playing으로 초기화된다.
}

void Stage::EventHandler() {
	// Playing -> 이벤트 없음
	// GameOver -> 보드 초기화
	// Claer -> 다음 스테이지
}

void Stage::setChapterStatus() {
	// 스테이지 진행 상태 변경
	// 보드 생성, 초기화 -> Playing
	// 게임 오버 조건 (목숨이 다한 경우, 지뢰를 밟은 경우 -> 차이 없지 않나?) -> GameOver
	// 게임 클리어 조건 (지뢰를 제외한 모든 칸을 열고 목숨이 남은 경우) -> Clear 
}

void Stage::getChapterStatus() {
	// 스테이지 진행 상태 확인
}

void Stage::RestartStage() {
	// 씬 초기화 -> 보드 초기화
}

void Stage::NextStage() {
	// 씬 변경 -> 씬 생성? 배경 사진만 바꾸고 보드 초기화? (후자가 나은 듯)
}

