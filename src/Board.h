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
#include "Item.h"

using namespace bangtal;

static int boardCount = 0;

// ** ����׸� ���� 100���� �ʱ�ȭ �� **
constexpr auto LIFE_COUNT = 100;

// �� �ϳ� �� ���� �ȼ� ����
constexpr auto CELL_SIZE = 30;

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

	// ������ ��ü
	std::shared_ptr<Item> item;

	// �� ���� �̺�Ʈ �ڵ鷯
	std::shared_ptr<BlockBreakHandler> OnBlockBreak;

	// ���� ������ ����
	BoardStatus status = BoardStatus::Playing;


public:
	Board(ScenePtr bg, int initLifeCount);

	/*
	* ���带 �־��� ũ��� �ʱ�ȭ�ϰ� �����ϴ� �Լ�
	*/ 
	void RefreshBoard(int newRow, int newCol, int stageNum);

	/*
	* ���� ���带 �ʱ�ȭ�ϴ� �Լ�
	*/ 
	void Clear();

	/*
	* ���带 �־��� ũ��� ���� �����ϴ� �Լ�
	*/ 
	void GenerateNewBoard(int newRow, int newCol, int stageNum);

	/*
	* ������ �ʱ�ȭ �Լ�
	*/
	void InitItem(int initLifeCount);

	/*
	* ������ ���¸� ��ȯ�ϴ� �Լ�
	*/ 
	BoardStatus getBoardStatus();

	/*
	* ������ ���� ũ�⸦ ��ȯ�ϴ� �Լ�
	*/ 
	int getRow();

	/*
	* ������ ���� ũ�⸦ ��ȯ�ϴ� �Լ�
	*/ 
	int getCol();

	/*
	* ������ ���¸� �����ϴ� �Լ�
	*/
	void setBoardStatus(BoardStatus status);
};