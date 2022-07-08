#include "dfs.h"

using namespace std;

DFS::DFS(Map_Info map) : Abstract(map)
{
	_dfs_map = map.map;
	_s.push(map.start);
}

void DFS::update()
{
	if (_map.map.at(_coor.x).at(_coor.y) == Define::eMapType::goal) {
		_end_flag = true;
	}
	else {
		dfs();
	}
}

void DFS::finalize()
{
	Coor start = _map.start, end = _map.end;
	vector<vector<int>> map = _map.map;

	ClearDrawScreen();

	for (int i = 0; i < Define::MAP_SIZE; i++) {
		for (int j = 0; j < Define::MAP_SIZE; j++)
		{
			if (map.at(i).at(j) == Define::eMapType::wall) {
				DrawString(20 + 20 * i, 20 + 20 * j, "¡", GetColor(255, 255, 255));
			}
			else {
				if (i == start.x && j == start.y) {
					DrawString(20 + 20 * i, 20 + 20 * j, "¡", GetColor(255, 0, 0));
				}
				else if (i == end.x && j == end.y) {
					DrawString(20 + 20 * i, 20 + 20 * j, "¡", GetColor(0, 0, 255));
				}
				else
					DrawString(20 + 20 * i, 20 + 20 * j, "  ", GetColor(255, 255, 255));
			}
		}
	}

	while (!_s.empty()) {
		if ((_s.top().x != start.x || _s.top().y != start.y) && (_s.top().x != end.x || _s.top().y != end.y))
			DrawString(20 + 20 * _s.top().x, 20 + 20 * _s.top().y, "¡", GetColor(0, 255, 0));

		_s.pop();
	}

	DrawFormatString(500, 480, GetColor(255, 255, 255), "%d", _turn);
	DrawString(500, 500, "please hit key", GetColor(255, 255, 255));

	ScreenFlip();

	WaitKey();
}

void DFS::dfs()
{
	if (judge_end()) {
		_dfs_map.at(_coor.x).at(_coor.y) = Define::eMapType::eMapTypeNum;

		_s.pop();

		_coor.x = _s.top().x;
		_coor.y = _s.top().y;
	}
	else {
		if (judge_wall(_now_dict)) {
			_now_dict++;
		}
		else {
			_dfs_map.at(_coor.x).at(_coor.y) = Define::eMapType::eMapTypeNum;

			switch (_now_dict)
			{
			case eDict::right:
				_coor.x++;
				break;
			case eDict::up:
				_coor.y--;
				break;
			case eDict::left:
				_coor.x--;
				break;
			case eDict::down:
				_coor.y++;
				break;
			}

			_turn++;

			_s.push({ _coor.x, _coor.y });

			Sleep(100);

			_now_dict = right;
		}
	}
}

bool DFS::judge_wall(int dict) const
{
	int x = _coor.x, y = _coor.y;

	switch (dict)
	{
	case eDict::up:
		if (_dfs_map.at(x).at(y - 1) == Define::eMapType::wall || _dfs_map.at(x).at(y - 1) == Define::eMapType::eMapTypeNum)
			return true;
		break;
	case eDict::down:
		if (_dfs_map.at(x).at(y + 1) == Define::eMapType::wall || _dfs_map.at(x).at(y + 1) == Define::eMapType::eMapTypeNum)
			return true;
		break;
	case eDict::right:
		if (_dfs_map.at(x + 1).at(y) == Define::eMapType::wall || _dfs_map.at(x + 1).at(y) == Define::eMapType::eMapTypeNum)
			return true;
		break;
	case eDict::left:
		if (_dfs_map.at(x - 1).at(y) == Define::eMapType::wall || _dfs_map.at(x - 1).at(y) == Define::eMapType::eMapTypeNum)
			return true;
		break;
	default:
		break;
	}

	return false;
}

bool DFS::judge_end() const
{
	for (int i = 0; i < eDict::dict_num; i++) {
		if (!judge_wall(i)) {
			return false;
		}
	}

	return true;
}

void DFS::draw() const
{
	Coor start = _map.start, end = _map.end;
	vector<vector <int>> map = _map.map;

	for (int i = 0; i < Define::MAP_SIZE; i++) {
		for (int j = 0; j < Define::MAP_SIZE; j++)
		{
			if (map.at(i).at(j) == Define::eMapType::wall) {
				DrawString(20 + 20 * i, 20 + 20 * j, "¡", GetColor(255, 255, 255));
			}
			else {
				if (i == start.x && j == start.y) {
					DrawString(20 + 20 * i, 20 + 20 * j, "¡", GetColor(255, 0, 0));
				}
				else if (i == end.x && j == end.y) {
					DrawString(20 + 20 * i, 20 + 20 * j, "¡", GetColor(0, 0, 255));
				}
				else if (_dfs_map.at(i).at(j) == Define::eMapType::eMapTypeNum) {
					DrawString(20 + 20 * i, 20 + 20 * j, "¡", GetColor(0, 255, 0));
				}
				else {
					DrawString(20 + 20 * i, 20 + 20 * j, "  ", GetColor(255, 255, 255));
				}
			}
		}
	}

	DrawFormatString(480, 480, GetColor(255, 255, 255), "        start:%d,%d", start.x, start.y);
	DrawFormatString(480, 500, GetColor(255, 255, 255), "          end:%d,%d", end.x, end.y);
	DrawFormatString(480, 520, GetColor(255, 255, 255), "now searching:%d,%d", _coor.x, _coor.y);

}