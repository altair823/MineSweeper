/*
* Item.h
*
* 지뢰찾기 게임에서 아이템을 관리하는 클래스.
* 아이템의 종류, 아이템의 개수, 현재 사용중인 아이템, 아이템바 객체 등은 이 클래스에서 관리한다.
* 현재 사용중인 아이템이 무엇인지는 이 클래스로부터 다른 클래스들로 전달된다.
* 아이템은 9칸을 강제로 열어주는 아이템, 1번의 전투를 회피시켜주는 아이템이 있다.
*/

#pragma once

#include <iostream>
#include "resource.h"
#include <bangtal>

using namespace bangtal;

//enum class Hand {
//	//곡괭이
//	Pickax,
//	//깃발
//	Flag,
//};

class Item {
private:
	// 현재 플레이되고 있는 배경
	ScenePtr background;

	// 현재 핸드 상황
	//Hand hand = Hand::Pickax;

	// 아이템의 종류를 표현해줄 아이템바 방탈오브젝트
	ObjectPtr itemBar;

	// 각 아이템의 개수를 확인하기 위한 배열(-1은 무한으로 한다.)
	int itemNumber[6] = { -1,-1,0,1,2,3 };

	// 각 아이템의 개수를 나타내기 위한 방탈 오브젝트 배열
	ObjectPtr numObject[6];

	// 현재 사용중인 아이템을 표현해줄 테두리 방탈오브젝트
	ObjectPtr nowUsing;

public:
	Item(ScenePtr bg);

	// 현재 핸드를 확인하는 함수
	//Hand getHand();

	// 현재 아이템의 개수를 확인하는 함수
	//int* getItemNumber();

	// Hand를 바꾸는 함수
	void ChangeHand(int n);

	// 아이템의 개수를 줄이는 함수
	//void ReduceItem(Hand hand);

	// 아이템의 개수를 늘리는 함수
	//void AddItem(Hand hand);
};