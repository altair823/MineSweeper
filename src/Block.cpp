#include "Block.h"

std::shared_ptr<_block> Block::Create(ScenePtr bg, int x, int y, int stageNum) {
	// 새로운 칸 객체 생성
	std::shared_ptr<_block> newBlock(new _block(bg, x, y, stageNum));
	return newBlock;
}

_block::_block(ScenePtr bg, int x, int y, int stageNum) : stageNum(stageNum) {
	switch (this->stageNum){
	case 0:
		blockObject = Object::create(BlockResource::BLOCK1, bg, x, y);
		break;
	case 1:
		blockObject = Object::create(BlockResource::BLOCK2, bg, x, y);
		break;
	case 2:
		blockObject = Object::create(BlockResource::BLOCK3, bg, x, y);
		break;
	default:
		break;
	}

	// blockObject->hide(); //디버그용
	isFlagImage = false;
}

void _block::ChangeToFlagImage() {
	if (isFlagImage) {
		return;
	}
	switch (stageNum) {
	case 0:
		blockObject->setImage(BlockResource::FLAG1);
		break;
	case 1:
		blockObject->setImage(BlockResource::FLAG2);
		break;
	case 2:
		blockObject->setImage(BlockResource::FLAG3);
		break;
	default:
		break;
	}
	isFlagImage = true;
}

void _block::ChangeToEmptyBlockImage() {
	if (!isFlagImage) {
		return;
	}
	switch (stageNum) {
	case 0:
		blockObject->setImage(BlockResource::BLOCK1);
		break;
	case 1:
		blockObject->setImage(BlockResource::BLOCK2);
		break;
	case 2:
		blockObject->setImage(BlockResource::BLOCK3);
		break;
	default:
		break;
	}
	isFlagImage = false;
}

void _block::SwapBlockImage() {
	if (isFlagImage) {
		ChangeToEmptyBlockImage();
	}
	else {
		ChangeToFlagImage();
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