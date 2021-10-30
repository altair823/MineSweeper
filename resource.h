/*
* resource.h
* 
* 게임 내에서 사용할 모든 외부 리소스들을 게임 내부의 변수와 연결하는 헤더. 
* 코드 내에서는 오직 아래에 새로 정의된 변수 명을 사용해야 하고
* 외부의 리소스를 가리켜서는 안된다. 
*/

#pragma once

namespace BoardResource {
	constexpr auto BACKGROUND = "image/BackgroundTest.png";
}

namespace CellResource {
	constexpr auto NORMAL = "image/CellNormal.png";
	constexpr auto MINE = "image/CellMine.png";
}