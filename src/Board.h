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
#include "Combat.h"
#include "Combats/RockPaperScissor.h"
#include "Combats/DiceRolling.h"
#include "Combats/ShootTheMonster.h"
using namespace bangtal;

static int boardCount = 0;

/*
* ����ã�⸦ ������ �� Ŭ����
*/
class Board {
private:
	// ���
	ScenePtr background;

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

	// **����׿�** ���带 �ʱ�ȭ �ϱ� ���� ��ư ��ü
	ObjectPtr resetButton;

public:

	Board(ScenePtr bg);

	// �ڵ���Ʈ�� ��ü�� ���¸� �ٲٴ� �Լ�
	void HandChange();

	// ���带 �ʱ�ȭ�ϴ� �Լ�
	void RefreshBoard(Status stat, ScenePtr ch);
};