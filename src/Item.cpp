#include "Item.h"

Item::Item(ScenePtr bg, int initLifeCount): background(bg) {

	// 목숨 이미지 생성
	lifeObject.resize(initLifeCount);
	for (int i = 0; i < lifeObject.size(); i++) {
		lifeObject[i] = Object::create(ItemResource::LIFE, background, 1200 - i * 65, 650);
		lifeObject[i]->setScale(0.05f);
	}

	//아이템바 위치 생성
	itemBar = Object::create(ItemResource::ITEM_BAR, background, 340, 0);

	// 현재 사용중인 아이템을 표시
	currentItemIndicator = Object::create(ItemResource::INDICATOR, bg, 340, 0);

	// 아이템 바에서 보여줄 아이템 오브젝트 객체 생성
	itemObject.resize(4);
	itemObject[0] = Object::create(ItemResource::PICKAX, background, 350, 10);
	itemObject[1] = Object::create(ItemResource::FLAG, background, 450, 10);
	itemObject[2] = Object::create(ItemResource::DETECTOR, background, 555, 10, false);
	itemObject[3] = Object::create(ItemResource::SPRAY, background, 670, 10, false);

	// 아이템들의 개수 배열 초기화
	itemCount.resize(4);
	itemCount[0] = INFINITE;
	itemCount[1] = INFINITE;
	itemCount[2] = 0;
	itemCount[3] = 0;
	itemCountOnject.resize(4);
	for (int i = 0; i < itemCount.size(); i++) {
		itemCountOnject[i] = Object::create(ItemResource::EMPTY, background, 400 + (103 * i), 7, false);
	}

	// 아이템 객체에 대한 키보드 콜백
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

	// 아이템 객체들에 대한 마우스 콜백
	for (int i = 0; i < itemObject.size(); i++) {
		itemObject[i]->setOnMouseCallback([=](auto, auto, auto, auto)->bool {
			ChangeHandByIndex(i);
			return true;
			});
	}

	// 스프레이 사용 여부를 표시하는 오브젝트
	sprayUsedIndicator = Object::create(ItemResource::SPRAY, background, 1210, 570, false);
	sprayUsedIndicator->setScale(0.8f);
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
		SelectSpray();
		break;
	default:
		break;
	}
}

void Item::ChangeHand(Hand hand) {
	int index = getItemIndex(hand);
	ChangeHandByIndex(index);
}

void Item::UseDetector(int clickedCellRow, int clickedCellCol, std::vector<std::vector<CellPtr>>& cells, MineField& field) {
	if (getItemCount(Hand::Detector) <= 0) {
		return;
	}
	// 클릭한 칸의 주위 9칸을 확인
	for (int i = clickedCellRow - 1; i <= clickedCellRow + 1; i++) {
		if (i < 0 || i >= cells.size()) {
			continue;
		}
		for (int j = clickedCellCol - 1; j <= clickedCellCol + 1; j++) {
			if (j < 0 || j >= cells[0].size()) {
				continue;
			}
			switch (field[i][j].cellValue) {
			case CellValue::Mine:
				cells[i][j]->getBlock()->ChangeToFlagImage();
				break;
			default:
				cells[i][j]->BreakBlock();
				break;
			}
		}
	}
	ReduceItem(Hand::Detector);
	ChangeHand(Hand::Pickax);
}

void Item::SelectSpray() {
	// 스프레이는 중복 사용할 수 없다. 
	if (itemCount[getItemIndex(Hand::Spray)] <= 0 || isSprayUsed == true) {
		return;
	}
	showMessage("스프레이 하나를 사용했습니다!");
	isSprayUsed = true;
	sprayUsedIndicator->show();
	// 사용 즉시 아이템 창에서는 개수 -1
	ReduceItem(Hand::Spray);
	ChangeHand(Hand::Pickax);
}

void Item::UseSpray() {
	isSprayUsed = false;
	sprayUsedIndicator->hide();
}

bool Item::getIsSprayUsed() {
	return isSprayUsed;
}



int Item::getItemCount(Hand hand) {
	int index = getItemIndex(hand);
	return itemCount[index];
}

void Item::refreshCountImage(int itemIndex) {
	itemCountOnject[itemIndex]->show();
	itemObject[itemIndex]->show();
	switch (itemCount[itemIndex]) {
	// 해당 아이템의 개수가 0이라면 아이템과 개수 숫자를 숨김
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
	// 무한대를 개수로 갖는 아이템
	if (itemCount[index] == INFINITE) {
		return;
	}
	// 0개 이상의 개수를 갖는 아이템
	else if (itemCount[index] > 0) {
		itemCount[index]--;
		refreshCountImage(index);
	}
}

void Item::AddItem(ItemValue itemValue) {
	int index;

	switch (itemValue)	{
	case ItemValue::AddLife:
		AddLifeCount();
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

void Item::ReduceLifeCount() {
	if (lifeObject.size() > 0) {
		lifeObject.back()->hide();
		lifeObject.pop_back();
	}
}

void Item::AddLifeCount() {
	if (lifeObject.size() < 19) {
		lifeObject.push_back(Object::create(ItemResource::LIFE, background, 1200 - lifeObject.size() * 65, 650));
		lifeObject.back()->setScale(0.05f);
	}
}

int Item::getLifeCount() {
	return lifeObject.size();
}
