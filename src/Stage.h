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
#include "GameGuide.h"

#define DEBUG

using namespace bangtal;

// �������� ����
constexpr auto NUM_OF_STAGE_TO_BE_CLEARED = 3;

// ���� �ʱ� ũ��
constexpr auto STAGE1_ROW = 10, STAGE1_COL = 10;

// �ʱ� ��� ����
constexpr auto INIT_LIFE_COUNT = 3;

// ���� ������ �����ϱ� ���� �ִ� ���� Ƚ��
constexpr auto COMBAT_COUNT_FOR_HAPPY_ENDING = 8;


class Stage {
private:

	// �� ȭ���� ���� ���
	ScenePtr titleBackground;
	ScenePtr scriptBackground;
	ScenePtr boardBackground;
	ScenePtr endingBackground;

	// ���� ������ �����ִ� ���̵� Ŭ���� ��ü
 	std::shared_ptr<GameGuide> gameGuide;

	// �������� �� ��ũ��Ʈ
	ObjectPtr script;

	// ��ũ��Ʈ ȭ���� �ѱ�� ��ư
	ObjectPtr nextButton;

	// ���Ұ� ��ư�� ���Ұ� ���� ����
	ObjectPtr muteButton;
	bool isGameMute;

	// �� ����� �������
	SoundPtr titleMusic;
	SoundPtr scriptMusic;
	SoundPtr boardMusic;
	SoundPtr endingMusic;

	// Ż���ϱ� ��ư
	ObjectPtr escapeButton;

	// ����ã�� ����
	std::shared_ptr<Board> board;

	// Ŭ������ ���������� ����
	int stageNum = 0;

	// ���� ���� ��Ȳ�� üũ�� Ÿ�̸�
	TimerPtr boardStatusChecker;

	// �������� ������ ��ư
	ObjectPtr goToTitleButton;
	ObjectPtr gameEndButton;

public:
	Stage();

	void StartGame();

	// tile ���� title ����� ������ ��Ż ������Ʈ���� �ʱ�ȭ�ϴ� �Լ�
	void MakeTitle();

	// scriptBackground ���� scriptBackground ����� ������ ��Ż ������Ʈ���� �ʱ�ȭ�ϴ� �Լ�
	void ShowScript(int stageNum);

	// background ���� background ����� ������ ��Ż ������Ʈ���� �ʱ�ȭ�ϴ� �Լ�
	void CreateBoard();

	// ending ���� ending ����� ������ ��Ż ������Ʈ���� �ʱ�ȭ�ϴ� �Լ�
	void EnterEnding();

	// ���� ���� ��Ȳ ����� ������ �̺�Ʈ�� �߻��ϴ� �Լ�
	void StartStatusHandler();

	// ���� Ŭ���� �� ���� ���������� �Ѿ�� �Լ�
	void EnterNextStage();

	/*
	* ���Ұ� ��ư�� �����ϴ� �Լ�
	*/
	void CreateMuteButton(ScenePtr background, SoundPtr music);

	/*
	* ������ ������ϴ� �Լ�
	*/
	void RestartGame();
};
