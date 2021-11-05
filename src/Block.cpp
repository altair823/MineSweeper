#include "Block.h"

std::shared_ptr<_block> Block::Create(ScenePtr bg, int x, int y)
{
	// x, y의 좌표를 계산하지 않고 Cell의 좌표를 그대로 받아 사용한다.
	//int x = (col + 1) * CELL_SIZE + 100;
	//int y = -(row + 1) * CELL_SIZE + 420;


	// 새로운 칸 객체 생성
	std::shared_ptr<_block> newBlock(new _block(bg, x, y));
	return newBlock;
}

_block::_block(ScenePtr bg, int x, int y) {
	blockObject = Object::create(BlockResource::BLOCK, bg, x, y);
	blockObject->hide(); //디버그용
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