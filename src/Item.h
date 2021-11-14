/*
* Item.h
*
* ����ã�� ���ӿ��� �������� �����ϴ� Ŭ����.
* �������� ����, �������� ����, ���� ������� ������, �����۹� ��ü ���� �� Ŭ�������� �����Ѵ�.
* ���� ������� �������� ���������� �� Ŭ�����κ��� �ٸ� Ŭ������� ���޵ȴ�.
* �������� 9ĭ�� ������ �����ִ� ������, 1���� ������ ȸ�ǽ����ִ� �������� �ִ�.
* �������� �ִ� ������ 3���� �Ѵ�.
*/

#pragma once

#include <iostream>
#include <vector>
#include "resource.h"
#include "MineField.h"
#include <bangtal>

using namespace bangtal;

enum class Hand {
	//���
	Pickax,
	//���
	Flag,
	//���� Ž����
	Detector,
	//�������� (���Ϳ��� ������ 1�� ȸ��)
	Spray,
};

class Item {
private:
	// ���� �÷��̵ǰ� �ִ� ���
	ScenePtr background;

	// ���� ��� ����
	int lifeCount;

	// ���� �ڵ� ��Ȳ
	Hand hand = Hand::Pickax;

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

public:
	Item(ScenePtr bg, int initLifeCount);

	// ���� �ڵ带 Ȯ���ϴ� �Լ�
	Hand getHand();

	// Hand�� �ش��ϴ� ������ index�� ��ȯ�ϴ� �Լ�
	int getItemIndex(Hand hand);

	// Hand�� �ٲٴ� �Լ� - KeyboardCallback�� ���� �ٸ� index�� ���ڷ� �޴´�.
	void ChangeHand(int index);

	// ���� �������� ������ Ȯ���ϴ� �Լ�
	int getItemCount(Hand hand);

	// �ش� �������� itemCount ���� ���� Item���� �̹����� �����ϴ� �Լ�
	void refreshCountImage(int itemIndex);

	// ��� �̹����� ���ΰ�ġ�� �Լ�
	void refreshLifeCountImage();

	// �������� ������ ���̴� �Լ�
	void ReduceItem(Hand hand);

	// �������� ������ �ø��� �Լ�
	void AddItem(ItemValue itemValue);
};