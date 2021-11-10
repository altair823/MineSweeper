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
#include "Block.h"
using namespace bangtal;

class _cell;

/*
* _cell ��ü�� shared_ptr�� �����Ͽ�
* CellPtr�� ��ȯ�ϴ� �Լ�.
*/
namespace Cell {
	std::shared_ptr<_cell> Create(ScenePtr bg, FieldData fieldData, int x, int y, Hand* handPtr);
}

class _cell {
	// Create �Լ��� private�� ���� �����ϵ��� ����
	friend std::shared_ptr<_cell> Cell::Create(ScenePtr, FieldData, int, int, Hand*);

private:
	// ��Ż ������Ʈ ��ü
	ObjectPtr cellObject;

	// ���� ���� �ִ� Block ��ü
	BlockPtr block;

	// ���� �巯�� ���������� ��Ÿ���� �÷���
	bool isOpened = false;

	// ���� �ڵ��� ���¸� ����Ű�� ������
	Hand* handPtr;

	/*
	* _cell�� �����ڴ� ������ �ְ� Cell::create()�� ����� �����ؾ� �Ѵ�.
	*/
	_cell(ScenePtr bg, FieldData fieldData, int x, int y, Hand* handPtr);

public:
	/*
	* �־��� ���ڷ� �� �̹����� �ٲٴ� �Լ�
	*/
	void ChangeNumImage(FieldData fieldData);

	/*
	* block��ü�� blockObject�� ���� Mousecallback�� ����� �Լ�
	*/
	void MakeBlockCallback();

	/*
	* ���� �μ��� �Լ�
	*/
	void BreakBlock();

	/*
	* ���� cell�� ���̴��� ���θ� ��ȯ�ϴ� �Լ�
	*/
	bool getIsOpened();
};

// _cell�� ���� shared_ptr�� CellPtr�� ���Ѵ�. 
typedef std::shared_ptr<_cell> CellPtr;