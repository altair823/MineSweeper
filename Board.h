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

public:

	Board(ScenePtr bg);
};

