#pragma once

/*
*
*
*/

#pragma once

#include <iostream>
#include <string>
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

	// frontground�� �������� �� �̹����� �����ϰ� �ִ� ����
	std::vector<std::string> frontgroundImage = {StageResource::FG_IMAGE_0, StageResource::FG_IMAGE_1, StageResource::FG_IMAGE_2, StageResource::FG_IMAGE_3};

	// ���� Ÿ��Ʋ �� �������� �� ��ũ��Ʈ�� ��Ÿ���� ��Ż ������Ʈ
	ObjectPtr script;

	// script�� �������� �� �̹����� �����ϰ� �ִ� ����
	std::vector<std::string> scriptImage = { StageResource::SCRIPT_IMAGE_0, StageResource::SCRIPT_IMAGE_1, StageResource::SCRIPT_IMAGE_2, StageResource::SCRIPT_IMAGE_3 };

	// Ż���ϱ� ��ư�� ��Ÿ���� ��Ż ������Ʈ
	ObjectPtr escapeButton;
	
	// ����ã�� ����
	Board* board;

	// ���� �������� ����
	int currentStageLevel = 0;

	// ���� ���� ��Ȳ�� üũ�� Ÿ�̸�
	TimerPtr boardStatusChecker;

public:
	Stage();

	// ���� ����� ��ȯ�ϴ� �Լ�
	ScenePtr getFrontground();

	// ���� ���� ��Ȳ ����� ������ �̺�Ʈ�� �߻��ϴ� �Լ�
	void EventHandler();

	// ���� Ŭ���� �� ���� ���������� �Ѿ�� �Լ�
	void NextStage();
};
