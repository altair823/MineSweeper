#include "Stage.h"

Stage::Stage(ScenePtr ch, Status stat) {
	// ���������� ���� ȭ��� ���� ȭ���� ������
	// ch.����ȭ��
	// ���콺 �ݹ� -> ch.���ȭ��
	// ����� ch.���ȭ������ ����� �� ���δ�.
	// ���尡 �ʱ�ȭ�Ǹ� �������� ���� ��Ȳ�� Playing���� �ʱ�ȭ�ȴ�.
}

void Stage::EventHandler() {
	// Playing -> �̺�Ʈ ����
	// GameOver -> ���� �ʱ�ȭ
	// Claer -> ���� ��������
}

void Stage::setChapterStatus() {
	// �������� ���� ���� ����
	// ���� ����, �ʱ�ȭ -> Playing
	// ���� ���� ���� (����� ���� ���, ���ڸ� ���� ��� -> ���� ���� �ʳ�?) -> GameOver
	// ���� Ŭ���� ���� (���ڸ� ������ ��� ĭ�� ���� ����� ���� ���) -> Clear 
}

void Stage::getChapterStatus() {
	// �������� ���� ���� Ȯ��
}

void Stage::RestartStage() {
	// �� �ʱ�ȭ -> ���� �ʱ�ȭ
}

void Stage::NextStage() {
	// �� ���� -> �� ����? ��� ������ �ٲٰ� ���� �ʱ�ȭ? (���ڰ� ���� ��)
}

