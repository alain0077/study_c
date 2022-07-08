#pragma once

#include <DxLib.h>
#include <vector>
#include "Define.h"
#include "Map.h"

class Abstract
{
public:
	Abstract(Map_Info map);
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
	Map_Info _map;

	// searching coordinates
	Coor _coor;

	// searching direction
	int _now_dict;

	// end flag
	bool _end_flag;

	// required turn for saerch
	int _turn;
};