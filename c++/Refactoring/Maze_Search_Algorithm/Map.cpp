#include "Map.h"

using namespace std;

Map::Map() :
	_seed(0),
	_start({ 0, 0 }),
	_end({ 0, 0 })
{
	vector<int> n;

	for (int i = 0; i < Define::MAP_SIZE; i++) {

		_map.push_back(n);

		for (int j = 0; j < Define::MAP_SIZE; j++) {
			_map.at(i).push_back(Define::eMapType::road);
		}
	}

	for (int i = 1; i < Define::MAP_SIZE - 1; i++) {
		for (int j = 1; j < Define::MAP_SIZE - 1; j++) {
			_map.at(i).at(j) = Define::eMapType::wall;
		}
	}

	_start = { GetRandom(1, 10) * 2, GetRandom(1, 10) * 2 };

	_map.at(_start.x).at(_start.y) = Define::eMapType::road;
}

bool Map::CreatMap(int mode)
{
	bool flag = false;

	while (1)
	{
		vector<int> row;
		vector<int> col;

		while (!row.empty())
		{
			row.pop_back();
		}

		while (!col.empty())
		{
			col.pop_back();
		}

		flag = false;

		for (int i = 2; i < 21; i += 2) {
			for (int j = 2; j < 21; j += 2) {
				if (_map.at(i).at(j) == Define::eMapType::wall) {
					flag = true;
				}
				else {
					row.push_back(i);
					col.push_back(j);
				}
			}
		}

		if (!flag) {
			break;
		}

		int _num = GetRandom(1, row.size()) - 1;

		int _row = row.at(_num);

		int _col = col.at(_num);

		bool _comp = false;

		while (!_comp)
		{
			vector<int> _tmp = { 1,2,3,4 };

			vector<int> dict;

			for (int i = 0; i < 4; i++) {
				if (_tmp.size() == 1) {
					dict.push_back(_tmp[0]);
				}
				else {
					int num = GetRandom(0, _tmp.size() - 1);

					dict.push_back(_tmp[num]);

					_tmp.erase(_tmp.begin() + num);
				}
			}

			while (1)
			{
				bool _flag = false;

				switch (dict[0])
				{
				case 1:
					if (_map.at(_row).at(_col - 2) != Define::eMapType::road) {
						_map.at(_row).at(--_col) = Define::eMapType::road;

						_end = { _row, _col };

						_flag = true;
					}
					else {
						dict.erase(dict.begin());
					}
					break;
				case 2:
					if (_map.at(_row).at(_col + 2) != Define::eMapType::road) {
						_map.at(_row).at(++_col) = Define::eMapType::road;

						_end = { _row, _col };
						
						_flag = true;
					}
					else {
						dict.erase(dict.begin());
					}
					break;
				case 3:
					if (_map.at(_row - 2).at(_col) != Define::eMapType::road) {
						_map.at(--_row).at(_col) = Define::eMapType::road;

						_end = { _row, _col };

						_flag = true;
					}
					else {
						dict.erase(dict.begin());
					}
					break;
				case 4:
					if (_map.at(_row + 2).at(_col) != Define::eMapType::road) {
						_map.at(++_row).at(_col) = Define::eMapType::road;

						_end = { _row, _col };

						_flag = true;
					}
					else {
						dict.erase(dict.begin());
					}
					break;
				}

				if (dict.empty()) {
					_comp = true;
					break;
				}

				if (_flag) {
					break;
				}
			}
		}
	}

	_map.at(_start.x).at(_start.y) = Define::eMapType::start;
	_map.at(_end.x).at(_end.y) = Define::eMapType::goal;

	WaitKey();

	return true;
}

int Map::GetRandom(int min, int max)
{
	if (max == 0) {
		return 0;
	}

	srand(GetNowCount() / (min + max + ++_seed));

	int num = rand();

	uniform_int_distribution<int> dist(min, max);

	mt19937 mt(num);

	num = dist(mt);

	return num;
}