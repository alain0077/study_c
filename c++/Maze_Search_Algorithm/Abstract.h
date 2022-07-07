#pragma once

#include <DxLib.h>
#include <vector>
#include "Define.h"

class Abstract
{
public:
	Abstract(std::vector<std::vector<int>> _map, int start_x, int start_y, int end_x, int end_y);
	~Abstract() = default;
	bool loop();
	virtual void update() = 0;
	virtual void draw() const = 0;
	virtual void finalize() = 0;

	enum eDict {
		right,
		up,
		left,
		down,

		dict_num
	};

protected:
	// map
	std::vector<std::vector<int>> _map;

	// start coordinates
	int start_x;
	int start_y;

	// end coordinates
	int end_x;
	int end_y;

	// searching coordinates
	int x;
	int y;

	// searching direction
	int now_dict;

	// end flag
	bool end_flag;

	// required turn for saerch
	int turn;
};