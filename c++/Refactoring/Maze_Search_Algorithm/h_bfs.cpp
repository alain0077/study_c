#include "h_bfs.h"
#include <cstdlib>

using namespace std;

// for list sort
bool man_d_comp(H_bfs_Coor& l1, H_bfs_Coor& l2)
{
	if (l1.man_d < l2.man_d) {
		return true;
	}

	return false;
}

H_bfs::H_bfs(Map_Info map) :Abstract(map),
_cost(0)
{
	_map.map.at(_coor.x).at(_coor.y) = _cost + Define::eMapType::eMapTypeNum;
}

void H_bfs::finalize()
{
	ClearDrawScreen();

	int goal_cost = _cost + Define::eMapType::eMapTypeNum;
	int dict = 0;
	Coor start = _map.start, end = _map.end;
	vector<vector<int>> map = _map.map;

	H_bfs_Coor goal = { end.x, end.y,  0, 0, 0 };

	list<H_bfs_Coor> g;

	goal_cost--;

	for (int i = 0; i < Define::MAP_SIZE; i++) {
		for (int j = 0; j < Define::MAP_SIZE; j++)
		{
			if (map.at(i).at(j) == Define::eMapType::wall) {
				DrawString(20 + 20 * i, 20 + 20 * j, "Å°", GetColor(255, 255, 255));
			}
			else {
				if (i == start.x && j == start.y) {
					DrawString(20 + 20 * i, 20 + 20 * j, "Å°", GetColor(255, 0, 0));
				}
				else if (i == end.x && j == end.y) {
					DrawString(20 + 20 * i, 20 + 20 * j, "Å°", GetColor(0, 0, 255));
				}
				else {
					DrawString(20 + 20 * i, 20 + 20 * j, "  ", GetColor(255, 255, 255));
				}
			}
		}
	}


	while (goal_cost != Define::eMapType::eMapTypeNum) {

		dict++;

		switch (dict % eDict::dict_num)
		{
		case right:
			if (map.at(goal.x + 1).at(goal.y) == goal_cost) {
				goal.x++;
				g.push_back(goal);
				goal_cost--;
			}

			break;

		case up:
			if (map.at(goal.x).at(goal.y - 1) == goal_cost) {
				goal.y--;
				g.push_back(goal);
				goal_cost--;
			}

			break;

		case left:
			if (map.at(goal.x - 1).at(goal.y) == goal_cost) {
				goal.x--;
				g.push_back(goal);
				goal_cost--;
			}

			break;

		case down:
			if (map.at(goal.x).at(goal.y + 1) == goal_cost) {
				goal.y++;
				g.push_back(goal);
				goal_cost--;
			}

			break;
		}
	}

	while (!g.empty())
	{
		DrawString(20 + 20 * g.front().x, 20 + 20 * g.front().y, "Å°", GetColor(0, 255, 0));
		g.pop_front();
	}

	DrawFormatString(500, 480, GetColor(255, 255, 255), "%d", _turn);
	DrawString(500, 500, "please hit key", GetColor(255, 255, 255));

	ScreenFlip();

	WaitKey();
}

void H_bfs::update()
{
	if (_coor.x == _map.end.x && _coor.y == _map.end.y) {
		_end_flag = true;
	}
	else {
		bfs();

		int c = 0;

		for (auto itr = _branch.begin(); itr != _branch.end(); itr++) {
			DrawFormatString(480, 100 + 20 * c, GetColor(255, 255, 255), "        man_d:%d", itr->man_d);
			c++;
		}
	}
}

