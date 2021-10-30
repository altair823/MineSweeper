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
	std::shared_ptr<_cell> create(ScenePtr bg, bool isThisMine, int row, int col);
}

class _cell {
	friend std::shared_ptr<_cell> Cell::create(ScenePtr, bool, int, int);

private:
	// ��Ż ������Ʈ ��ü
	ObjectPtr cellObject;

	// ����ĭ���� ����
	bool isThisMine;

	/*
	* _cell�� �����ڴ� ������ �ְ� Cell::create()�� ����� �����ؾ� �Ѵ�. 
	*/
	_cell(ScenePtr, const std::string, int, int);

public:

};

// _cell�� ���� shared_ptr�� CellPtr�� ���Ѵ�. 
typedef std::shared_ptr<_cell> CellPtr;