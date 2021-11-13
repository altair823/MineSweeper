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

// ������ ���� ���� ũ��
constexpr auto INIT_BOARD_SIZE = 10;

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
	Item* itemObject;

	// ���� ������� ������ ���¸� ǥ���ϱ� ���� ��ü
	ObjectPtr handObject;

	// ���� ���
	int life = LIFE_COUNT;

	// �̺�Ʈ �ڵ鷯
	std::shared_ptr<BlockBreakHandler> OnBlockBreak;

public:
	Board(ScenePtr bg);

	// ���带 �־��� ũ��� �ʱ�ȭ�ϰ� �����ϴ� �Լ�
	void RefreshBoard(int newRow, int newCol);

	// ���� ���带 �ʱ�ȭ�ϴ� �Լ�
	void Clear();

	// ���带 �־��� ũ��� ���� �����ϴ� �Լ�
	void GenerateNewBoard(int newRow, int newCol);

	// ������ ���¸� ��ȯ�ϴ� �Լ�
	BoardStatus getBoardStatus();

	// ������ ���� ũ�⸦ ��ȯ�ϴ� �Լ�
	int getRow();

	// ������ ���� ũ�⸦ ��ȯ�ϴ� �Լ�
	int getCol();
};