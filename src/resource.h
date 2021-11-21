/*
* resource.h
*
* 게임 내에서 사용할 모든 외부 리소스들을 게임 내부의 변수와 연결하는 헤더.
* 코드 내에서는 오직 아래에 새로 정의된 변수 명을 사용해야 하고
* 외부의 리소스를 가리켜서는 안된다.
*/

#pragma once

namespace TitleResource {
	constexpr auto TITLE = "image/Background/Title.png";
	constexpr auto START_BUTTON = "image/script/stage1_start.png";

	constexpr auto TITLE_MUSIC = "music/Title.mp3";
}

namespace EndingResource {
	constexpr auto HAPPY_END = "image/Background/Ending1.png";
	constexpr auto BAD_END = "image/Background/Ending2.png";

	constexpr auto END_BUTTON = "image/script/end.png";

	constexpr auto HAPPY_END_MUSIC = "music/HappyEnding.mp3";
	constexpr auto BAD_END_MUSIC = "music/BadEnding.mp3";
}

namespace ScriptResource {
	constexpr auto SCRIPT_BACKGROUND_1 = "image/script/stage1_clear.PNG";
	constexpr auto SCRIPT_BACKGROUND_2 = "image/script/stage2_clear.PNG";
	constexpr auto SCRIPT_BACKGROUND_3 = "image/script/stage3_clear.PNG";

	constexpr auto SCRIPT_IMAGE_1 = "image/script/stage1_start.png";
	constexpr auto SCRIPT_IMAGE_2 = "image/script/stage2_start.png";
	constexpr auto SCRIPT_IMAGE_3 = "image/script/stage3_start.png";

	constexpr auto SCRIPT_MUSIC_1 = "music/Stage1Script.mp3";
	constexpr auto SCRIPT_MUSIC_2 = "music/Stage2Script.mp3";
	constexpr auto SCRIPT_MUSIC_3 = "music/Stage3Script.mp3";
}

namespace BoardResource {
	constexpr auto BACKGROUND1 = "image/Background/Background1.png";
	constexpr auto BACKGROUND2 = "image/Background/Background2.png";
	constexpr auto BACKGROUND3 = "image/Background/Background3.png";

	constexpr auto ESCAPE_BUTTON = "image/ButtonUI/ExcapeButton.png";

	constexpr auto MUTE_BUTTON = "image/ButtonUI/Sound_Off.png";
	constexpr auto UNMUTE_BUTTON = "image/ButtonUI/Sound_On.png";

	constexpr auto BOARD_MUSIC_1 = "music/Stage1Board.mp3";
	constexpr auto BOARD_MUSIC_2 = "music/Stage2Board.mp3";
	constexpr auto BOARD_MUSIC_3 = "music/Stage3Board.mp3";
	constexpr auto CLEAR_MUSIC = "music/Clear.mp3";
}

namespace CellResource {
	constexpr auto MINE = "image/Cell/Mine.png";
	constexpr auto ESCAPE = "image/Cell/Escape.png";

	constexpr auto EMPTY = "image/Cell/Empty.png";
	constexpr auto ONE = "image/Cell/1.png";
	constexpr auto TWO = "image/Cell/2.png";
	constexpr auto THREE = "image/Cell/3.png";
	constexpr auto FOUR = "image/Cell/4.png";
	constexpr auto FIVE = "image/Cell/5.png";
	constexpr auto SIX = "image/Cell/6.png";
	constexpr auto SEVEN = "image/Cell/7.png";
	constexpr auto EIGHT = "image/Cell/8.png";
}

namespace BlockResource {
	constexpr auto BLOCK1 = "image/Block/BlockEmpty_1.png";
	constexpr auto FLAG1 = "image/Block/BlockFlag_1.png";
	constexpr auto BLOCK2 = "image/Block/BlockEmpty_2.png";
	constexpr auto FLAG2 = "image/Block/BlockFlag_2.png";
	constexpr auto BLOCK3 = "image/Block/BlockEmpty_3.png";
	constexpr auto FLAG3 = "image/Block/BlockFlag_3.png";

	constexpr auto BREAK_SOUND = "music/BreakingBlock.mp3";
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

	constexpr auto EMPTY = "image/Cell/Empty.png";
	constexpr auto ONE = "image/Item_number/1.png";
	constexpr auto TWO = "image/Item_number/2.png";
	constexpr auto THREE = "image/Item_number/3.png";
	constexpr auto FOUR = "image/Item_number/4.png";
	constexpr auto FIVE = "image/Item_number/5.png";
	constexpr auto SIX = "image/Item_number/6.png";
	constexpr auto SEVEN = "image/Item_number/7.png";
	constexpr auto EIGHT = "image/Item_number/8.png";

	constexpr auto CHANGE_SOUND = "music/ChangingItem.mp3";
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
		constexpr auto ROCK = "image/Rock.png";
		constexpr auto PAPER = "image/Paper.png";
		constexpr auto SCISSOR = "image/Scissors.png";
		constexpr auto OPPORTUNITY = "image/Heart.png";
	}

	namespace DiceRolling {
		constexpr auto BUTTON = "image/DiceRollButton.png";
		constexpr auto OPPORTUNITY = "image/Heart.png";

		constexpr auto ONE = "image/Dice1.png";
		constexpr auto TWO = "image/Dice2.png";
		constexpr auto THREE = "image/Dice3.png";
		constexpr auto FOUR = "image/Dice4.png";
		constexpr auto FIVE = "image/Dice5.png";
		constexpr auto SIX = "image/Dice6.png";
	}
	namespace OddOrEven {
		constexpr auto OPPORTUNITY = "image/Heart.png";

		constexpr auto ONE = "image/Dice1.png";
		constexpr auto TWO = "image/Dice2.png";
		constexpr auto THREE = "image/Dice3.png";
		constexpr auto FOUR = "image/Dice4.png";
		constexpr auto FIVE = "image/Dice5.png";
		constexpr auto SIX = "image/Dice6.png";

		constexpr auto ODD_BUTTON = "image/OddButton.png";
		constexpr auto EVEN_BUTTON = "image/EvenButton.png";
	}

	namespace ShootTheMonster {
		constexpr auto PISTOL = "image/Pistol.png";
		constexpr auto OPPORTUNITY = "image/Bullet.png";
		constexpr auto EXPLODE = "image/Explode.png";
	}

	namespace DiceMatching {
		constexpr auto OPPORTUNITY = "image/Heart.png";

		constexpr auto ONE = "image/Dice1.png";
		constexpr auto TWO = "image/Dice2.png";
		constexpr auto THREE = "image/Dice3.png";
		constexpr auto FOUR = "image/Dice4.png";
		constexpr auto FIVE = "image/Dice5.png";
		constexpr auto SIX = "image/Dice6.png";
	}
}



