/*
* Board
*
* ����ã�� ������ ������ ���� �����ϴ� Ŭ����.
* �� ������������ ������ ������ ĭ�� ������
* ������ ��ġ�� �� �Ǹ��� ���������̾�� �Ѵ�.
*
*/

#pragma once

#include "Cell.h"
#include "MineField.h"
#include <vector>
#include <bangtal>
#include "BlockBreakHandler.h"

using namespace bangtal;

static int boardCount = 0;

/*
* ����ã�⸦ ������ �� Ŭ����
*/
class Board {
private:
	// ���
	ScenePtr background;

	// ������ ���� ���� ũ��
	int row, col;

	// ĭ ��ü�� �����ϴ� 2���� vector
	std::vector<std::vector<CellPtr>> cells;

	// ����ã�� �� ��ü�� �����͸� �����ϴ� ��ü
	MineField field;

	// ���� ������� ����
	Hand hand = Hand::Pickax;

	// ���� ������� ������ ���¸� ǥ���ϱ� ���� ��ü
	ObjectPtr handObject;

	// ���� ������ ��Ȳ�� ��Ÿ���� ����
	Status status;

	// �̺�Ʈ �ڵ鷯
	std::shared_ptr<BlockBreakHandler> OnBlockBreak;

	// **����׿�** ���带 �ʱ�ȭ �ϱ� ���� ��ư ��ü
	ObjectPtr resetButton;

public:

	Board(ScenePtr bg);

	// �ڵ���Ʈ�� ��ü�� ���¸� �ٲٴ� �Լ�
	void HandChange();

	// ���带 �־��� ũ��� �ʱ�ȭ�ϰ� �����ϴ� �Լ�
	void RefreshBoard(int newRow, int newCol);

	// ���� ���带 �ʱ�ȭ�ϴ� �Լ�
	void Clear();

	// ���带 �־��� ũ��� ���� �����ϴ� �Լ�
	void GenerateNewBoard(int newRow, int newCol);
};