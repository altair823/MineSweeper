/*
* CommonDeclarations.h
* 
* �ڵ� ������ ����ϴ� ��ũ�ο� ���� �������� �����ϴ� ���. 
* Ÿ�̸� �ð�, ��ǥ�� ���� ���� �����Ѵ�. 
*/

#pragma once

/*
* ���ڸ� �����ϴ� enum.
* ���ڰ� �ƴ϶� ���ڶ�� �� ���� �ƴ� �ش� ���� ���� ������ �Ѵ�.
*/
enum CellValue {
	Escape = -2,
	Mine = -1,
	None = 0,
};

/*
* ������ �� Ż�ⱸ�� ���� �����Ѵ�. 
* ���� �������� �߰��Ǹ� ���⿡ �߰��� ��. 
*/
enum ItemValue {
	AddLife,
	MineDetector,
	AvoidCombat,
};

/*
* ���� ��ġ�� �����͸� ������ �� ����� ���� Ŭ����
*/
struct FieldData {
	// ���� ��ġ�� ����, Ż�ⱸ ����
	CellValue cellValue;

	// ���� ��ġ�� ���� ��
	int num;

	// ���� ��ġ�� ������ ��
	ItemValue itemValue;
};

// �� �ϳ� �� ���� �ȼ� ����
constexpr auto CELL_SIZE = 30;