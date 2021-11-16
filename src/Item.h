/*
* Item.h
*
* 지뢰찾기 게임에서 아이템을 관리하는 클래스.
* 아이템의 종류, 아이템의 개수, 목숨의 개수, 현재 사용중인 아이템, 아이템바 객체 등은 이 클래스에서 관리한다.
* 현재 사용중인 아이템이 무엇인지는 이 클래스로부터 다른 클래스들로 전달된다.
*/

#pragma once

#include <iostream>
#include <vector>
#include "resource.h"
#include "MineField.h"
#include <bangtal>

// 무한개의 아이템 개수 정의
constexpr auto INFINITE = -1;
// 목숨의 가능한 최대의 개수 정의
constexpr auto MAX_LIFE_COUNT = 19;

using namespace bangtal;

/*
* 아이템 창에서 선택가능한 항목들
*/
enum class Hand {
	//곡괭이
	Pickax,
	//깃발
	Flag,
	//지뢰 탐지기
	Detector,
	//스프레이 (몬스터와의 전투를 1번 회피)
	Spray,
};

class Item {
private:
	// 현재 플레이되고 있는 배경
	ScenePtr background;

	// 현재 핸드 상황
	Hand currentHand = Hand::Pickax;

	// 아이템바 방탈 오브젝트
	ObjectPtr itemBar;

	// 아이템 오브젝트 벡터
	std::vector<ObjectPtr> itemObject;

	// 각 아이템의 개수를 확인하기 위한 배열
	std::vector<int> itemCount;

	// 각 아이템의 개수를 화면에 표시하기 위한 방탈 오브젝트 배열
	std::vector<ObjectPtr> itemCountOnject;

	// 현재 사용중인 아이템을 표시해줄 테두리 방탈오브젝트
	ObjectPtr currentItemIndicator;

	// 목숨 이미지 오브젝트 벡터
	// 이 벡터의 크기가 곧 목숨의 개수이다. 
	std::vector<ObjectPtr> lifeObject;

	// 스프레이 사용 후 인디케이터
	ObjectPtr sprayUsedIndicator;
	bool isSprayUsed;

	/*
	* 해당 아이템의 itemCount 값에 따라 Item개수 이미지를 변경하는 함수
	*/
	void refreshCountImage(int itemIndex);

	/*
	* Hand에 해당하는 아이템 index를 반환하는 함수
	*/
	int getItemIndex(Hand hand);

public:
	Item(ScenePtr bg, int initLifeCount);

	/*
	* 현재 핸드를 확인하는 함수
	*/ 
	Hand getCurrentHand();

	/*
	* Hand를 바꾸는 함수들
	*/ 
	void ChangeHandByIndex(int index);
	void ChangeHand(Hand hand);

	/*
	* 현재 아이템의 개수를 확인하는 함수
	*/ 
	int getItemCount(Hand hand);

	/*
	* 아이템의 개수를 줄이는 함수
	*/ 
	void ReduceItem(Hand hand);

	/*
	* 아이템의 개수를 늘리는 함수
	*/ 
	void AddItem(ItemValue itemValue);

	/*
	* 목숨의 개수를 하나 줄이는 함수
	*/
	void ReduceLifeCount();

	/*
	* 목숨을 하나 추가하는 함수
	*/
	void AddLifeCount();

	/*
	* 목숨 개수를 반환하는 함수
	*/
	int getLifeCount();
};