/*
* Item.h
*
* 지뢰찾기 게임에서 아이템을 관리하는 클래스.
* 아이템의 종류, 아이템의 개수, 현재 사용중인 아이템, 아이템바 객체 등은 이 클래스에서 관리한다.
* 현재 사용중인 아이템이 무엇인지는 이 클래스로부터 다른 클래스들로 전달된다.
* 아이템은 9칸을 강제로 열어주는 아이템, 1번의 전투를 회피시켜주는 아이템이 있다.
* 아이템의 최대 개수는 3개로 한다.
*/

#pragma once

#include <iostream>
#include "resource.h"
#include <bangtal>

using namespace bangtal;

enum class Hand {
	//곡괭이
	Pickax,
	//깃발
	Flag,
	//폭탄 (근처 9칸을 부수는 아이템)
	Tnt,
	//하트 (생명을 1 더해주는 아이템)
	Heart,
	//스프레이 (몬스터와의 전투를 1번 회피하게 하는 아이템
	Spray,
	//빈손
	None,
};

class Item {
private:
	// 현재 플레이되고 있는 배경
	ScenePtr background;

	// 현재 핸드 상황
	Hand hand = Hand::Pickax;

	// 아이템의 종류를 표현해줄 아이템바 방탈오브젝트
	ObjectPtr itemBar;

	// 각 아이템의 개수를 확인하기 위한 배열(-1은 무한으로 한다.)
	// 각 index 별로 아이템의 초기 개수를 설정할 수 있다.
	int itemNumber[6] = { -1,-1,1,2,3,-1 };

	// 각 아이템의 개수를 화면에 표시하기 위한 방탈 오브젝트 배열
	ObjectPtr numObject[6];

	// 현재 사용중인 아이템을 표시해줄 테두리 방탈오브젝트
	ObjectPtr nowUsing;

public:
	Item(ScenePtr bg);

	// 현재 핸드를 확인하는 함수
	Hand getHand();

	// Hand에 해당하는 아이템 index를 반환하는 함수
	int getHandIndex(Hand hand);

	// Hand를 바꾸는 함수 - KeyboardCallback에 따라 다른 index를 인자로 받는다.
	void ChangeHand(int index);

	// 현재 아이템의 개수를 확인하는 함수
	int getItemNumber(Hand hand);

	// Item 개수에 따라 Item개수 이미지를 변경하는 함수
	// 멤버함수 ReduceItem 혹은 AddItem에 의해서만 불린다.
	void ChangeNumberImage(int index);

	// 아이템의 개수를 줄이는 함수
	void ReduceItem(Hand hand);

	// 아이템의 개수를 늘리는 함수
	void AddItem(Hand hand);
};