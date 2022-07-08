#pragma once

#include <DxLib.h>
#include <vector>
#include <random>
#include "Define.h"

struct Coor {
	int x;
	int y;
	int depth;
	int dict;
	int cost;
	// manhattan distance
	int man_d;
};

struct Map_Info {
	Coor start;
	Coor end;
	std::vector<std::vector<int>> map;
};

class Map
{
public:
	Map();
	~Map() = default;
	bool CreatMap(int mode = 0);
	Map_Info getMap() { return { _start, _end, _map }; }

private:
	int _seed;
	Coor _start;
	Coor _end;

	std::vector<std::vector<int>> _map;

	int GetRandom(int min, int max);
};