#include "Block.h"

std::shared_ptr<_block> Block::Create(ScenePtr bg, int x, int y) {
	// ���ο� ĭ ��ü ����
	std::shared_ptr<_block> newBlock(new _block(bg, x, y));
	return newBlock;
}

_block::_block(ScenePtr bg, int x, int y) {
	blockObject = Object::create(BlockResource::BLOCK, bg, x, y);

	// blockObject->hide(); //����׿�
	isFlagImage = false;
}

void _block::ChangeFlagImage() {
	if (isFlagImage) {
		return;
	}
	blockObject->setImage(BlockResource::FLAG);
	isFlagImage = true;
}

void _block::ChangeEmptyBlockImage() {
	if (~isFlagImage) {
		return;
	}
	blockObject->setImage(BlockResource::BLOCK);
	isFlagImage = false;
}

void _block::ChangeBlockImage() {
	if (isFlagImage) {
		blockObject->setImage(BlockResource::BLOCK);
		isFlagImage = false;
	}
	else {
		blockObject->setImage(BlockResource::FLAG);
		isFlagImage = true;
	}
}

bool _block::HideBlock() {
	if (isFlagImage) {
		return false;
	}
	blockObject->hide();
	return true;
}

void _block::setClickCallback(std::function<bool(ObjectPtr, int, int, MouseAction)> callback) {
	blockObject->setOnMouseCallback(callback);
}