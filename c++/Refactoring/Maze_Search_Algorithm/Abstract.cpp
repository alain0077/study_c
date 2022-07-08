#include "Abstract.h"

using namespace std;

Abstract::Abstract(vector<vector<int>> _map, int start_x, int start_y, int end_x, int end_y) : _map(_map),
x(start_x), y(start_y), start_x(start_x), start_y(start_y), end_x(end_x), end_y(end_y), now_dict(0), end_flag(false), turn(0)
{
}

bool Abstract::loop()
{
	if (end_flag) {
		return false;
	}
	else {
		update();
		draw();
	}

	return true;
}