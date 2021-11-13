#include "Item.h"

Item::Item(ScenePtr bg) {
	background = bg;

	//�����۹� ��ġ ����
	itemBar = Object::create(HandResource::ITEMBAR, bg, 340, 0);
	
	// ������ ������ ���ڷ� ǥ��
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

	// ���� ������� �������� ǥ��
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
