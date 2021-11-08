#pragma once

/*
*
*
*/

#pragma once

#include <iostream>
#include <bangtal>
#include "CommonDeclarations.h"
#include "Board.h"

using namespace bangtal;

class Stage {
private:
	ScenePtr chapter;
	//Board board;

public:
	Stage(ScenePtr ch, Status stat);

	// �������� ���� ��Ȳ ����� ������ �̺�Ʈ�� �߻��ϴ� �Լ�
	void EventHandler(); // �̺�Ʈ�� ��𿡼� �߻�����?( ���� �̺�Ʈ ������ �����ϳ�?)

	// �������� ���� ��Ȳ�� �����ϴ� �Լ�
	void setChapterStatus();

	// �������� ���� ��Ȳ�� Ȯ���ϴ� �Լ�
	void getChapterStatus();

	// ���� ���� �� �ش� ���������� �ٽ� �����ϴ� �Լ�
	void RestartStage();

	// �������� Ŭ���� �� ���� ���������� �Ѿ�� �Լ�
	void NextStage();
};
