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
	constexpr auto START_BUTTON = "image/ButtonUI/StartGame.png";
	constexpr auto HOW_TO_BUTTON = "image/ButtonUI/HowToPlay.png";

	constexpr auto TITLE_MUSIC = "music/Title.mp3";
}

namespace GuideResource {
	constexpr auto BACKGROUND = "image/Background/GuideBackground.png";

	constexpr auto GUIDE_PAGE_1 = "image/HowToPlay/HowToPlay1.png";
	constexpr auto GUIDE_PAGE_2 = "image/HowToPlay/HowToPlay2.png";
	constexpr auto GUIDE_PAGE_3 = "image/HowToPlay/HowToPlay3.png";

	constexpr auto PREVIOUS_PAGE = "image/ButtonUI/howtoplay_left.png";
	constexpr auto NEXT_PAGE = "image/ButtonUI/howtoplay_right.png";
	constexpr auto CLOSE_GUIDE = "image/ButtonUI/howtoplay_exit.png";
}

namespace EndingResource {
	constexpr auto HAPPY_END = "image/Background/Ending1.png";
	constexpr auto BAD_END = "image/Background/Ending2.png";

	constexpr auto END_BUTTON = "image/ButtonUI/GoToExit.png";
	constexpr auto GO_TO_TITLE_BUTTON = "image/ButtonUI/GoToTitle.png";

	constexpr auto HAPPY_END_MUSIC = "music/HappyEnding.mp3";
	constexpr auto BAD_END_MUSIC = "music/BadEnding.mp3";
}

namespace ScriptResource {
	constexpr auto BACKGROUND_1 = "image/script/Script1.png";
	constexpr auto BACKGROUND_2 = "image/script/Script2.png";
	constexpr auto BACKGROUND_3 = "image/script/Script3.png";

	constexpr auto SCRIPT_IMAGE_1 = "image/script/stage1_start.png";
	constexpr auto SCRIPT_IMAGE_2 = "image/script/stage2_start.png";
	constexpr auto SCRIPT_IMAGE_3 = "image/script/stage3_start.png";

	constexpr auto NEXT_BUTTON = "image/ButtonUI/GoToStage.png";

	constexpr auto SCRIPT_MUSIC_1 = "music/Stage1Script.mp3";
	constexpr auto SCRIPT_MUSIC_2 = "music/Stage2Script.mp3";
	constexpr auto SCRIPT_MUSIC_3 = "music/Stage3Script.mp3";
}

namespace BoardResource {
	constexpr auto BACKGROUND1 = "image/Background/Background1.png";
	constexpr auto BACKGROUND2 = "image/Background/Background2.png";
	constexpr auto BACKGROUND3 = "image/Background/Background3.png";

	constexpr auto ESCAPE_BUTTON = "image/ButtonUI/ExcapeButton.png";

	constexpr auto MUTE_BUTTON = "image/ButtonUI/Sound_On.png";
	constexpr auto UNMUTE_BUTTON = "image/ButtonUI/Sound_Off.png";

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
	constexpr auto LIFE = "image/Item/Item_Heart.png";
	constexpr auto INDICATOR = "image/Item/ItemBox_using.png";
	constexpr auto ITEM_BAR = "image/Item/ItemBox.png";
	constexpr auto PICKAX = "image/Item/Item_Pickax.png";
	constexpr auto FLAG = "image/Item/Item_Flag.png";
	constexpr auto DETECTOR = "image/Item/MineDetector.png";
	constexpr auto SPRAY = "image/Item/Item_Spray.png";
	constexpr auto ADD_LIFE = "image/Item/Item_Heartplus.png";

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
	constexpr auto BACKGROUND1 = "image/Combat/CombatBackground1.jpg";
	constexpr auto BACKGROUND2 = "image/Combat/CombatBackground2.jpg";
	constexpr auto BACKGROUND3 = "image/Combat/CombatBackground3.jpg";

	constexpr auto MONSTER1 = "image/Combat/Monster1.png";
	constexpr auto MONSTER2 = "image/Combat/Monster2.png";
	constexpr auto MONSTER3 = "image/Combat/Monster3.png";
	constexpr auto MONSTER4 = "image/Combat/Monster4.png";
	constexpr auto MONSTER5 = "image/Combat/Monster5.png";
	constexpr auto MONSTER6 = "image/Combat/Monster6.png";

	namespace RockPaperScissor {
		constexpr auto ROCK = "image/Combat/Rock.png";
		constexpr auto PAPER = "image/Combat/Paper.png";
		constexpr auto SCISSOR = "image/Combat/Scissors.png";
		constexpr auto OPPORTUNITY = "image/Combat/Heart.png";
	}

	namespace DiceRolling {
		constexpr auto BUTTON = "image/Combat/DiceRollButton.png";
		constexpr auto OPPORTUNITY = "image/Combat/Heart.png";

		constexpr auto ONE = "image/Combat/Dice1.png";
		constexpr auto TWO = "image/Combat/Dice2.png";
		constexpr auto THREE = "image/Combat/Dice3.png";
		constexpr auto FOUR = "image/Combat/Dice4.png";
		constexpr auto FIVE = "image/Combat/Dice5.png";
		constexpr auto SIX = "image/Combat/Dice6.png";
	}
	namespace OddOrEven {
		constexpr auto OPPORTUNITY = "image/Combat/Heart.png";

		constexpr auto ONE = "image/Combat/Dice1.png";
		constexpr auto TWO = "image/Combat/Dice2.png";
		constexpr auto THREE = "image/Combat/Dice3.png";
		constexpr auto FOUR = "image/Combat/Dice4.png";
		constexpr auto FIVE = "image/Combat/Dice5.png";
		constexpr auto SIX = "image/Combat/Dice6.png";

		constexpr auto ODD_BUTTON = "image/Combat/OddButton.png";
		constexpr auto EVEN_BUTTON = "image/Combat/EvenButton.png";
	}

	namespace ShootTheMonster {
		constexpr auto PISTOL = "image/Combat/Pistol.png";
		constexpr auto OPPORTUNITY = "image/Combat/Bullet.png";
		constexpr auto EXPLODE = "image/Combat/Explode.png";
	}

	namespace DiceMatching {
		constexpr auto OPPORTUNITY = "image/Combat/Heart.png";

		constexpr auto ONE = "image/Combat/Dice1.png";
		constexpr auto TWO = "image/Combat/Dice2.png";
		constexpr auto THREE = "image/Combat/Dice3.png";
		constexpr auto FOUR = "image/Combat/Dice4.png";
		constexpr auto FIVE = "image/Combat/Dice5.png";
		constexpr auto SIX = "image/Combat/Dice6.png";
	}
}



