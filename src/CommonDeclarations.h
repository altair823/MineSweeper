/*
* CommonDeclarations.h
* 
* �ڵ� ������ ����ϴ� ��ũ�ο� ���� �������� �����ϴ� ���. 
* Ÿ�̸� �ð�, ��ǥ�� ���� ���� �����Ѵ�. 
*/

#pragma once

/*
* ���ڿ� ���ڸ� �����ϴ� enum.
* �ڵ� �������� ���������� ����� ���� �ʰ�
* ���ǵ� ���� ���� ���� ����.
*/
enum CellValue {
	Mine = -1,
	None = 0,
};

// �� �ϳ� �� ���� �ȼ� ����
constexpr auto CELL_SIZE = 30;