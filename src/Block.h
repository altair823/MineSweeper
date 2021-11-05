/*
* Block
*
* ������ ĭ ���� ���� �� Ŭ����.
* ���� ��ü���� ���� ������ ��, �ڵ����� �� ���� ���� ������ �Ѵ�.
*/

#pragma once

#include "CommonDeclarations.h"
#include "resource.h"
#include <bangtal>
using namespace bangtal;

class _block;

/*
* _block ��ü�� shared_ptr�� �����Ͽ�
* BlockPtr�� ��ȯ�ϴ� �Լ�.
*/
namespace Block {
	std::shared_ptr<_block> Create(ScenePtr bg, int x, int y);
}


class _block {
	// Create �Լ��� private�� ���� �����ϵ��� ����
	friend std::shared_ptr<_block> Block::Create(ScenePtr, int, int);

private:
	// ��� �̹������� ����
	bool isFlagImage;

	// ��Ż ������Ʈ ��ü
	ObjectPtr blockObject;

	/*
	* _block�� �����ڴ� ������ �ְ� Block::create()�� ����� �����ؾ� �Ѵ�.
	*/
	_block(ScenePtr bg, int x, int y);

public:
	/*
	* ��߷� �� �̹����� �ٲٴ� �Լ�
	*/
	void ChangeFlagImage();

	/*
	* �� ������ �� �̹����� �ٲٴ� �Լ�
	*/
	void ChangeEmptyBlockImage();

	/*
	* blockObject�� ����� �Լ�
	*/
	void hideBlock();

	/*
	* ���� Ŭ�� ���� ���� ���� �ݹ� �Լ�
	* �Լ��� ���ڸ� ���޹޾� blockObject�� setOnMouseCallback()�� �����Ѵ�.
	*/ 
	void setClickCallback(std::function<bool(ObjectPtr, int, int, MouseAction)> callback);
};

// _block�� ���� shared_ptr�� BlockPtr�� ���Ѵ�. 
typedef std::shared_ptr<_block> BlockPtr;