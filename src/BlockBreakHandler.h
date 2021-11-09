/*
* BlockBreakHandler.h
* 
* ���� Ŭ���ؼ� ������ ��, �������� üũ�ϰ� �̺�Ʈ�� ó���ϴ� Ŭ����. 
* ���� ĭ�̶�� ���� ��Ȳ���� �̵��ϰ�,
* ��ĭ�̶�� Ȯ���� �ϸ�, ���� ĭ�̶�� �ƹ��͵� ���� �ʴ´�. 
*/

#pragma once

#include <vector>
#include "MineField.h"
#include "Cell.h"
#include <bangtal>

#include "Combat.h"
#include "Combats/DiceMatching.h"
#include "Combats/DiceRolling.h"
#include "Combats/OddOrEven.h"
#include "Combats/RockPaperScissor.h"
#include "Combats/RockPaperScissor.h"
#include "Combats/ShootTheMonster.h"

using namespace bangtal;

class BlockBreakHandler {
private:

	// ������ ũ��
	int row, col;

	// ������ ���ȴ����� üũ�ϴ� 2���� ����
	std::vector<std::vector<bool>> isCellOpen;

	// ��� ĭ���� �����͸� ����
	MineField& field;

	// ��� ���� 2���� ���͸� ����
	std::vector<std::vector<CellPtr>>& cells;

	// ���� ���� cell�� �ִ��� üũ�� Ÿ�̸�
	TimerPtr refreshTimer;

public:
	BlockBreakHandler(int newRow, int newCol, MineField& newField, std::vector<std::vector<CellPtr>>& newCells);
	~BlockBreakHandler();

	/*
	* ���� ���� cell�� �ִ��� Ȯ���ϴ� �Լ�
	*/
	void CheckNewCellOpened();

	/*
	* �� ĭ�� ��迡 �ִ� cell���� ���� Ȯ���ϴ� �Լ�
	*/
	void ExpandBorder(int i, int j);

	/*
	* cell Ȯ���� �ߴ��ϴ� �Լ�
	* Timer�� �ʱ�ȭ�ϱ� ���� �ʿ���.
	*/
	void StopCheckNewCellOpened();
};

