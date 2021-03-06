/*
* Cell
*
* 보드에 나열될 칸 클래스.
* 보드 객체에서 팩토리 메서드로 셀을 생성할 때
* 해당 셀이 지뢰일지, 그렇지 않을지 결정한다.
* 지뢰 여부는 생성시에 결정되지만 숫자는 이후에 정해진다.
*/

#pragma once

#include "resource.h"
#include <bangtal>
#include "Block.h"
#include "MineField.h"
using namespace bangtal;


class _cell;

/*
* _cell 객체를 shared_ptr로 생성하여
* CellPtr을 반환하는 함수.
*/
namespace Cell {
	std::shared_ptr<_cell> Create(ScenePtr bg, FieldData fieldData, int x, int y, int stageNum);
}

class _cell {
	// Create 함수가 private에 접근 가능하도록 설정
	friend std::shared_ptr<_cell> Cell::Create(ScenePtr, FieldData, int, int, int);

private:
	// 셀의 방탈 오브젝트 객체
	ObjectPtr cellObject;

	// 셀을 덮고 있는 Block 객체
	BlockPtr block;

	// 셀의 아이템 값
	ItemValue itemValue;

	// 셀의 아이템 이미지를 보여줄 오브젝트
	ObjectPtr itemObject;

	// 아이템 이미지를 보여주고 제거할 타이머
	TimerPtr itemShowTimer;

	// 셀이 드러난 상태인지를 나타내는 플래그
	bool isOpened = false;

	/*
	* _cell의 생성자는 숨겨져 있고 Cell::create()를 사용해 생성해야 한다.
	*/
	_cell(ScenePtr bg, FieldData fieldData, int x, int y, int stageNum);

public:
	/*
	* 주어진 숫자로 셀 이미지를 바꾸는 함수
	*/
	void ChangeNumImage(FieldData fieldData);

	/*
	* 블럭을 부수는 함수
	*/
	void BreakBlock();

	/*
	* 현재 cell이 보이는지 여부를 반환하는 함수
	*/
	bool getIsOpened();

	/*
	* 현재 cell과 연결된 블럭을 반환하는 함수
	*/
	BlockPtr getBlock();

	/*
	* 현재 cell의 ItemValue 값 반환
	*/
	ItemValue getItemValue();
};

// _cell에 대한 shared_ptr를 CellPtr로 정한다. 
typedef std::shared_ptr<_cell> CellPtr;