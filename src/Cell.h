/*
* Cell
* 
* ���忡 ������ ĭ Ŭ����. 
* ���� ��ü���� ���丮 �޼���� ���� ������ ��
* �ش� ���� ��������, �׷��� ������ �����Ѵ�. 
* ���� ���δ� �����ÿ� ���������� ���ڴ� ���Ŀ� ��������. 
*/

#pragma once

#include "CommonDeclarations.h"
#include "resource.h"
#include <bangtal>
using namespace bangtal;

class _cell;

/*
* _cell ��ü�� shared_ptr�� �����Ͽ� 
* CellPtr�� ��ȯ�ϴ� �Լ�. 
*/
namespace Cell {
	std::shared_ptr<_cell> Create(ScenePtr bg, FieldData cell, int row, int col);
}

class _cell {
	// Create �Լ��� private�� ���� �����ϵ��� ����
	friend std::shared_ptr<_cell> Cell::Create(ScenePtr, FieldData, int, int);

private:
	// ��Ż ������Ʈ ��ü
	ObjectPtr cellObject;

	// ����ĭ���� ����
	bool isThisMine;

	/*
	* _cell�� �����ڴ� ������ �ְ� Cell::create()�� ����� �����ؾ� �Ѵ�. 
	*/
	_cell(ScenePtr bg, FieldData cellValue, int x, int y);

public:
	/*
	* �־��� ���ڷ� �� �̹����� �ٲٴ� �Լ�
	*/
	void ChangeNumImage(FieldData cellValue);
};

// _cell�� ���� shared_ptr�� CellPtr�� ���Ѵ�. 
typedef std::shared_ptr<_cell> CellPtr;