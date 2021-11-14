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
#include "resource.h"
#include <bangtal>

using namespace bangtal;

enum class Hand {
	//���
	Pickax,
	//���
	Flag,
	//��ź (��ó 9ĭ�� �μ��� ������)
	Tnt,
	//��Ʈ (������ 1 �����ִ� ������)
	Heart,
	//�������� (���Ϳ��� ������ 1�� ȸ���ϰ� �ϴ� ������
	Spray,
	//���
	None,
};

class Item {
private:
	// ���� �÷��̵ǰ� �ִ� ���
	ScenePtr background;

	// ���� �ڵ� ��Ȳ
	Hand hand = Hand::Pickax;

	// �������� ������ ǥ������ �����۹� ��Ż������Ʈ
	ObjectPtr itemBar;

	// �� �������� ������ Ȯ���ϱ� ���� �迭(-1�� �������� �Ѵ�.)
	// �� index ���� �������� �ʱ� ������ ������ �� �ִ�.
	int itemNumber[6] = { -1,-1,1,2,3,-1 };

	// �� �������� ������ ȭ�鿡 ǥ���ϱ� ���� ��Ż ������Ʈ �迭
	ObjectPtr numObject[6];

	// ���� ������� �������� ǥ������ �׵θ� ��Ż������Ʈ
	ObjectPtr nowUsing;

public:
	Item(ScenePtr bg);

	// ���� �ڵ带 Ȯ���ϴ� �Լ�
	Hand getHand();

	// Hand�� �ش��ϴ� ������ index�� ��ȯ�ϴ� �Լ�
	int getHandIndex(Hand hand);

	// Hand�� �ٲٴ� �Լ� - KeyboardCallback�� ���� �ٸ� index�� ���ڷ� �޴´�.
	void ChangeHand(int index);

	// ���� �������� ������ Ȯ���ϴ� �Լ�
	int getItemNumber(Hand hand);

	// Item ������ ���� Item���� �̹����� �����ϴ� �Լ�
	// ����Լ� ReduceItem Ȥ�� AddItem�� ���ؼ��� �Ҹ���.
	void ChangeNumberImage(int index);

	// �������� ������ ���̴� �Լ�
	void ReduceItem(Hand hand);

	// �������� ������ �ø��� �Լ�
	void AddItem(Hand hand);
};