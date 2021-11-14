/*
* MineField.h
* 
* 지뢰찾기 게임에서 지뢰와 숫자의 위치 데이터를 관리하는 클래스.
* 지뢰와 숫자, 빈칸의 위치를 저장하고, 
* 새 게임이 시작할 때마다 판의 크기에 따라 지뢰를 무작위적으로 배치하며,
* 외부에서 위치에 따른 데이터에 접근할 수 있도록 한다. 
*/

#pragma once

#include <iostream>
#include <vector>
#include <random>



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

constexpr auto ADDLIFE_COUNT = 1;
constexpr auto MINE_DETECTOR_COUNT = 1;
constexpr auto AVOID_COMBAT_COUNT = 1;

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

/*
* 2차원 배열에서 한 행에 해당하는 클래스.
* 연산자 오버로딩을 위해 필요하다. 
* MineField 클래스 밖에서는 사용하지 않는다. 
*/
class _fieldDataArray {
private:
	// 한 행에 들어있는 위치 데이터 벡터
	std::vector<FieldData> data;

public:
	_fieldDataArray(int size);

public:
	/*
	* 배열 연산자 오버로딩
	*/
	FieldData& const operator[](const int index);

	/*
	* 초기화 함수
	*/
	void Clear();

	/*
	* 벡터를 주어진 크기로 늘리고 새로 초기화하는 함수
	*/
	void Resize(int size);
};

class MineField {
private:
	// 현재 지뢰찾기의 가로, 세로 길이
	int row = 0;
	int col = 0;

	// 지뢰의 개수
	int mineCount;

	// 모든 위치 데이터가 들어있는 2차원 벡터
	std::vector<_fieldDataArray> fieldData;

public:

	/*
	* 배열 연산자 오버로딩
	*/
	_fieldDataArray& const operator[](const int index);

	/*
	* 2차원 벡터를 모두 초기화하는 함수
	*/
	void Clear();

	/*
	* 새로운 2차원 벡터를 생성하는 함수
	*/
	void Resize(int newRow, int newCol);

	/*
	* 지뢰를 무작위로 뿌리는 함수
	*/
	void MountMine();

	/*
	* 지뢰 칸 주변 칸들에 숫자를 채워넣는 함수
	*/
	void setAdjacentNum();

	/*
	* ##디버그용## 출력 함수
	*/
	void Print();
};