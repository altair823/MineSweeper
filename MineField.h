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
#include <time.h>
#include <random>
#include "CommonDeclarations.h"


/*
* 2���� �迭���� �� �࿡ �ش��ϴ� Ŭ����.
* ������ �����ε��� ���� �ʿ��ϴ�. 
* MineField Ŭ���� �ۿ����� ������� �ʴ´�. 
*/
class _intArray {
private:
	// �� �࿡ ����ִ� ��ġ ������ ����
	std::vector<int> data;

public:
	_intArray(int size);

public:
	/*
	* �迭 ������ �����ε�
	*/
	int& const operator[](const int index);

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
	int row;
	int col;

	// ������ ����
	int mineCount;

	// ��� ��ġ �����Ͱ� ����ִ� 2���� ����
	std::vector<_intArray> fieldData;

public:

	/*
	* �迭 ������ �����ε�
	*/
	_intArray& const operator[](const int index);

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
	* ##����׿�## �迭�� ���� �������� �����ϴ� �Լ�
	*/
	void setRandomValue();

	/*
	* ##����׿�## ��� �Լ�
	*/
	void Print();
};