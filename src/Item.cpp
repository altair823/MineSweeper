#include "Item.h"

Item::Item(ScenePtr bg) {
	background = bg;

	//아이템바 위치 생성
	itemBar = Object::create(HandResource::ITEMBAR, bg, 340, 0);
	
	// 아이템 개수를 숫자로 표현
	for (int i = 0; i < 6; i++) {
		if (itemNumber[i] == -1) {
			numObject[i] = Object::create(CellResource::MINE, bg, 400 + (100 * i), 7);
		}
		else if (itemNumber[i] == 0) {
			numObject[i] = Object::create(CellResource::EMPTY, bg, 400 + (100 * i), 7);
		}
		else if (itemNumber[i] == 1) {
			numObject[i] = Object::create(CellResource::ONE, bg, 400 + (100 * i), 7);
		}
		else if (itemNumber[i] == 2) {
			numObject[i] = Object::create(CellResource::TWO, bg, 400 + (100 * i), 7);
		}
		else if (itemNumber[i] == 3) {
			numObject[i] = Object::create(CellResource::THREE, bg, 400 + (100 * i), 7);
		}
	}

	// 현재 사용중인 아이템을 표시
	nowUsing = Object::create(HandResource::USING, bg, 340, 0);
}

Hand Item::getHand() {
	return hand;
}

void Item::ChangeHand(int n) {
	nowUsing->locate(background, 340 + (100 * n), 0);
	if (n == 0) {
		hand = Hand::Pickax;
	}
	if (n == 1) {
		hand = Hand::Flag;
	}
}
