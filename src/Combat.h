/*
* Combat.h
* 
* 몬스터 칸(지뢰 칸)을 누르면 Combat 클래스 객체가 생성되고
* 이를 통해 전투상황으로 진입한다. 
* 
* Combat 클래스 자체는 가상 메서드로만 이루어진 인터페이스이다. 
* 몬스터의 종류에 따라 다른 전투 이벤트가 발생하므로, 
* Combat 인터페이스를 상속한 여러 전투 클래스를 구현하여 이를 다룬다. 
*/
#pragma once
#include "resource.h"



class Combat {
public:

	/*
	* 전투 상황으로 진입하는 함수.
	* 모든 전투 클래스는 이 함수를 사용해 전투 상황에 진입한다. 
	*/
	virtual void EnterBattle() = 0;

};
