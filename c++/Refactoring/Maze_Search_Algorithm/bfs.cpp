#include "bfs.h"

using namespace std;

BFS::BFS(Map_Info map) : Abstract(map),
_depth(0)
{
	_bfs_map = map.map;
	_q.push({ map.start.x, map.start.y, Define::eMapType::eMapTypeNum });
}

void BFS::update()
{
	bfs();
}

void BFS::finalize()
{
	ClearDrawScreen();

	int goal_depth = _depth;
	int dict = 0;
	Coor start = _map.start, end = _map.end;
	vector<vector <int>> map = _map.map;

	Bfs_Coor goal = { end.x, end.y, goal_depth };

	queue<Bfs_Coor> g;

	goal_depth--;



	while (goal_depth != Define::eMapType::eMapTypeNum) {

		dict++;

		if (dict >= eDict::dict_num)
			dict = 0;

		switch (dict)
		{
		case right:
			if (_bfs_map.at(goal.x + 1).at(goal.y) == goal_depth) {
				goal.x++;
				g.push(goal);
				goal_depth--;
			}

			break;

		case up:
			if (_bfs_map.at(goal.x).at(goal.y - 1) == goal_depth) {
				goal.y--;
				g.push(goal);
				goal_depth--;
			}

			break;

		case left:
			if (_bfs_map.at(goal.x - 1).at(goal.y) == goal_depth) {
				goal.x--;
				g.push(goal);
				goal_depth--;
			}

			break;

		case down:
			if (_bfs_map.at(goal.x).at(goal.y + 1) == goal_depth) {
				goal.y++;
				g.push(goal);
				goal_depth--;
			}

			break;
		}
	}

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

	while (!g.empty())
	{
		DrawString(20 + 20 * g.front().x, 20 + 20 * g.front().y, "Å°", GetColor(0, 255, 0));
		g.pop();
	}

	DrawFormatString(500, 480, GetColor(255, 255, 255), "%d", _turn);
	DrawString(500, 500, "please hit key", GetColor(255, 255, 255));

	ScreenFlip();

	WaitKey();
}

void BFS::bfs()
{
	_coor.x = _q.front().x, _coor.y = _q.front().y;
	vector<vector <int>> map = _map.map;

	_depth = _q.front().depth;

	_q.pop();

	_turn++;

	for (int i = 0; i < eDict::dict_num; i++) {
		if (judge_road(i)) {
			switch (i)
			{
			case eDict::right:
				_q.push({ _coor.x + 1, _coor.y, _depth + 1 });
				_bfs_map.at(_coor.x + 1).at(_coor.y) = _depth + 1;

				if (map.at(_coor.x + 1).at(_coor.y) == Define::eMapType::goal) {
					_coor.x++;
					_depth++;
					_turn++;
					_end_flag = true;
				}

				break;

			case eDict::up:
				_q.push({ _coor.x, _coor.y - 1, _depth + 1 });
				_bfs_map.at(_coor.x).at(_coor.y - 1) = _depth + 1;

				if (map.at(_coor.x).at(_coor.y - 1) == Define::eMapType::goal) {
					_coor.y--;
					_depth++;
					_turn++;
					_end_flag = true;
				}

				break;

			case eDict::left:
				_q.push({ _coor.x - 1, _coor.y, _depth + 1 });
				_bfs_map.at(_coor.x - 1).at(_coor.y) = _depth + 1;

				if (map.at(_coor.x - 1).at(_coor.y) == Define::eMapType::goal) {
					_coor.x--;
					_depth++;
					_turn++;
					_end_flag = true;
				}

				break;

			case eDict::down:
				_q.push({ _coor.x, _coor.y + 1, _depth + 1 });
				_bfs_map.at(_coor.x).at(_coor.y + 1) = _depth + 1;

				if (map.at(_coor.x).at(_coor.y + 1) == Define::eMapType::goal) {
					_coor.y++;
					_depth++;
					_turn++;
					_end_flag = true;
				}

				break;
			}

			if (_end_flag) {
				break;
			}
		}
	}
}

bool BFS::judge_road(int dict) const
{
	int x = _coor.x, y = _coor.y;

	switch (dict)
	{
	case eDict::up:
		if (_bfs_map.at(x).at(y - 1) == Define::eMapType::road || _map.map.at(x).at(y - 1) == Define::eMapType::goal)
			return true;
		break;
	case eDict::down:
		if (_bfs_map.at(x).at(y + 1) == Define::eMapType::road || _map.map.at(x).at(y + 1) == Define::eMapType::goal)
			return true;
		break;
	case eDict::right:
		if (_bfs_map.at(x + 1).at(y) == Define::eMapType::road || _map.map.at(x + 1).at(y) == Define::eMapType::goal)
			return true;
		break;
	case eDict::left:
		if (_bfs_map.at(x - 1).at(y) == Define::eMapType::road || _map.map.at(x - 1).at(y) == Define::eMapType::goal)
			return true;
		break;
	default:
		break;
	}

	return false;
}

void BFS::draw() const
{
	Coor start = _map.start, end = _map.end;
	vector<vector <int>> map = _map.map;

	Sleep(100);

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
				else if (_bfs_map.at(i).at(j) > Define::eMapType::eMapTypeNum) {
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
}