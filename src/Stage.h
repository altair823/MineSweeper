#pragma once

/*
*
*
*/

#pragma once

#include <iostream>
#include <bangtal>
#include "Board.h"

using namespace bangtal;

// �������� ����
constexpr auto STAGE_COUNT = 3;

class Stage {
private:
	// ����ã�� ������ ����Ǵ� ��Ż ���
	ScenePtr background;

	// ���� Ÿ��Ʋ �� �������� �� ��ũ��Ʈ�� ���̱� ���� ��Ż ���
	ScenePtr frontground;

	// ���� Ÿ��Ʋ �� �������� �� ��ũ��Ʈ�� ��Ÿ���� ��Ż ������Ʈ
	ObjectPtr script;
	
	// ����ã�� ����
	Board* board;

	// ���� �������� ����
	int currentStageLevel = 0;

	// ���� ���� ��Ȳ�� üũ�� Ÿ�̸�
	TimerPtr boardStatusChecker;

public:
	Stage(ScenePtr background, ScenePtr frontground);

	// ���� ���� ��Ȳ ����� ������ �̺�Ʈ�� �߻��ϴ� �Լ�
	void EventHandler();

	// ���� Ŭ���� �� ���� ���������� �Ѿ�� �Լ�
	void NextStage();
};
