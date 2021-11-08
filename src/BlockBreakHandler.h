/*
* BlockBreakHandler.h
* 
* ���� Ŭ���ؼ� ������ ��, �� �̺�Ʈ�� ó���ϴ� Ŭ����. 
* ���� ĭ�̶�� ���� ��Ȳ���� �̵��ϰ�,
* ��ĭ�̶�� Ȯ���� �ϸ�, ���� ĭ�̶�� �ƹ��͵� ���� �ʴ´�. 
*/

#pragma once

#include <vector>
#include "MineField.h"
#include "Cell.h"
#include <bangtal>
using namespace bangtal;

class BlockBreakHandler {
private:

	// ������ ũ��
	int row, col;

	// ������ ���ȴ����� üũ�ϴ� 2���� ����
	std::vector<std::vector<bool>> isCellOpen;

	// ��� ĭ���� ������
	MineField& field;

	// ��� ��
	std::vector<std::vector<CellPtr>>& cells;

	// ���� ���� cell�� �ִ��� üũ�� Ÿ�̸�
	TimerPtr refreshTimer;

public:
	BlockBreakHandler(int newRow, int newCol, MineField& newField, std::vector<std::vector<CellPtr>>& newCells);

	/*
	* ���� ���� cell�� �ִ��� Ȯ���ϴ� �Լ�
	*/
	void CheckNewCellOpened();

	void StopCheckNewCellOpened();
};

