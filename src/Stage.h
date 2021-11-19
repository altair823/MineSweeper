/*
* Stage
*
* ������ �����ϰ� �������� ������ ����ϴ� Ŭ����
* 
* Ÿ��Ʋ, ��ũ��Ʈ, ��׶���, ���� ����� ������
* ������ ���� ��Ȳ�� ������ ������ ����� �����ϰ� �����ϰ�
* ���ǿ� �´� ������� �����Ѵ�.
*/

#pragma once

#include <iostream>
#include <string>
#include <bangtal>
#include "Board.h"

using namespace bangtal;

// ������ ���� Ŭ�����ؾ� �ϴ� �������� ����
constexpr auto NUM_OF_STAGE_TO_BE_CLEARED = 3;

class Stage {
private:
	/*
	** Title **
	*/
	// ���� Ÿ��Ʋ
	ScenePtr title;

	// ���� ���� ��ư�� ���� ��Ż ������Ʈ
	ObjectPtr startButton;

	// ���� ��� ��ư�� ���� ��Ż ������Ʈ
	ObjectPtr howToPlayButton;

	/*
	** Script **
	*/
	// �������� �� ��ũ��Ʈ�� ���̱� ���� ��Ż ���
	ScenePtr scriptBackground;

	// scriptBackground�� �������� �� �̹����� �����ϰ� �ִ� ����
	std::vector<std::string> scriptBackgroundImage = { StageResource::SCRIPT_BACKGROUND_1, StageResource::SCRIPT_BACKGROUND_2, StageResource::SCRIPT_BACKGROUND_3 };

	// �������� �� ��ũ��Ʈ�� ��Ÿ���� ��Ż ������Ʈ
	ObjectPtr script;

	// script�� �������� �� �̹����� �����ϰ� �ִ� ����
	std::vector<std::string> scriptImage = { StageResource::SCRIPT_IMAGE_1, StageResource::SCRIPT_IMAGE_2, StageResource::SCRIPT_IMAGE_3 };

	/*
	** Background **
	*/
	// ����ã�� ������ ����Ǵ� ��Ż ���
	ScenePtr background;

	// background�� �������� �� �̹����� �����ϰ� �ִ� ����
	std::vector<std::string> backgroundImage = { BoardResource::BACKGROUND1, BoardResource::BACKGROUND2, BoardResource::BACKGROUND3 };

	// Ż���ϱ� ��ư�� ��Ÿ���� ��Ż ������Ʈ
	ObjectPtr escapeButton;

	// ����ã�� ����
	Board* board;

	// Ŭ������ ���������� ����
	int clearedStageCount = 0;

	// ���� ���� ��Ȳ�� üũ�� Ÿ�̸�
	TimerPtr boardStatusChecker;

	/*
	** Ending **
	*/
	// ���� ȭ���� ���̱� ���� ��Ż ���
	ScenePtr ending;

	// ���� ��Ʈ��Ʈ�� ���� ��Ż ������Ʈ
	ObjectPtr endingScript;

public:
	Stage();

	// tile ���� title ����� ������ ��Ż ������Ʈ���� �ʱ�ȭ�ϴ� �Լ�
	void setTitle();

	// scriptBackground ���� scriptBackground ����� ������ ��Ż ������Ʈ���� �ʱ�ȭ�ϴ� �Լ�
	void setScriptBackground();

	// background ���� background ����� ������ ��Ż ������Ʈ���� �ʱ�ȭ�ϴ� �Լ�
	void setBackground();

	// ending ���� ending ����� ������ ��Ż ������Ʈ���� �ʱ�ȭ�ϴ� �Լ�
	void setEnding();

	// ���� Ÿ��Ʋ�� ��ȯ�ϴ� �Լ�
	ScenePtr getTitle();

	// ���� ���� ��Ȳ ����� ������ �̺�Ʈ�� �߻��ϴ� �Լ�
	void EventHandler();

	// ���� Ŭ���� �� ���� ���������� �Ѿ�� �Լ�
	void NextStage();
};
