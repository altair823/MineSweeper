/*
* MineField.h
* 
* ����ã�� ���ӿ��� ���ڿ� ������ ��ġ �����͸� �����ϴ� Ŭ����.
* ���ڿ� ����, ��ĭ�� ��ġ�� �����ϰ�, 
* �� ������ ������ ������ ���� ũ�⿡ ���� ���ڸ� ������������ ��ġ�ϸ�,
* �ܺο��� ��ġ�� ���� �����Ϳ� ������ �� �ֵ��� �Ѵ�. 
*/

#pragma once

#include <iostream>
#include <vector>
#include <random>



/*
* ���ڿ� ����, Ż�ⱸ�� �����ϴ� enum.
*/
enum CellValue {
	Escape,
	Mine,
	Empty,
};

/*
* �������� �����ϴ� enum.
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
* �� cell�� ��� ������ ������ �� ����� Ŭ����.
* ���� ������ ���ÿ� ������ �� ����Ѵ�.
*/
struct FieldData {
	// ����, Ż�ⱸ, ��ĭ ����
	CellValue cellValue;
	// ���� ��
	int num;
	// ������ ��
	ItemValue itemValue;
};

/*
* 2���� �迭���� �� �࿡ �ش��ϴ� Ŭ����.
* ������ �����ε��� ���� �ʿ��ϴ�. 
* MineField Ŭ���� �ۿ����� ������� �ʴ´�. 
*/
class _fieldDataArray {
private:
	// �� �࿡ ����ִ� ��ġ ������ ����
	std::vector<FieldData> data;

public:
	_fieldDataArray(int size);

public:
	/*
	* �迭 ������ �����ε�
	*/
	FieldData& const operator[](const int index);

	/*
	* �ʱ�ȭ �Լ�
	*/
	void Clear();

	/*
	* ���͸� �־��� ũ��� �ø��� ���� �ʱ�ȭ�ϴ� �Լ�
	*/
	void Resize(int size);
};

class MineField {
private:
	// ���� ����ã���� ����, ���� ����
	int row = 0;
	int col = 0;

	// ������ ����
	int mineCount;

	// ��� ��ġ �����Ͱ� ����ִ� 2���� ����
	std::vector<_fieldDataArray> fieldData;

public:

	/*
	* �迭 ������ �����ε�
	*/
	_fieldDataArray& const operator[](const int index);

	/*
	* 2���� ���͸� ��� �ʱ�ȭ�ϴ� �Լ�
	*/
	void Clear();

	/*
	* ���ο� 2���� ���͸� �����ϴ� �Լ�
	*/
	void Resize(int newRow, int newCol);

	/*
	* ���ڸ� �������� �Ѹ��� �Լ�
	*/
	void MountMine();

	/*
	* ���� ĭ �ֺ� ĭ�鿡 ���ڸ� ä���ִ� �Լ�
	*/
	void setAdjacentNum();

	/*
	* ##����׿�## ��� �Լ�
	*/
	void Print();
};