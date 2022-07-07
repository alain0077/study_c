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

H_bfs::H_bfs(std::vector<std::vector<int>> map, int start_x, int start_y, int end_x, int end_y) :Abstract(map, start_x, start_y, end_x, end_y),
cost(0)
{
	_map.at(x).at(y) = cost + Define::eMapType::eMapTypeNum;
}

void H_bfs::finalize()
{
	ClearDrawScreen();

	int goal_cost = cost + Define::eMapType::eMapTypeNum;
	int dict = 0;

	H_bfs_Coor goal = { end_x, end_y,  0, 0, 0 };

	list<H_bfs_Coor> g;

	goal_cost--;

	for (int i = 0; i < Define::MAP_SIZE; i++) {
		for (int j = 0; j < Define::MAP_SIZE; j++)
		{
			if (_map.at(i).at(j) == Define::eMapType::wall) {
				DrawString(20 + 20 * i, 20 + 20 * j, "Å°", GetColor(255, 255, 255));
			}
			else {
				if (i == start_x && j == start_y) {
					DrawString(20 + 20 * i, 20 + 20 * j, "Å°", GetColor(255, 0, 0));
				}
				else if (i == end_x && j == end_y) {
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

		switch (dict % dict_num)
		{
		case right:
			if (_map.at(goal.x + 1).at(goal.y) == goal_cost) {
				goal.x++;
				g.push_back(goal);
				goal_cost--;
			}

			break;

		case up:
			if (_map.at(goal.x).at(goal.y - 1) == goal_cost) {
				goal.y--;
				g.push_back(goal);
				goal_cost--;
			}

			break;

		case left:
			if (_map.at(goal.x - 1).at(goal.y) == goal_cost) {
				goal.x--;
				g.push_back(goal);
				goal_cost--;
			}

			break;

		case down:
			if (_map.at(goal.x).at(goal.y + 1) == goal_cost) {
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

	DrawFormatString(500, 480, GetColor(255, 255, 255), "%d", turn);
	DrawString(500, 500, "please hit key", GetColor(255, 255, 255));

	ScreenFlip();

	WaitKey();
}

void H_bfs::update()
{
	if (x == end_x && y == end_y) {
		end_flag = true;
	}
	else {
		bfs();

		int c = 0;

		for (auto itr = branch.begin(); itr != branch.end(); itr++) {
			DrawFormatString(480, 100 + 20 * c, GetColor(255, 255, 255), "        man_d:%d", itr->man_d);
			c++;
		}
	}
}

void H_bfs::bfs()
{
	if (judge_road(now_dict) && !judge_branch()) {
		switch (now_dict)
		{
		case right:
			x++;
			break;
		case up:
			y--;
			break;
		case left:
			x--;
			break;
		case down:
			y++;
			break;
		}

		cost++;
	}
	else if (!judge_road(now_dict) && !judge_branch()) {
		x = branch.front().x;
		y = branch.front().y;
		now_dict = branch.front().dict;
		cost = branch.front().cost;
		branch.pop_front();
	}
	else {
		for (int i = 0; i < dict_num; i++) {
			if (judge_road(i)) {
				switch (i)
				{
				case right:
					branch.push_back({ x + 1, y, right, cost + 1, man_d(x + 1, y) });
					break;
				case up:
					branch.push_back({ x, y - 1, up, cost + 1, man_d(x, y - 1) });
					break;
				case left:
					branch.push_back({ x - 1, y, left, cost + 1, man_d(x - 1, y) });
					break;
				case down:
					branch.push_back({ x, y + 1, down, cost + 1, man_d(x, y + 1) });
					break;
				}
			}
		}

		branch_sort();

		x = branch.front().x;
		y = branch.front().y;
		now_dict = branch.front().dict;
		cost = branch.front().cost;

		branch.pop_front();
	}

	_map.at(x).at(y) = cost + Define::eMapType::eMapTypeNum;

	turn++;
}

void H_bfs::branch_sort()
{
	branch.sort([](H_bfs_Coor& n, H_bfs_Coor& m) {
		return (n.man_d < m.man_d);
		});
}

int H_bfs::man_d(int _x, int _y)
{
	return abs(end_x - _x) + abs(end_y - _y);
}

bool H_bfs::judge_road(int dict) const
{
	switch (dict)
	{
	case right:
		if (_map.at(x + 1).at(y) == Define::eMapType::road || _map.at(x + 1).at(y) == Define::eMapType::goal) {
			return true;
		}
		break;
	case up:
		if (_map.at(x).at(y - 1) == Define::eMapType::road || _map.at(x).at(y - 1) == Define::eMapType::goal) {
			return true;
		}
		break;
	case left:
		if (_map.at(x - 1).at(y) == Define::eMapType::road || _map.at(x - 1).at(y) == Define::eMapType::goal) {
			return true;
		}
		break;
	case down:
		if (_map.at(x).at(y + 1) == Define::eMapType::road || _map.at(x).at(y + 1) == Define::eMapType::goal) {
			return true;
		}
		break;
	}

	return false;
}

bool H_bfs::judge_branch()
{
	for (int i = 0; i < dict_num; i++) {
		if (judge_road(i) && now_dict != i) {
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

	for (int i = 0; i < Define::MAP_SIZE; i++) {
		for (int j = 0; j < Define::MAP_SIZE; j++)
		{
			if (_map.at(i).at(j) == Define::eMapType::wall) {
				DrawString(20 + 20 * i, 20 + 20 * j, "Å°", GetColor(255, 255, 255));
			}
			else {
				if (i == start_x && j == start_y) {
					DrawString(20 + 20 * i, 20 + 20 * j, "Å°", GetColor(255, 0, 0));
				}
				else if (i == end_x && j == end_y) {
					DrawString(20 + 20 * i, 20 + 20 * j, "Å°", GetColor(0, 0, 255));
				}
				else if (_map.at(i).at(j) > Define::eMapType::eMapTypeNum) {
					DrawString(20 + 20 * i, 20 + 20 * j, "Å°", GetColor(0, 255, 0));
				}
				else {
					DrawString(20 + 20 * i, 20 + 20 * j, "  ", GetColor(255, 255, 255));
				}
			}
		}
	}

	DrawFormatString(480, 480, GetColor(255, 255, 255), "        start:%d,%d", start_x, start_y);
	DrawFormatString(480, 500, GetColor(255, 255, 255), "          end:%d,%d", end_x, end_y);
	DrawFormatString(480, 520, GetColor(255, 255, 255), "now searching:%d,%d", x, y);
	DrawFormatString(460, 540, GetColor(255, 255, 255), "manhattan distance:%d", abs(end_x - x) + abs(end_y - y));
}