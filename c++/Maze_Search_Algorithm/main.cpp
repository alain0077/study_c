#pragma warning(disable: 4996)

#include <DxLib.h>
#include <map>
#include <vector>
#include <random>
#include "Define.h"

#include "Abstract.h"
#include "dfs.h"
#include "bfs.h"
#include "h_bfs.h"

using namespace std;

int GetRandom(int min, int max, int count = 1)
{
	if (max == 0) {
		return 0;
	}

	srand(GetNowCount() / (min + max + ++count));

	int num = rand();

	uniform_int_distribution<int> dist(min, max);

	mt19937 mt(num);

	num = dist(mt);

	return num;
}

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
	SetAlwaysRunFlag(TRUE);						//ウィンドウがノンアクティブでも実行
	ChangeWindowMode(TRUE);						// ウィンドウモードに設定
	SetWindowSizeChangeEnableFlag(TRUE);		//ウィンドウサイズを自由に変更できるようにする
	SetOutApplicationLogValidFlag(FALSE);
	SetGraphMode(700, 600, 32);
	DxLib_Init();								// DXライブラリ初期化処理

	SetDrawScreen(DX_SCREEN_BACK); //描画先を裏画面に設定

	vector<vector<int>> _map;

	vector<int> n;

	for (int i = 0; i < Define::MAP_SIZE; i++) {

		_map.push_back(n);

		for (int j = 0; j < Define::MAP_SIZE; j++) {
			_map.at(i).push_back(Define::eMapType::road);
		}
	}

	int count = 1;


	for (int i = 1; i < Define::MAP_SIZE - 1; i++) {
		for (int j = 1; j < Define::MAP_SIZE - 1; j++) {
			_map.at(i).at(j) = Define::eMapType::wall;
		}
	}

	int start_x = GetRandom(1, 10, count++) * 2;
	int start_y = GetRandom(1, 10, count++) * 2;

	_map.at(start_x).at(start_y) = Define::eMapType::road;

	bool flag = false;

	int end_x = 0;
	int end_y = 0;


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

		for (int i = 2; i < Define::MAP_SIZE - 2; i += 2) {
			for (int j = 2; j < Define::MAP_SIZE - 2; j += 2) {
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

		int _num = GetRandom(1, row.size(), count++) - 1;

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
					int num = GetRandom(0, _tmp.size() - 1, count++);

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
						_map.at(_row).at(--_col) = Define::eMapType::road;

						end_x = _row;
						end_y = _col;

						_flag = true;
					}
					else {
						dict.erase(dict.begin());
					}
					break;
				case 2:
					if (_map.at(_row).at(_col + 2) != Define::eMapType::road) {
						_map.at(_row).at(++_col) = Define::eMapType::road;
						_map.at(_row).at(++_col) = Define::eMapType::road;

						end_x = _row;
						end_y = _col;

						_flag = true;
					}
					else {
						dict.erase(dict.begin());
					}
					break;
				case 3:
					if (_map.at(_row - 2).at(_col) != Define::eMapType::road) {
						_map.at(--_row).at(_col) = Define::eMapType::road;
						_map.at(--_row).at(_col) = Define::eMapType::road;

						end_x = _row;
						end_y = _col;

						_flag = true;
					}
					else {
						dict.erase(dict.begin());
					}
					break;
				case 4:
					if (_map.at(_row + 2).at(_col) != Define::eMapType::road) {
						_map.at(++_row).at(_col) = Define::eMapType::road;
						_map.at(++_row).at(_col) = Define::eMapType::road;

						end_x = _row;
						end_y = _col;

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

	_map.at(start_x).at(start_y) = Define::eMapType::start;
	_map.at(end_x).at(end_y) = Define::eMapType::goal;


	WaitKey();

	Abstract* search = new H_bfs(_map, start_x, start_y, end_x, end_y);

	while (!ScreenFlip() && !ProcessMessage() && !ClearDrawScreen()) {
		if (!search->loop()) {
			search->finalize();
			break;
		}
	}


	search = new DFS(_map, start_x, start_y, end_x, end_y);

	while (!ScreenFlip() && !ProcessMessage() && !ClearDrawScreen()) {
		if (!search->loop()) {
			search->finalize();
			break;
		}
	}


	search = new BFS(_map, start_x, start_y, end_x, end_y);

	while (!ScreenFlip() && !ProcessMessage() && !ClearDrawScreen()) {
		if (!search->loop()) {
			search->finalize();
			break;
		}
	}

	DxLib_End(); // DXライブラリ終了処理
	return 0;
}