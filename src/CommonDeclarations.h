/*
* CommonDeclarations.h
*
* �ڵ� ������ ����ϴ� ��ũ�ο� ���� �������� �����ϴ� ���.
* Ÿ�̸� �ð�, ��ǥ�� ���� ���� �����Ѵ�.
*/

#pragma once

/*
* �������� ���� ��Ȳ�� �����ϴ� enum.
*/
enum Status {
	Playing,
	GameOver,
	Clear
};

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

/*
* �ڵ忡 ����ϴ� enum
*/
enum class Hand {
	//���
	Pickax,
	//���
	Flag,
};


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

// �� �ϳ� �� ���� �ȼ� ����
constexpr auto CELL_SIZE = 30;

// ������ ���� ���� ũ��
constexpr auto INIT_BOARD_SIZE = 10;

// �̺�Ʈ �ڵ鷯�� ���� ����
constexpr auto REFRESH_TIME = 0.1f;