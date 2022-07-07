#pragma once

#include <string>


class Define final {
public:
	const static int WIN_W;	//ウィンドウサイズ横
	const static int WIN_H;	//ウィンドウサイズ縦

	const static int MAP_SIZE; //マップのサイズ

	enum eMapType {
		wall,
		road,
		start,
		goal,

		eMapTypeNum
	};
};