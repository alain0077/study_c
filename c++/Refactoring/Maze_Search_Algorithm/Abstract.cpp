#include "Abstract.h"

using namespace std;

Abstract::Abstract(Map_Info map) : _map(map), _now_dict(0), _end_flag(false), _turn(0)
{
	_coor = map.start;
}

bool Abstract::loop()
{
	if (_end_flag) {
		return false;
	}
	else {
		update();
		draw();
	}

	return true;
}