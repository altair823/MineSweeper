#include "Item.h"

Item::Item(ScenePtr bg, int initLifeCount): background(bg), lifeCount(initLifeCount) {

	//�����۹� ��ġ ����
	itemBar = Object::create(ItemResource::ITEM_BAR, background, 340, 0);

	// ���� ������� �������� ǥ��
	currentItemIndicator = Object::create(ItemResource::INDICATOR, bg, 340, 0);

	// ������ �ٿ��� ������ ������ ������Ʈ ��ü ����
	itemObject.resize(4);
	itemObject[0] = Object::create(ItemResource::PICKAX, background, 350, 10);
	itemObject[1] = Object::create(ItemResource::FLAG, background, 450, 10);
	itemObject[2] = Object::create(ItemResource::DETECTOR, background, 555, 10, false);
	itemObject[3] = Object::create(ItemResource::SPRAY, background, 670, 10, false);

	// �����۵��� ���� �迭 �ʱ�ȭ
	itemCount.resize(4);
	itemCount[0] = INFINITE;
	itemCount[1] = INFINITE;
	itemCount[2] = 0;
	itemCount[3] = 0;

	itemCountOnject.resize(4);
	for (int i = 0; i < itemCount.size(); i++) {
		itemCountOnject[i] = Object::create(ItemResource::EMPTY, background, 400 + (103 * i), 7, false);
	}

	// ������ ��ü�� ���� Ű���� �ݹ�
	background->setOnKeyboardCallback([&](auto bg, auto KeyCode, auto pressed)->bool {
		if (KeyCode == KeyCode::KEY_1 && pressed == true) {
			ChangeHand(Hand::Pickax);
		}
		else if (KeyCode == KeyCode::KEY_2 && pressed == true) {
			ChangeHand(Hand::Flag);
		}
		else if (KeyCode == KeyCode::KEY_3 && pressed == true) {
			ChangeHand(Hand::Detector);
		}
		else if (KeyCode == KeyCode::KEY_4 && pressed == true) {
			ChangeHand(Hand::Spray);
		}
		else if (KeyCode == KeyCode::KEY_5 && pressed == true) {
			ChangeHandByIndex(4);
		}
		else if (KeyCode == KeyCode::KEY_6 && pressed == true) {
			ChangeHandByIndex(5);
		}
		return true;
		});

	// ������ ��ü�鿡 ���� ���콺 �ݹ�
	for (int i = 0; i < itemObject.size(); i++) {
		itemObject[i]->setOnMouseCallback([=](auto, auto, auto, auto)->bool {
			ChangeHandByIndex(i);
			return true;
			});
	}
}

Hand Item::getCurrentHand() {
	return currentHand;
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

void Item::ChangeHandByIndex(int index) {
	currentItemIndicator->locate(background, 340 + (103 * index), 0);
	switch (index) {
	case 0:
		currentHand = Hand::Pickax;
		break;
	case 1:
		currentHand = Hand::Flag;
		break;
	case 2:
		currentHand = Hand::Detector;
		break;
	case 3:
		currentHand = Hand::Spray;
		break;
	default:
		break;
	}
}

void Item::ChangeHand(Hand hand) {
	int index = getItemIndex(hand);
	ChangeHandByIndex(index);
}

int Item::getItemCount(Hand hand) {
	int index = getItemIndex(hand);
	return itemCount[index];
}

void Item::refreshCountImage(int itemIndex) {
	itemCountOnject[itemIndex]->show();
	itemObject[itemIndex]->show();
	switch (itemCount[itemIndex]) {
	// �ش� �������� ������ 0�̶�� �����۰� ���� ���ڸ� ����
	case 0:
		itemCountOnject[itemIndex]->hide();
		itemObject[itemIndex]->hide();
		break;
	case 1:
		itemCountOnject[itemIndex]->setImage(ItemResource::ONE);
		break;
	case 2:
		itemCountOnject[itemIndex]->setImage(ItemResource::TWO);
		break;
	case 3:
		itemCountOnject[itemIndex]->setImage(ItemResource::THREE);
		break;
	case 4:
		itemCountOnject[itemIndex]->setImage(ItemResource::FOUR);
		break;
	case 5:
		itemCountOnject[itemIndex]->setImage(ItemResource::FIVE);
		break;
	case 6:
		itemCountOnject[itemIndex]->setImage(ItemResource::SIX);
		break;
	case 7:
		itemCountOnject[itemIndex]->setImage(ItemResource::SEVEN);
		break;
	case 8:
		itemCountOnject[itemIndex]->setImage(ItemResource::EIGHT);
		break;
	default:
		break;
	}
}

void Item::ReduceItem(Hand hand) {
	int index = getItemIndex(hand);
	// ���Ѵ븦 ������ ���� ������
	if (itemCount[index] == INFINITE) {
		return;
	}
	// 0�� �̻��� ������ ���� ������
	else if (itemCount[index] > 0) {
		itemCount[index]--;
		refreshCountImage(index);
	}
}

void Item::refreshLifeCountImage() {

}

void Item::AddItem(ItemValue itemValue) {
	int index;

	switch (itemValue)	{
	case ItemValue::AddLife:
		lifeCount++;
		refreshLifeCountImage();
		return;
	case ItemValue::MineDetector:
		index = getItemIndex(Hand::Detector);
		break;
	case ItemValue::AvoidCombat:
		index = getItemIndex(Hand::Spray);
		break;
	default:
		break;
	}

	// ���� �ش� �������� �ѹ��� ȹ���� ���� ���ٸ�
	// itemCount�� �ش� ������ �ڸ��� ������ �Ѵ�. 
	if (itemCount.size() <= index) {
		itemCount.resize(index);
	}

	// ���� �ش� �������� ���� 0�����
	// ���̰� ������� ���� +1
	if (itemCount[index] == 0) {
		itemObject[index]->show();
	}
	itemCount[index]++;

	refreshCountImage(index);
}