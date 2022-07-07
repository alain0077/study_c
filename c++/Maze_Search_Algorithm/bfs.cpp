#include "bfs.h"

using namespace std;

BFS::BFS(std::vector<std::vector<int>> map, int start_x, int start_y, int end_x, int end_y) : Abstract(map, start_x, start_y, end_x, end_y),
bfs_map(map), depth(0)
{
	q.push({ start_x, start_y, Define::eMapType::eMapTypeNum });
}

void BFS::update()
{
	bfs();
}

void BFS::finalize()
{
	ClearDrawScreen();

	int goal_depth = depth;
	int dict = 0;

	Bfs_Coor goal = { end_x, end_y, goal_depth };

	queue<Bfs_Coor> g;

	goal_depth--;



	while (goal_depth != Define::eMapType::eMapTypeNum) {

		dict++;

		if (dict >= dict_num)
			dict = 0;

		switch (dict)
		{
		case right:
			if (bfs_map.at(goal.x + 1).at(goal.y) == goal_depth) {
				goal.x++;
				g.push(goal);
				goal_depth--;
			}

			break;

		case up:
			if (bfs_map.at(goal.x).at(goal.y - 1) == goal_depth) {
				goal.y--;
				g.push(goal);
				goal_depth--;
			}

			break;

		case left:
			if (bfs_map.at(goal.x - 1).at(goal.y) == goal_depth) {
				goal.x--;
				g.push(goal);
				goal_depth--;
			}

			break;

		case down:
			if (bfs_map.at(goal.x).at(goal.y + 1) == goal_depth) {
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

	while (!g.empty())
	{
		DrawString(20 + 20 * g.front().x, 20 + 20 * g.front().y, "Å°", GetColor(0, 255, 0));
		g.pop();
	}

	DrawFormatString(500, 480, GetColor(255, 255, 255), "%d", turn);
	DrawString(500, 500, "please hit key", GetColor(255, 255, 255));

	ScreenFlip();

	WaitKey();
}

void BFS::bfs()
{
	x = q.front().x;
	y = q.front().y;
	depth = q.front().depth;

	q.pop();

	turn++;

	for (int i = 0; i < eDict::dict_num; i++) {
		if (judge_road(i)) {
			switch (i)
			{
			case eDict::right:
				q.push({ x + 1, y, depth + 1 });
				bfs_map.at(x + 1).at(y) = depth + 1;

				if (_map.at(x + 1).at(y) == Define::eMapType::goal) {
					x++;
					depth++;
					turn++;
					end_flag = true;
				}

				break;

			case eDict::up:
				q.push({ x, y - 1, depth + 1 });
				bfs_map.at(x).at(y - 1) = depth + 1;

				if (_map.at(x).at(y - 1) == Define::eMapType::goal) {
					y--;
					depth++;
					turn++;
					end_flag = true;
				}

				break;

			case eDict::left:
				q.push({ x - 1, y, depth + 1 });
				bfs_map.at(x - 1).at(y) = depth + 1;

				if (_map.at(x - 1).at(y) == Define::eMapType::goal) {
					x--;
					depth++;
					turn++;
					end_flag = true;
				}

				break;

			case eDict::down:
				q.push({ x, y + 1, depth + 1 });
				bfs_map.at(x).at(y + 1) = depth + 1;

				if (_map.at(x).at(y + 1) == Define::eMapType::goal) {
					y++;
					depth++;
					turn++;
					end_flag = true;
				}

				break;
			}

			if (end_flag) {
				break;
			}
		}
	}
}

bool BFS::judge_road(int dict) const
{
	switch (dict)
	{
	case eDict::up:
		if (bfs_map.at(x).at(y - 1) == Define::eMapType::road || _map.at(x).at(y - 1) == Define::eMapType::goal)
			return true;
		break;
	case eDict::down:
		if (bfs_map.at(x).at(y + 1) == Define::eMapType::road || _map.at(x).at(y + 1) == Define::eMapType::goal)
			return true;
		break;
	case eDict::right:
		if (bfs_map.at(x + 1).at(y) == Define::eMapType::road || _map.at(x + 1).at(y) == Define::eMapType::goal)
			return true;
		break;
	case eDict::left:
		if (bfs_map.at(x - 1).at(y) == Define::eMapType::road || _map.at(x - 1).at(y) == Define::eMapType::goal)
			return true;
		break;
	default:
		break;
	}

	return false;
}

void BFS::draw() const
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
				else if (bfs_map.at(i).at(j) > Define::eMapType::eMapTypeNum) {
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
}