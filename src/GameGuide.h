/*
* GameGuide.h
* 
* ���ӿ� ���� ������ �Ұ��� 
* ������ �ϴ� ����� �����ϴ� ���̵� ȭ���� �����ϴ� Ŭ����
*/

#pragma once

#include <bangtal>
#include <vector>
#include "resource.h"

using namespace bangtal;

class GameGuide {
private:

	// ���̵��� ���
	ScenePtr guideBackground;

	// �ٽ� ���ư� ���
	ScenePtr previousBackground;

	// ���� ��濡������ ����� �������
	SoundPtr currentMusic;
	
	// ���Ұ� ��ư�� ���Ұ� ���θ� �����ϴ� ������
	ObjectPtr muteButton;
	bool& isGameMute;

	// ���̵� ������
	std::vector<ObjectPtr> guidePage;

	// ���� ���̴� �������� �ε���
	int currentPageIndex;

	// �������� �ѱ�� ���� ��ư��
	ObjectPtr nextButton;
	ObjectPtr previousButton;
	ObjectPtr closeButton;

public:
	GameGuide(ScenePtr previousBackground, SoundPtr currentMusic, bool& isGameMute);

	/*
	* ���̵带 ���� �Լ�
	*/
	void EnterGuide();

	/*
	* ���̵带 �ݴ� �Լ�
	*/
	void CloseGuide();

	/*
	* ���̵� ���������� �ʱ�ȭ�ϰ� �����ϴ� �Լ�
	*/
	void SetupPages();

	/*
	* ���̵� ��ư���� �ʱ�ȭ�ϰ� �����ϴ� �Լ�
	*/
	void SetupButtons();

	/*
	* ���Ұ� ��ư�� �����ϴ� �Լ�
	*/
	void CreateMuteButton(ScenePtr background, SoundPtr music);
};

