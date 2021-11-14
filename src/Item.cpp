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

int Item::getHandIndex(Hand hand) {
	if (hand == Hand::Pickax) {
		return 0;
	}
	else if (hand == Hand::Flag) {
		return 1;
	}
	else if (hand == Hand::Tnt) {
		return 2;
	}
	else if (hand == Hand::Heart) {
		return 3;
	}
	else if (hand == Hand::Spray) {
		return 4;
	}
	// 빈손이면 5을 반환한다.
	return 5;
}

void Item::ChangeHand(int index) {
	nowUsing->locate(background, 340 + (100 * index), 0);
	if (index == 0) {
		hand = Hand::Pickax;
	}
	if (index == 1) {
		hand = Hand::Flag;
	}
	if (index == 2) {
		hand = Hand::Tnt;
	}
	if (index == 3) {
		hand = Hand::Heart;
	}
	if (index == 4) {
		hand = Hand::Spray;
	}
	if (index == 5) {
		hand = Hand::None;
	}
}

int Item::getItemNumber(Hand hand) {
	int index = getHandIndex(hand);

	return itemNumber[index];
}

void Item::ChangeNumberImage(int index) {
	if (itemNumber[index] == 0) {
		numObject[index]->setImage(CellResource::EMPTY);
	}
	else if (itemNumber[index] == 1) {
		numObject[index]->setImage(CellResource::ONE);
	}
	else if (itemNumber[index] == 2) {
		numObject[index]->setImage(CellResource::TWO);
	}
	else if (itemNumber[index] == 3) {
		numObject[index]->setImage(CellResource::THREE);
	}
}

void Item::ReduceItem(Hand hand) {
	int index = getHandIndex(hand);

	if (itemNumber[index] > 0) {
		itemNumber[index]--;
		ChangeNumberImage(index);
	}

	// 디버그용
	std::cout << "Number of Item: " << itemNumber[index] << std::endl;
}

void Item::AddItem(Hand hand) {
	int index = getHandIndex(hand);

	if (itemNumber[index] >= 0 && itemNumber[index] < 3) {
		itemNumber[index]++;
		ChangeNumberImage(index);
	}

	// 디버그용
	std::cout << "Number of Item: " << itemNumber[index] << std::endl;
}