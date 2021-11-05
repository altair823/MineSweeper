/*
* CommonDeclarations.h
* 
* 코드 내에서 사용하는 매크로와 전역 변수들을 정의하는 헤더. 
* 타이머 시간, 좌표값 간격 등을 정의한다. 
*/

#pragma once

/*
* 지뢰와 숫자, 탈출구를 정의하는 enum.
*/
enum CellValue {
	Escape,
	Mine,
	Empty,
};

/*
* 아이템을 정의하는 enum. 
*/
enum ItemValue {
	AddLife,
	MineDetector,
	AvoidCombat,
	None,
};

/*
* 한 cell에 담긴 정보를 전달할 때 사용할 클래스. 
* 여러 정보를 동시에 전달할 때 사용한다. 
*/
struct FieldData {
	// 지뢰, 탈출구, 빈칸 여부
	CellValue cellValue;

	// 숫자 값
	int num;

	// 아이템 값
	ItemValue itemValue;
};

// 셀 하나 한 변의 픽셀 길이
constexpr auto CELL_SIZE = 30;
