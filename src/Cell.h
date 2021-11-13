/*
* Cell
*
* ���忡 ������ ĭ Ŭ����.
* ���� ��ü���� ���丮 �޼���� ���� ������ ��
* �ش� ���� ��������, �׷��� ������ �����Ѵ�.
* ���� ���δ� �����ÿ� ���������� ���ڴ� ���Ŀ� ��������.
*/

#pragma once

#include "resource.h"
#include <bangtal>
#include "Block.h"
#include "MineField.h"
using namespace bangtal;


class _cell;

/*
* _cell ��ü�� shared_ptr�� �����Ͽ�
* CellPtr�� ��ȯ�ϴ� �Լ�.
*/
namespace Cell {
	std::shared_ptr<_cell> Create(ScenePtr bg, FieldData fieldData, int x, int y);
}

class _cell {
	// Create �Լ��� private�� ���� �����ϵ��� ����
	friend std::shared_ptr<_cell> Cell::Create(ScenePtr, FieldData, int, int);

private:
	// ��Ż ������Ʈ ��ü
	ObjectPtr cellObject;

	// ���� ���� �ִ� Block ��ü
	BlockPtr block;

	// ���� �巯�� ���������� ��Ÿ���� �÷���
	bool isOpened = false;

	/*
	* _cell�� �����ڴ� ������ �ְ� Cell::create()�� ����� �����ؾ� �Ѵ�.
	*/
	_cell(ScenePtr bg, FieldData fieldData, int x, int y);

public:
	/*
	* �־��� ���ڷ� �� �̹����� �ٲٴ� �Լ�
	*/
	void ChangeNumImage(FieldData fieldData);

	/*
	* ���� �μ��� �Լ�
	*/
	void BreakBlock();

	/*
	* ���� cell�� ���̴��� ���θ� ��ȯ�ϴ� �Լ�
	*/
	bool getIsOpened();

	/*
	* ���� cell�� ����� ���� ��ȯ�ϴ� �Լ�
	*/
	BlockPtr getBlock();
};

// _cell�� ���� shared_ptr�� CellPtr�� ���Ѵ�. 
typedef std::shared_ptr<_cell> CellPtr;