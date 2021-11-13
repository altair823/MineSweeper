/*
* Item.h
*
* ����ã�� ���ӿ��� �������� �����ϴ� Ŭ����.
* �������� ����, �������� ����, ���� ������� ������, �����۹� ��ü ���� �� Ŭ�������� �����Ѵ�.
* ���� ������� �������� ���������� �� Ŭ�����κ��� �ٸ� Ŭ������� ���޵ȴ�.
* �������� 9ĭ�� ������ �����ִ� ������, 1���� ������ ȸ�ǽ����ִ� �������� �ִ�.
*/

#pragma once

#include <iostream>
#include "resource.h"
#include <bangtal>

using namespace bangtal;

//enum class Hand {
//	//���
//	Pickax,
//	//���
//	Flag,
//};

class Item {
private:
	// ���� �÷��̵ǰ� �ִ� ���
	ScenePtr background;

	// ���� �ڵ� ��Ȳ
	//Hand hand = Hand::Pickax;

	// �������� ������ ǥ������ �����۹� ��Ż������Ʈ
	ObjectPtr itemBar;

	// �� �������� ������ Ȯ���ϱ� ���� �迭(-1�� �������� �Ѵ�.)
	int itemNumber[6] = { -1,-1,0,1,2,3 };

	// �� �������� ������ ��Ÿ���� ���� ��Ż ������Ʈ �迭
	ObjectPtr numObject[6];

	// ���� ������� �������� ǥ������ �׵θ� ��Ż������Ʈ
	ObjectPtr nowUsing;

public:
	Item(ScenePtr bg);

	// ���� �ڵ带 Ȯ���ϴ� �Լ�
	//Hand getHand();

	// ���� �������� ������ Ȯ���ϴ� �Լ�
	//int* getItemNumber();

	// Hand�� �ٲٴ� �Լ�
	void ChangeHand(int n);

	// �������� ������ ���̴� �Լ�
	//void ReduceItem(Hand hand);

	// �������� ������ �ø��� �Լ�
	//void AddItem(Hand hand);
};