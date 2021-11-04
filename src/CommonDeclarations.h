/*
* CommonDeclarations.h
* 
* 코드 내에서 사용하는 매크로와 전역 변수들을 정의하는 헤더. 
* 타이머 시간, 좌표값 간격 등을 정의한다. 
*/

#pragma once

/*
* 지뢰를 정의하는 enum.
* 지뢰가 아니라 숫자라면 이 값이 아닌 해당 숫자 값을 갖도록 한다.
*/
enum CellValue {
	Escape = -2,
	Mine = -1,
	None = 0,
};

/*
* 아이템 및 탈출구의 값을 정의한다. 
* 만약 아이템이 추가되면 여기에 추가할 것. 
*/
enum ItemValue {
	AddLife,
	MineDetector,
	AvoidCombat,
};

/*
* 현재 위치의 데이터를 전해줄 때 사용할 형식 클래스
*/
struct FieldData {
	// 현재 위치의 지뢰, 탈출구 여부
	CellValue cellValue;

	// 현재 위치의 숫자 값
	int num;

	// 현재 위치의 아이템 값
	ItemValue itemValue;
};

// 셀 하나 한 변의 픽셀 길이
constexpr auto CELL_SIZE = 30;