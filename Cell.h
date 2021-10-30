/*
* Cell
* 
* 보드에 나열될 칸 클래스. 
* 보드 객체에서 팩토리 메서드로 셀을 생성할 때
* 해당 셀이 지뢰일지, 그렇지 않을지 결정한다. 
* 지뢰 여부는 생성시에 결정되지만 숫자는 이후에 정해진다. 
*/

#pragma once

#include "CommonDeclarations.h"
#include "resource.h"
#include <bangtal>
using namespace bangtal;

class _cell;

/*
* _cell 객체를 shared_ptr로 생성하여 
* CellPtr을 반환하는 함수. 
*/
namespace Cell {
	std::shared_ptr<_cell> create(ScenePtr bg, bool isThisMine, int row, int col);
}

class _cell {
	friend std::shared_ptr<_cell> Cell::create(ScenePtr, bool, int, int);

private:
	// 방탈 오브젝트 객체
	ObjectPtr cellObject;

	// 지뢰칸인지 여부
	bool isThisMine;

	/*
	* _cell의 생성자는 숨겨져 있고 Cell::create()를 사용해 생성해야 한다. 
	*/
	_cell(ScenePtr, const std::string, int, int);

public:

};

// _cell에 대한 shared_ptr를 CellPtr로 정한다. 
typedef std::shared_ptr<_cell> CellPtr;