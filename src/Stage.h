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

// �������� ����
constexpr auto NUM_OF_STAGE_TO_BE_CLEARED = 3;

// ���� �ʱ� ũ��
constexpr auto STAGE1_ROW = 10, STAGE1_COL = 10;

// �ʱ� ��� ����
constexpr auto INIT_LIFE_COUNT = 3;


class Stage {
private:
	// ���� Ÿ��Ʋ
	ScenePtr titleBackground;

	// �������� �� ��ũ��Ʈ�� ���̱� ���� ��Ż ���
	ScenePtr scriptBackground;

	// �������� �� ��ũ��Ʈ
	ObjectPtr script;

	// ��ũ��Ʈ ȭ���� �ѱ�� ��ư
	ObjectPtr nextButton;

	// ���Ұ� ��ư�� ���Ұ� ���� ����
	ObjectPtr muteButton;
	bool isMusicMute;

	// �� ����� �������
	SoundPtr titleMusic;
	SoundPtr scriptMusic;
	SoundPtr boardMusic;
	SoundPtr endingMusic;

	/*
	** Background **
	*/
	// ����ã�� ������ ����Ǵ� ��Ż ���
	ScenePtr boardBackground;

	// Ż���ϱ� ��ư�� ��Ÿ���� ��Ż ������Ʈ
	ObjectPtr escapeButton;

	// ����ã�� ����
	Board* board;

	// Ŭ������ ���������� ����
	int stageNum = 0;

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
	void StartGame();

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
