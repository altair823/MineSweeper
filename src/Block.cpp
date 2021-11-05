#include "Block.h"

std::shared_ptr<_block> Block::Create(ScenePtr bg, int x, int y)
{
	// x, y�� ��ǥ�� ������� �ʰ� Cell�� ��ǥ�� �״�� �޾� ����Ѵ�.
	//int x = (col + 1) * CELL_SIZE + 100;
	//int y = -(row + 1) * CELL_SIZE + 420;


	// ���ο� ĭ ��ü ����
	std::shared_ptr<_block> newBlock(new _block(bg, x, y));
	return newBlock;
}

_block::_block(ScenePtr bg, int x, int y) {
	blockObject = Object::create(BlockResource::BLOCK, bg, x, y);
	blockObject->hide(); //����׿�
	isFlagImage = true;
}

void _block::ChangeFlagImage() {
	if (isFlagImage) {
		return;
	}
	blockObject->setImage(BlockResource::FLAG);
	isFlagImage = false;
}

void _block::ChangeEmptyBlockImage() {
	if (~isFlagImage) {
		return;
	}
	blockObject->setImage(BlockResource::BLOCK);
	isFlagImage = true;
}

void _block::hideBlock() {
	blockObject->hide();
}

void _block::setClickCallback(std::function<bool(ObjectPtr, int, int, MouseAction)> callback) {
	blockObject->setOnMouseCallback(callback);
}