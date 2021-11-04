/*
* CommonDeclarations.h
* 
* 코드 내에서 사용하는 매크로와 전역 변수들을 정의하는 헤더. 
* 타이머 시간, 좌표값 간격 등을 정의한다. 
*/

#pragma once

/*
* 지뢰와 숫자를 정의하는 enum.
* 코드 내에서는 직접적으로 상수를 쓰지 않고
* 정의된 값을 쓰는 것이 좋다.
*/
enum CellValue {
	Mine = -1,
	None = 0,
};

// 셀 하나 한 변의 픽셀 길이
#define CELL_SIZE 20