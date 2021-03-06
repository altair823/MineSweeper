/*
* Block
*
* 보드의 칸 위에 덮힐 블럭 클래스.
* 보드 객체에서 셀을 생성할 때, 자동으로 그 위를 블럭이 덮도록 한다.
*/

#pragma once

#include "resource.h"
#include <bangtal>
using namespace bangtal;

class _block;

/*
* _block 객체를 shared_ptr로 생성하여
* BlockPtr을 반환하는 함수.
*/
namespace Block {
	std::shared_ptr<_block> Create(ScenePtr bg, int x, int y, int stageNum);
}


class _block {
	// Create 함수가 private에 접근 가능하도록 설정
	friend std::shared_ptr<_block> Block::Create(ScenePtr, int, int, int);

private:
	// 깃발 이미지인지 여부
	bool isFlagImage;

	// 현재 스테이지 번호
	// 블럭 이미지의 종류를 결정한다. 
	int stageNum;

	// 방탈 오브젝트 객체
	ObjectPtr blockObject;

	/*
	* _block의 생성자는 숨겨져 있고 Block::create()를 사용해 생성해야 한다.
	*/
	_block(ScenePtr bg, int x, int y, int stageNum);

public:
	/*
	* 깃발로 블럭 이미지를 바꾸는 함수
	*/
	void ChangeToFlagImage();

	/*
	* 빈 블럭으로 블럭 이미지를 바꾸는 함수
	*/
	void ChangeToEmptyBlockImage();

	/*
	* 빈 블럭은 깃발블럭으로 깃발블럭은 빈 블럭으로 바꾸는 함수
	*/
	void SwapBlockImage();

	/*
	* blockObject를 숨기는 함수
	*/
	bool HideBlock();

	/*
	* 블럭을 클릭 했을 때를 위한 콜백 함수
	* 함수의 인자를 전달받아 blockObject의 setOnMouseCallback()에 전달한다.
	*/ 
	void setClickCallback(std::function<bool(ObjectPtr, int, int, MouseAction)> callback);
};

// _block에 대한 shared_ptr를 BlockPtr로 정한다. 
typedef std::shared_ptr<_block> BlockPtr;