#include "AbstractMethod.h"
#include "Define.h"
#include <random>
#include <DxLib.h>

using namespace std;

AbstractMethod::AbstractMethod() : _seed(0)
{
	vector<vector<eMapType>> map(Define::MAX_ROW, vector<eMapType>(Define::MAX_COL, eMapType::wall));
	_map = map;
}


int AbstractMethod::GetRandom(int min, int max)
{
	if (max <= 0) {
		return 0;
	}

	if (min == max) return max;

	if (min > max) return GetRandom(max, min);

	srand(GetNowCount() / (min + max + _seed++));

	mt19937 mt(rand());
	uniform_int_distribution<int> dist(min, max);

	int num = dist(mt);

	return num;

	/*
	int rand;

	random_device rnd;
	mt19937 mt(rnd());
	uniform_int_distribution<> randN(min, max);  //¶¬‚·‚é—”‚Ì’l‚Ì”ÍˆÍ
	rand = randN(mt);

	return rand;
	*/
}

void AbstractMethod::WriteMap(int x1, int y1, int x2, int y2, eMapType type)
{
	if((x1 > x2) || (y1 > y2))
	{
		WriteMap(x2, y2, x1, y1, type);
	}

	for (int i = y1; i < y2 + 1; i++) {
		for (int j = x1; j < x2 + 1; j++) {
			_map[i][j] = type;
		}
	}
}