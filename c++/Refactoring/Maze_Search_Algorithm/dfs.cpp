#include "dfs.h"


DFS::DFS(std::vector<std::vector<int>> map, int start_x, int start_y, int end_x, int end_y) : Abstract(map, start_x, start_y, end_x, end_y),
dfs_map(map)
{
	s.push({ start_x, start_y });
}

void DFS::update()
{
	if (_map.at(x).at(y) == Define::eMapType::goal) {
		end_flag = true;
	}
	else {
		dfs();
	}
}

void DFS::finalize()
{
	ClearDrawScreen();

	for (int i = 0; i < Define::MAP_SIZE; i++) {
		for (int j = 0; j < Define::MAP_SIZE; j++)
		{
			if (_map.at(i).at(j) == Define::eMapType::wall) {
				DrawString(20 + 20 * i, 20 + 20 * j, "¡", GetColor(255, 255, 255));
			}
			else {
				if (i == start_x && j == start_y) {
					DrawString(20 + 20 * i, 20 + 20 * j, "¡", GetColor(255, 0, 0));
				}
				else if (i == end_x && j == end_y) {
					DrawString(20 + 20 * i, 20 + 20 * j, "¡", GetColor(0, 0, 255));
				}
				else
					DrawString(20 + 20 * i, 20 + 20 * j, "  ", GetColor(255, 255, 255));
			}
		}
	}

	while (!s.empty()) {
		if ((s.top().x != start_x || s.top().y != start_y) && (s.top().x != end_x || s.top().y != end_y))
			DrawString(20 + 20 * s.top().x, 20 + 20 * s.top().y, "¡", GetColor(0, 255, 0));

		s.pop();
	}

	DrawFormatString(500, 480, GetColor(255, 255, 255), "%d", turn);
	DrawString(500, 500, "please hit key", GetColor(255, 255, 255));

	ScreenFlip();

	WaitKey();
}

void DFS::dfs()
{
	if (judge_end()) {
		dfs_map.at(x).at(y) = Define::eMapType::eMapTypeNum;

		s.pop();

		x = s.top().x;
		y = s.top().y;
	}
	else {
		if (judge_wall(now_dict)) {
			now_dict++;
		}
		else {
			dfs_map.at(x).at(y) = Define::eMapType::eMapTypeNum;

			switch (now_dict)
			{
			case eDict::right:
				x++;
				break;
			case eDict::up:
				y--;
				break;
			case eDict::left:
				x--;
				break;
			case eDict::down:
				y++;
				break;
			}

			turn++;

			s.push({ x, y });

			Sleep(100);

			now_dict = right;
		}
	}
}

bool DFS::judge_wall(int dict) const
{
	switch (dict)
	{
	case eDict::up:
		if (dfs_map.at(x).at(y - 1) == Define::eMapType::wall || dfs_map.at(x).at(y - 1) == Define::eMapType::eMapTypeNum)
			return true;
		break;
	case eDict::down:
		if (dfs_map.at(x).at(y + 1) == Define::eMapType::wall || dfs_map.at(x).at(y + 1) == Define::eMapType::eMapTypeNum)
			return true;
		break;
	case eDict::right:
		if (dfs_map.at(x + 1).at(y) == Define::eMapType::wall || dfs_map.at(x + 1).at(y) == Define::eMapType::eMapTypeNum)
			return true;
		break;
	case eDict::left:
		if (dfs_map.at(x - 1).at(y) == Define::eMapType::wall || dfs_map.at(x - 1).at(y) == Define::eMapType::eMapTypeNum)
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
	for (int i = 0; i < Define::MAP_SIZE; i++) {
		for (int j = 0; j < Define::MAP_SIZE; j++)
		{
			if (_map.at(i).at(j) == Define::eMapType::wall) {
				DrawString(20 + 20 * i, 20 + 20 * j, "¡", GetColor(255, 255, 255));
			}
			else {
				if (i == start_x && j == start_y) {
					DrawString(20 + 20 * i, 20 + 20 * j, "¡", GetColor(255, 0, 0));
				}
				else if (i == end_x && j == end_y) {
					DrawString(20 + 20 * i, 20 + 20 * j, "¡", GetColor(0, 0, 255));
				}
				else if (dfs_map.at(i).at(j) == Define::eMapType::eMapTypeNum) {
					DrawString(20 + 20 * i, 20 + 20 * j, "¡", GetColor(0, 255, 0));
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