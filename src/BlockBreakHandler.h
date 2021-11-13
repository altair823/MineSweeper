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

// �̺�Ʈ �ڵ鷯�� ���� ����
constexpr auto REFRESH_TIME = 0.1f;

/*
* �������� ���� ��Ȳ�� �����ϴ� enum.
*/
enum class BoardStatus {
	// ������ ��������
	Playing,
	// ������ �÷��̾��� �й�� ����
	GameOver,
	// Ż�ⱸ�� ã��
	Escape,
	// ���ڸ� ������ ��� ĭ�� ����
	Clear
};

class BlockBreakHandler {
private:
	// ���� ������ ũ��
	int& row, col;

	// ���� ������ ����
	BoardStatus status = BoardStatus::Playing;

	// ���� ������ ���
	ScenePtr boardBackground;

	// ������ ���ȴ����� üũ�ϴ� 2���� ����
	std::vector<std::vector<bool>> isCellOpen;

	// ��� ĭ���� �����͸� ����
	MineField& field;

	// ��� ���� 2���� ���͸� ����
	std::vector<std::vector<CellPtr>>& cells;

	// ���� ���� cell�� �ִ��� üũ�� Ÿ�̸�
	TimerPtr refreshTimer;

	// ���ڸ� ���� �� ������ ���� ��Ȳ ������
	Combat* newCombat = nullptr;

public:
	BlockBreakHandler(int& newRow, int& newCol, MineField& newField, std::vector<std::vector<CellPtr>>& newCells, ScenePtr boardBackground);
	~BlockBreakHandler();


	/*
	* ���� ���� cell�� �ִ��� Ȯ���ϴ� �Լ�
	*/
	void CheckNewCellOpened();

	/*
	* �������� ���� ��Ȳ���� �����ϴ� �Լ�
	*/
	void EnterRandomCombat(int curRow, int curCol);

	/*
	* �� ĭ�� ��迡 �ִ� cell���� ���� Ȯ���ϴ� �Լ�
	*/
	void ExpandBorder(int curRow, int curCol);

	/*
	* ������ �����ϸ� ������ ���¸� �����ϴ� �Լ�
	*/
	void RefreshBoardStatus(int curRow, int curCol);

	/*
	* cell Ȯ���� �ߴ��ϴ� �Լ�
	* Timer�� �ʱ�ȭ�ϱ� ���� �ʿ���.
	*/
	void StopCheckNewCellOpened();

	/*
	* ������ ���¸� ��ȯ�ϴ� �Լ�
	*/
	BoardStatus getStatus();

	/*
	* ������ ���¸� �����ϴ� �Լ�
	*/
	void setStatus(BoardStatus stat);
};

