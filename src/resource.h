/*
* resource.h
* 
* 게임 내에서 사용할 모든 외부 리소스들을 게임 내부의 변수와 연결하는 헤더. 
* 코드 내에서는 오직 아래에 새로 정의된 변수 명을 사용해야 하고
* 외부의 리소스를 가리켜서는 안된다. 
*/

#pragma once

namespace BoardResource {
	// 1280*720 화면 크기 테스트용 배경 화면
	constexpr auto BACKGROUND = "image/Background_example3.png";
}

namespace CellResource {
	constexpr auto MINE = "image/CellMine.png";
	constexpr auto ESCAPE = "image/CellEscape.png";

	constexpr auto EMPTY = "image/CellEmpty.png";
	constexpr auto ONE = "image/Cell1.png";
	constexpr auto TWO = "image/Cell2.png";
	constexpr auto THREE = "image/Cell3.png";
	constexpr auto FOUR = "image/Cell4.png";
	constexpr auto FIVE = "image/Cell5.png";
	constexpr auto SIX = "image/Cell6.png";
	constexpr auto SEVEN = "image/Cell7.png";
	constexpr auto EIGHT = "image/Cell8.png";
}

namespace BlockResource {
	constexpr auto BLOCK = "image/BlockEmpty_2.png";
	constexpr auto FLAG = "image/BlockFlag_2.png";
}

namespace ItemResource {
	constexpr auto LIFE = "image/Item_Heart.png";
	constexpr auto INDICATOR = "image/ItemBox_using.png";
	constexpr auto ITEM_BAR = "image/ItemBox.png";
	constexpr auto PICKAX = "image/Item_Pickax.png";
	constexpr auto FLAG = "image/Item_Flag.png";
	constexpr auto DETECTOR = "image/MineDetector.png";
	constexpr auto SPRAY = "image/Item_Spray.png";
	constexpr auto ADD_LIFE = "image/Item_Heartplus.png";

	constexpr auto EMPTY = "image/CellEmpty.png";
	constexpr auto ONE = "image/Item_number/1.png";
	constexpr auto TWO = "image/Item_number/2.png";
	constexpr auto THREE = "image/Item_number/3.png";
	constexpr auto FOUR = "image/Item_number/4.png";
	constexpr auto FIVE = "image/Item_number/5.png";
	constexpr auto SIX = "image/Item_number/6.png";
	constexpr auto SEVEN = "image/Item_number/7.png";
	constexpr auto EIGHT = "image/Item_number/8.png";
}


namespace CombatResource {
	constexpr auto BACKGROUND1 = "image/CombatBackground1.jpg";
	constexpr auto BACKGROUND2 = "image/CombatBackground2.jpg";
	constexpr auto BACKGROUND3 = "image/CombatBackground3.jpg";

	constexpr auto MONSTER1 = "image/Monster1.png";
	constexpr auto MONSTER2 = "image/Monster2.png";
	constexpr auto MONSTER3 = "image/Monster3.png";
	constexpr auto MONSTER4 = "image/Monster4.png";
	constexpr auto MONSTER5 = "image/Monster5.png";
	constexpr auto MONSTER6 = "image/Monster6.png";

	namespace RockPaperScissor {
		constexpr auto Rock = "image/Rock.png";
		constexpr auto Paper = "image/Paper.png";
		constexpr auto Scissor = "image/Scissors.png";
		constexpr auto Opportunity = "image/Heart.png";
	}

	namespace DiceRolling {
		constexpr auto Button = "image/DiceRollButton.png";
		constexpr auto Opportunity = "image/Heart.png";

		constexpr auto One = "image/Dice1.png";
		constexpr auto Two = "image/Dice2.png";
		constexpr auto Three = "image/Dice3.png";
		constexpr auto Four = "image/Dice4.png";
		constexpr auto Five = "image/Dice5.png";
		constexpr auto Six = "image/Dice6.png";
	}
	namespace OddOrEven {
		constexpr auto Opportunity = "image/Heart.png";

		constexpr auto One = "image/Dice1.png";
		constexpr auto Two = "image/Dice2.png";
		constexpr auto Three = "image/Dice3.png";
		constexpr auto Four = "image/Dice4.png";
		constexpr auto Five = "image/Dice5.png";
		constexpr auto Six = "image/Dice6.png";

		constexpr auto OddButton = "image/OddButton.png";
		constexpr auto EvenButton = "image/EvenButton.png";
	}

	namespace ShootTheMonster {
		constexpr auto Pistol = "image/Pistol.png";
		constexpr auto Opportunity = "image/Bullet.png";
		constexpr auto Explode = "image/Explode.png";
	}

	namespace DiceMatching {
		constexpr auto Opportunity = "image/Heart.png";

		constexpr auto One = "image/Dice1.png";
		constexpr auto Two = "image/Dice2.png";
		constexpr auto Three = "image/Dice3.png";
		constexpr auto Four = "image/Dice4.png";
		constexpr auto Five = "image/Dice5.png";
		constexpr auto Six = "image/Dice6.png";
	}
}