/*
* Item.h
*
* ����ã�� ���ӿ��� �������� �����ϴ� Ŭ����.
* �������� ����, �������� ����, ����� ����, ���� ������� ������, �����۹� ��ü ���� �� Ŭ�������� �����Ѵ�.
* ���� ������� �������� ���������� �� Ŭ�����κ��� �ٸ� Ŭ������� ���޵ȴ�.
*/

#pragma once

#include <iostream>
#include <vector>
#include "resource.h"
#include "Cell.h"
#include "MineField.h"
#include <bangtal>

// ���Ѱ��� ������ ���� ����
constexpr auto INFINITE = -1;
// ����� ������ �ִ��� ���� ����
constexpr auto MAX_LIFE_COUNT = 19;

using namespace bangtal;

/*
* ������ â���� ���ð����� �׸��
*/
enum class Hand {
	//���
	Pickax,
	//���
	Flag,
	//���� Ž����
	Detector,
	//�������� (���Ϳ��� ������ 1�� ȸ��)
	Spray,
	
	None,
};

class Item {
private:
	// ���� �÷��̵ǰ� �ִ� ���
	ScenePtr background;

	// ���� �ڵ� ��Ȳ
	Hand currentHand = Hand::Pickax;

	// �����۹� ��Ż ������Ʈ
	ObjectPtr itemBar;

	// ������ ������Ʈ ����
	std::vector<ObjectPtr> itemObject;

	// �� �������� ������ Ȯ���ϱ� ���� �迭
	std::vector<int> itemCount;

	// �� �������� ������ ȭ�鿡 ǥ���ϱ� ���� ��Ż ������Ʈ �迭
	std::vector<ObjectPtr> itemCountOnject;

	// ���� ������� �������� ǥ������ �׵θ� ��Ż������Ʈ
	ObjectPtr currentItemIndicator;

	// ��� �̹��� ������Ʈ ����
	// �� ������ ũ�Ⱑ �� ����� �����̴�. 
	std::vector<ObjectPtr> lifeObject;

	// �������� ��� �� �ε�������
	ObjectPtr sprayUsedIndicator;
	bool isSprayUsed = false;

	// ������ ���Ұ� ����
	bool& isGameMute;

	/*
	* �ش� �������� itemCount ���� ���� Item���� �̹����� �����ϴ� �Լ�
	*/
	void refreshCountImage(int itemIndex);

	/*
	* Hand�� �ش��ϴ� ������ index�� ��ȯ�ϴ� �Լ�
	*/
	int getItemIndex(Hand hand);

public:
	Item(ScenePtr bg, int initLifeCount, bool& isGameMute);

	/*
	* ���� �ڵ带 Ȯ���ϴ� �Լ�
	*/ 
	Hand getCurrentHand();

	/*
	* Hand�� �ٲٴ� �Լ���
	*/ 
	void ChangeHandByIndex(int index);
	void ChangeHand(Hand hand);

	/*
	* detector �������� ������ ���·� ���� Ŭ���� ��츦 ó���� �Լ�
	*/
	void UseDetector(int clickedCellRow, int clickedCellCol, std::vector<std::vector<CellPtr>>& cells, MineField& field);

	/*
	* spray �������� ������ �ÿ� ȣ��� �Լ�
	*/
	void SelectSpray();

	/*
	* spray �������� ����� �� ȣ��Ǵ� �Լ�
	*/
	void UseSpray();

	/*
	* spray �������� ��������� ���θ� ��ȯ�ϴ� �Լ�
	*/
	bool getIsSprayUsed();

	/*
	* ���� �������� ������ Ȯ���ϴ� �Լ�
	*/ 
	int getItemCount(Hand hand);

	/*
	* �������� ������ ���̴� �Լ�
	*/ 
	void ReduceItem(Hand hand);

	/*
	* �������� ������ �ø��� �Լ�
	*/ 
	void AddItem(ItemValue itemValue);

	/*
	* ����� ������ �ϳ� ���̴� �Լ�
	*/
	void ReduceLifeCount();

	/*
	* ����� �ϳ� �߰��ϴ� �Լ�
	*/
	void AddLifeCount();

	/*
	* ��� ������ ��ȯ�ϴ� �Լ�
	*/
	int getLifeCount();
};