void H_bfs::bfs()
{
	if (judge_road(_now_dict) && !judge_branch()) {
		switch (_now_dict)
		{
		case right:
			_coor.x++;
			break;
		case up:
			_coor.y--;
			break;
		case left:
			_coor.x--;
			break;
		case down:
			_coor.y++;
			break;
		}

		_cost++;
	}
	else if (!judge_road(_now_dict) && !judge_branch()) {
		_coor.x = _branch.front().x;
		_coor.y = _branch.front().y;
		_now_dict = _branch.front().dict;
		_cost = _branch.front().cost;
		_branch.pop_front();
	}
	else {
		for (int i = 0; i < eDict::dict_num; i++) {
			int x = _coor.x, y = _coor.y;

			if (judge_road(i)) {
				switch (i)
				{
				case right:
					_branch.push_back({ x + 1, y, right, _cost + 1, man_d(x + 1, y) });
					break;
				case up:
					_branch.push_back({ x, y - 1, up, _cost + 1, man_d(x, y - 1) });
					break;
				case left:
					_branch.push_back({ x - 1, y, left, _cost + 1, man_d(x - 1, y) });
					break;
				case down:
					_branch.push_back({ x, y + 1, down, _cost + 1, man_d(x, y + 1) });
					break;
				}
			}
		}

		branch_sort();

		_coor.x = _branch.front().x;
		_coor.y = _branch.front().y;
		_now_dict = _branch.front().dict;
		_cost = _branch.front().cost;

		_branch.pop_front();
	}

	_map.map.at(_coor.x).at(_coor.y) = _cost + Define::eMapType::eMapTypeNum;

	_turn++;
}

void H_bfs::branch_sort()
{
	_branch.sort([](H_bfs_Coor& n, H_bfs_Coor& m) {
		return (n.man_d < m.man_d);
		});
}

int H_bfs::man_d(int _x, int _y)
{
	return abs(_map.end.x - _x) + abs(_map.end.y - _y);
}

bool H_bfs::judge_road(int dict) const
{
	int x = _coor.x, y = _coor.y;
	vector<vector<int>> map = _map.map;

	switch (dict)
	{
	case right:
		if (map.at(x + 1).at(y) == Define::eMapType::road || map.at(x + 1).at(y) == Define::eMapType::goal) {
			return true;
		}
		break;
	case up:
		if (map.at(x).at(y - 1) == Define::eMapType::road || map.at(x).at(y - 1) == Define::eMapType::goal) {
			return true;
		}
		break;
	case left:
		if (map.at(x - 1).at(y) == Define::eMapType::road || map.at(x - 1).at(y) == Define::eMapType::goal) {
			return true;
		}
		break;
	case down:
		if (map.at(x).at(y + 1) == Define::eMapType::road || map.at(x).at(y + 1) == Define::eMapType::goal) {
			return true;
		}
		break;
	}

	return false;
}

bool H_bfs::judge_branch()
{
	for (int i = 0; i < eDict::dict_num; i++) {
		if (judge_road(i) && _now_dict != i) {
			switch (i)
			{
			case right:
				return true;
				break;
			case up:
				return true;
				break;
			case left:
				return true;
				break;
			case down:
				return true;
				break;
			}
		}
	}

	return false;
}

void H_bfs::draw() const
{
	Sleep(100);

	Coor start = _map.start, end = _map.end;
	vector<vector <int>> map = _map.map;

	for (int i = 0; i < Define::MAP_SIZE; i++) {
		for (int j = 0; j < Define::MAP_SIZE; j++)
		{
			if (map.at(i).at(j) == Define::eMapType::wall) {
				DrawString(20 + 20 * i, 20 + 20 * j, "Å°", GetColor(255, 255, 255));
			}
			else {
				if (i == start.x && j == start.y) {
					DrawString(20 + 20 * i, 20 + 20 * j, "Å°", GetColor(255, 0, 0));
				}
				else if (i == end.x && j == end.y) {
					DrawString(20 + 20 * i, 20 + 20 * j, "Å°", GetColor(0, 0, 255));
				}
				else if (map.at(i).at(j) > Define::eMapType::eMapTypeNum) {
					DrawString(20 + 20 * i, 20 + 20 * j, "Å°", GetColor(0, 255, 0));
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
	DrawFormatString(460, 540, GetColor(255, 255, 255), "manhattan distance:%d", abs(end.x - _coor.x) + abs(end.y - _coor.y));
}