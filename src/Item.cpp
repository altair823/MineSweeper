#include "Item.h"

Item::Item(ScenePtr bg, int initLifeCount): background(bg), lifeCount(initLifeCount) {

	//아이템바 위치 생성
	itemBar = Object::create(ItemResource::ITEM_BAR, background, 340, 0);

	// 현재 사용중인 아이템을 표시
	currentItemIndicator = Object::create(ItemResource::INDICATOR, bg, 340, 0);
	
	ObjectPtr pickax = Object::create(ItemResource::PICKAX, background, 350, 10);
	ObjectPtr flag = Object::create(ItemResource::FLAG, background, 450, 10);
	ObjectPtr detector = Object::create(ItemResource::DETECTOR, background, 555, 10, false);
	ObjectPtr spray = Object::create(ItemResource::SPRAY, background, 670, 10, false);

	itemObject.push_back(pickax);
	itemObject.push_back(flag);
	itemObject.push_back(detector);
	itemObject.push_back(spray);

	itemCount.resize(4);
	itemCount[0] = -1;
	itemCount[1] = -1;
	itemCount[2] = 0;
	itemCount[3] = 0;

	itemCountOnject.resize(4);
	for (int i = 0; i < itemCount.size(); i++) {
		itemCountOnject[i] = Object::create(ItemResource::EMPTY, background, 400 + (103 * i), 7, false);
	}

	// 아이템 객체에 대한 키보드 콜백
	background->setOnKeyboardCallback([&](auto bg, auto KeyCode, auto pressed)->bool {
		if (KeyCode == KeyCode::KEY_1 && pressed == true) {
			ChangeHand(0);
		}
		else if (KeyCode == KeyCode::KEY_2 && pressed == true) {
			ChangeHand(1);
		}
		else if (KeyCode == KeyCode::KEY_3 && pressed == true) {
			ChangeHand(2);
		}
		else if (KeyCode == KeyCode::KEY_4 && pressed == true) {
			ChangeHand(3);
		}
		else if (KeyCode == KeyCode::KEY_5 && pressed == true) {
			ChangeHand(4);
		}
		else if (KeyCode == KeyCode::KEY_6 && pressed == true) {
			ChangeHand(5);
		}
		return true;
		});

	// 아이템 객체들에 대한 마우스 콜백
	for (int i = 0; i < itemObject.size(); i++) {
		itemObject[i]->setOnMouseCallback([=](auto, auto, auto, auto)->bool {
			ChangeHand(i);
			return true;
			});
	}
}

Hand Item::getHand() {
	return hand;
}

int Item::getItemIndex(Hand hand) {
	switch (hand) {
	case Hand::Pickax:
		return 0;
	case Hand::Flag:
		return 1;
	case Hand::Detector:
		return 2;
	case Hand::Spray:
		return 3;
	default:
		return 4;
	}
}

void Item::ChangeHand(int index) {
	currentItemIndicator->locate(background, 340 + (103 * index), 0);
	switch (index) {
	case 0:
		hand = Hand::Pickax;
		break;
	case 1:
		hand = Hand::Flag;
		break;
	case 2:
		hand = Hand::Detector;
		break;
	case 3:
		hand = Hand::Spray;
		break;
	default:
		break;
	}
}

int Item::getItemCount(Hand hand) {
	int index = getItemIndex(hand);
	return itemCount[index];
}

void Item::refreshCountImage(int index) {
	itemCountOnject[index]->show();
	switch (itemCount[index]) {
	case 0:
		itemCountOnject[index]->hide();
		break;
	case 1:
		itemCountOnject[index]->setImage(ItemResource::ONE);
		break;
	case 2:
		itemCountOnject[index]->setImage(ItemResource::TWO);
		break;
	case 3:
		itemCountOnject[index]->setImage(ItemResource::THREE);
		break;
	case 4:
		itemCountOnject[index]->setImage(ItemResource::FOUR);
		break;
	case 5:
		itemCountOnject[index]->setImage(ItemResource::FIVE);
		break;
	case 6:
		itemCountOnject[index]->setImage(ItemResource::SIX);
		break;
	case 7:
		itemCountOnject[index]->setImage(ItemResource::SEVEN);
		break;
	case 8:
		itemCountOnject[index]->setImage(ItemResource::EIGHT);
		break;
	default:
		break;
	}
}

void Item::ReduceItem(Hand hand) {
	int index = getItemIndex(hand);

	if (itemCount[index] > 0) {
		itemCount[index]--;
		refreshCountImage(index);
	}

	// 디버그용
	std::cout << "Number of Item: " << itemCount[index] << std::endl;
}

void Item::refreshLifeCountImage() {

}

void Item::AddItem(ItemValue itemValue) {
	int index;

	switch (itemValue)	{
	case AddLife:
		lifeCount++;
		refreshLifeCountImage();
		return;
	case MineDetector:
		index = getItemIndex(Hand::Detector);
		break;
	case AvoidCombat:
		index = getItemIndex(Hand::Spray);
		break;
	default:
		break;
	}

	// 만약 해당 아이템을 한번도 획득한 적이 없다면
	// itemCount의 해당 아이템 자리를 만들어야 한다. 
	if (itemCount.size() <= index) {
		itemCount.resize(index);
	}

	// 만약 해당 아이템이 현재 0개라면
	// 보이게 만든다음 숫자 +1
	if (itemCount[index] == 0) {
		itemObject[index]->show();
	}
	itemCount[index]++;

	refreshCountImage(index);
}