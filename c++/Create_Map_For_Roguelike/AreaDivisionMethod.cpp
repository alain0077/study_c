#include "AreaDivisionMethod.h"
#include "Define.h"
#include <DxLib.h>
#include <algorithm>


using namespace std;

AreaDivisionMethod::AreaDivisionMethod() : AbstractMethod()
{
	//AreaDiv();
	//AreaDivEx();
}

void AreaDivisionMethod::init()
{
	_areas.clear();
	_rooms.clear();
	_bounds.clear();
	_ways.clear();
	_areas_ex.clear();
	for (int i = 0; i < Define::MAX_ROW; i++)for (int j = 0; j < Define::MAX_COL; j++) _map[i][j] = eMapType::wall;

}

void AreaDivisionMethod::AreaDiv()
{
	//Coordinate of Left Corner
	int x1 = 1;
	int y1 = 1;

	//Coordinate of Right Corner
	int x2 = Define::MAX_COL - 2;
	int y2 = Define::MAX_ROW - 2;

	// Vertical or Hhorizontal division
	bool isVertical = GetRandom(0, 1) ? true : false;
	
	while (_areas.size() < Define::ROOM_NUM)
	{
		if ((x2 - x1 < 2 * (Define::MIN_WIDTH + 2) + 1) && (y2 - y1 < 2 * (Define::MIN_HEIGHT + 2) + 1))  break;
		else if (x2 - x1 < 2 * (Define::MIN_WIDTH + 2) + 1) { isVertical = false; }
		else if (y2 - y1 < 2 * (Define::MIN_HEIGHT + 2) + 1) { isVertical = true; }

		Area area;

		int divpoint = 0;

		if (isVertical) // Vertical division
		{
			divpoint = GetRandom(x1 + Define::MIN_WIDTH + 2, x2 - Define::MIN_WIDTH - 2);

			if ((x1 + x2) / 2 < divpoint)
			{
				_bounds.push_back({ divpoint, y1, divpoint, y2 });

				area = { divpoint + 1, y1, x2, y2 };

				x2 = divpoint - 1;
			}
			else
			{
				_bounds.push_back({ divpoint, y1, divpoint, y2 });

				area = { x1, y1, divpoint - 1, y2 };

				x1 = divpoint + 1;
			}

			isVertical = false;
		}
		else // Hhorizontal division
		{
			divpoint = GetRandom(y1 + Define::MIN_WIDTH + 2, y2 - Define::MIN_WIDTH - 2);

			if ((y1 + y2) / 2 < divpoint)
			{
				_bounds.push_back({ x1, divpoint, x2, divpoint });

				area = { x1, divpoint + 1, x2, y2 };

				y2 = divpoint - 1;
			}
			else
			{
				_bounds.push_back({ x1, divpoint, x2, divpoint });

				area = { x1, y1, x2, divpoint - 1 };

				y1 = divpoint + 1;
			}

			isVertical = true;
		}

		_areas.push_back(area);
	}
}

void AreaDivisionMethod::AreaDivEx()
{
	bool isVertical = true;

	// For list sort
	auto comp = [](auto const& a, auto const& b) { return ((a.x2 - a.x1) * (a.y2 - a.y1)) > ((b.x2 - b.x1) * (b.y2 - b.y1)); };

	// Initialization
	_areas.push_back({ 1, 1, Define::MAX_COL - 2, Define::MAX_ROW - 2 });

	// For Draw()
	_areas_ex.push_back(_areas);

	while (_areas.size() < Define::ROOM_NUM)
	{
		Area area = _areas.front();

		/*
		* Decide whether to divide Vertically or Horizontally
		*/
		if (area.x2 - area.x1 < 2 * Define::MIN_WIDTH + 4)
		{
			if (area.y2 - area.y1 >= 2 * Define::MIN_HEIGHT + 4)
			{
				isVertical = false;
			}
			else
			{
				break;
			}
		}
		else if (area.y2 - area.y1 < 2 * Define::MIN_HEIGHT + 4)
		{
			if (area.x2 - area.x1 >= 2 * Define::MIN_WIDTH + 4)
			{
				isVertical = true;
			}
			else
			{
				break;
			}
		}
		else
		{
			isVertical = GetRandom(0, 1) ? true : false;
		}
		
		int bound = 0;

		/*
		* Divide the Area in the determined direction
		*/
		if (isVertical)
		{
			// Randomly set Boundry
			bound = GetRandom(area.x1 + Define::MIN_WIDTH + 2, area.x2 - Define::MIN_WIDTH - 2);

			_bounds.push_back({ bound, area.y1, bound, area.y2 });

			_areas.push_back({ area.x1, area.y1, bound - 1, area.y2 });

			_areas.push_back({ bound + 1, area.y1, area.x2, area.y2 });

			isVertical = false;
		}
		else
		{
			// Randomly set Boundry
			bound = GetRandom(area.y1 + Define::MIN_HEIGHT + 2, area.y2 - Define::MIN_HEIGHT - 2);

			_bounds.push_back({ area.x1, bound, area.x2, bound });

			_areas.push_back({ area.x1, area.y1, area.x2, bound - 1 });

			_areas.push_back({ area.x1, bound + 1, area.x2, area.y2 });

			isVertical = true;
		}
		_areas.pop_front();

		// For Draw()
		_areas_ex.push_back(_areas);

		// Sort by Area in order of Size
		_areas.sort(comp);
	}
}

void AreaDivisionMethod::CreateRoom()
{
	int cnt = 0;

	auto area = _areas.begin();

	while (area != _areas.end())
	{
		Room room;
		room.id = cnt++;
		
		//room.x = GetRandom(area->x + 1, area->width - Define::MIN_WIDTH);
		room.x1 = area->x1 + 1;

		room.x2 = GetRandom(room.x1 + Define::MIN_WIDTH - 1, area->x2 - 1);
		
		//room.y = GetRandom(area->y + 1, area->height - Define::MIN_HEIGHT);
		room.y1 = area->y1 + 1;

		room.y2 = GetRandom(room.y1 + Define::MIN_HEIGHT - 1, area->y2 - 1);
		
		WriteMap(room.x1, room.y1, room.x2, room.y2, eMapType::room);

		area->room = room;
		
		_rooms.push_back(room);

		area++;
	}
}

void AreaDivisionMethod::CreateRoad()
{
	auto area = _areas.begin();

	/*
	* Create the Way from the Room to the edge of the Area
	*/
	while (area != _areas.end())
	{
		/*
		* Left Side
		* Whether it is the Leftmost Area
		*/
		if (area->x1 != 1)
		{
			Way way;
			way.x1 = area->room.x1 - 1;
			way.y1 = GetRandom(area->room.y1 + 1, area->room.y2 - 1);
			way.x2 = area->x1;
			way.y2 = way.y1;

			WriteMap(way.x1, way.y1, way.x2, way.y2, eMapType::way);

			area->ways.push_back(way);
			_ways.push_back(way);
		}

		/*
		* Right Side
		* Whether it is the Rightmost Area
		*/
		if (area->x2 != Define::MAX_COL - 2)
		{
			Way way;
			way.x1 = area->room.x2 + 1;
			way.y1 = GetRandom(area->room.y1 + 1, area->room.y2 - 1);
			way.x2 = area->x2;
			way.y2 = way.y1;

			WriteMap(way.x1, way.y1, way.x2, way.y2, eMapType::way);

			area->ways.push_back(way);
			_ways.push_back(way);
		}

		/*
		* Upper Side
		* Whether it is the Top Area
		*/
		if (area->y1 != 1)
		{
			Way way;
			way.x1 = GetRandom(area->room.x1 + 1, area->room.x2 - 1);
			way.y1 = area->room.y1 - 1;
			way.x2 = way.x1;
			way.y2 = area->y1;

			WriteMap(way.x1, way.y1, way.x2, way.y2, eMapType::way);

			area->ways.push_back(way);
			_ways.push_back(way);
		}

		/*
		* Lower Side
		* Whether it is the Bottom Area
		*/
		if (area->y2 != Define::MAX_ROW - 2)
		{
			Way way;
			way.x1 = GetRandom(area->room.x1 + 1, area->room.x2 - 1);
			way.y1 = area->room.y2 + 1;
			way.x2 = way.x1;
			way.y2 = area->y2;

			WriteMap(way.x1, way.y1, way.x2, way.y2, eMapType::way);

			area->ways.push_back(way);
			_ways.push_back(way);
		}

		area++;
	}

	/*
	* Connect Ways that extend to the Boundary
	*/
	for (auto bound : _bounds)
	{
		bool isVertical = (bound.x1 == bound.x2) ? true : false;

		// axis
		int k = isVertical ? bound.x1 : bound.y1;

		
		vector<int> points;

		if (isVertical)
		{
			for (int i = bound.y1; i <= bound.y2; i++)
			{
				if (_map[i][k - 1] == eMapType::way) points.push_back(i);

				if (_map[i][k + 1] == eMapType::way) points.push_back(i);
			}
		}
		else
		{
			for (int i = bound.x1; i <= bound.x2; i++)
			{
				if (_map[k - 1][i] == eMapType::way) points.push_back(i);

				if (_map[k + 1][i] == eMapType::way) points.push_back(i);
			}
		}

		for (int i = 1; i < points.size(); i += 2)
		{
			int t = points[i - 1], p = points[i];

			if (isVertical)
			{
				WriteMap(bound.x1, t, bound.x2, p, eMapType::way);
				_ways.push_back({ bound.x1, t, bound.x2, p });
			}
			else
			{
				WriteMap(t, bound.y1, p, bound.y2, eMapType::way);
				_ways.push_back({ t, bound.y1, p, bound.y2 });
			}
		}
	}
}

void AreaDivisionMethod::ReduceWays()
{
	for (auto area : _areas)
	{
		for (auto way : area.ways)
		{
			/*
			* Left Side
			*/
			if (area.x1 == way.x1)
			{
				if (_map[way.y1][way.x1 - 1] == eMapType::wall)
				{
					WriteMap(way.x1, way.y1, way.x2, way.y2, eMapType::wall);
				}
			}
			/*
			* Right Side
			*/
			if (area.x2 == way.x2)
			{
				if (_map[way.y2][way.x2 + 1] == eMapType::wall)
				{
					WriteMap(way.x1, way.y1, way.x2, way.y2, eMapType::wall);
				}
			}
			/*
			* Upper Side
			*/
			if (area.y1 == way.y1)
			{
				if (_map[way.y1 - 1][way.x1] == eMapType::wall)
				{
					WriteMap(way.x1, way.y1, way.x2, way.y2, eMapType::wall);
				}
			}
			/*
			* Lower Side
			*/
			if (area.y2 == way.y2)
			{
				if (_map[way.y2 + 1][way.x2] == eMapType::wall)
				{
					WriteMap(way.x1, way.y1, way.x2, way.y2, eMapType::wall);
				}
			}
		}
	}
}

void AreaDivisionMethod::draw()
{
	DrawString(200, 400, "Area Division Method", GetColor(255, 255, 255));
	DrawString(200, 420, "Alternate verticaland horizontal divisions.", GetColor(255, 255, 255));
	DrawString(200, 440, "Please Hit Key", GetColor(255, 255, 255));

	ScreenFlip();
	WaitKey();

	ClearDrawScreen();

	for (int i = 0; i < Define::MAX_ROW; i++) {
		for (int j = 0; j < Define::MAX_COL; j++) {
			DrawString(0 + 20 * j, 0 + 20 * i, "¡", GetColor(255, 255, 255));
		}
	}

	AreaDiv();

	for (auto area : _areas) {
		for (int i = area.y1; i < area.y2 + 1; i++) {
			for (int j = area.x1; j < area.x2 + 1; j++) {
				DrawString(0 + 20 * j, 0 + 20 * i, "¡", GetColor(255, 0, 255));
			}
		}

		ScreenFlip();
		Sleep(20);
	}

	for (auto bound : _bounds) {
		for (int i = bound.y1; i < bound.y2 + 1; i++) {
			for (int j = bound.x1; j < bound.x2 + 1; j++) {
				DrawString(0 + 20 * j, 0 + 20 * i, "¡", GetColor(0, 255, 255));
			}
		}

		ScreenFlip();
		Sleep(20);
	}

	CreateRoom();

	for (auto room : _rooms) {
		for (int i = room.y1; i < room.y2 + 1; i++) {
			for (int j = room.x1; j < room.x2 + 1; j++) {
				DrawString(0 + 20 * j, 0 + 20 * i, "¡", GetColor(0, 0, 255));
			}
		}

		ScreenFlip();
		Sleep(20);
	}

	CreateRoad();

	for (auto road : _ways) {
		for (int i = road.y1; i < road.y2 + 1; i++) {
			for (int j = road.x1; j < road.x2 + 1; j++) {
				DrawString(0 + 20 * j, 0 + 20 * i, "¡", GetColor(0, 0, 255));
			}
		}

		ScreenFlip();
		Sleep(20);
	}

	WaitKey();

	ReduceWays();

	ClearDrawScreen();

	for(int i = 0; i < Define::MAX_ROW; i++) {
		for (int j = 0; j < Define::MAX_COL; j++) {
			if(_map[i][j] == eMapType::wall) DrawString(0 + 20 * j, 0 + 20 * i, "¡", GetColor(255, 255, 255));
			else DrawString(0 + 20 * j, 0 + 20 * i, "¡", GetColor(0, 0, 255));
		}
	}

	ScreenFlip();
	WaitKey();


	init();

	ClearDrawScreen();

	DrawString(200, 400, "Area Division Method", GetColor(255, 255, 255));
	DrawString(200, 420, "Divide the area in order of size.", GetColor(255, 255, 255));
	DrawString(200, 440, "Please Hit Key", GetColor(255, 255, 255));

	ScreenFlip();
	WaitKey();

	AreaDivEx();

	for (auto ex : _areas_ex) {
		ClearDrawScreen();

		for (int i = 0; i < Define::MAX_ROW; i++) {
			for (int j = 0; j < Define::MAX_COL; j++) {
				DrawString(0 + 20 * j, 0 + 20 * i, "¡", GetColor(255, 255, 255));
			}
		}

		for (auto area : ex) {
			for (int i = area.y1; i < area.y2 + 1; i++) {
				for (int j = area.x1; j < area.x2 + 1; j++) {
					DrawString(0 + 20 * j, 0 + 20 * i, "¡", GetColor(255, 0, 255));
				}
			}
		}

		ScreenFlip();
		Sleep(30);
	}

	for (auto bound : _bounds) {
		for (int i = bound.y1; i < bound.y2 + 1; i++) {
			for (int j = bound.x1; j < bound.x2 + 1; j++) {
				DrawString(0 + 20 * j, 0 + 20 * i, "¡", GetColor(0, 255, 255));
			}
		}

		ScreenFlip();
		Sleep(30);
	}


	CreateRoom();

	for (auto room : _rooms) {
		for (int i = room.y1; i < room.y2 + 1; i++) {
			for (int j = room.x1; j < room.x2 + 1; j++) {
				DrawString(0 + 20 * j, 0 + 20 * i, "¡", GetColor(0, 0, 255));
			}
		}

		ScreenFlip();
		Sleep(30);
	}

	CreateRoad();

	for (auto road : _ways) {
		for (int i = road.y1; i < road.y2 + 1; i++) {
			for (int j = road.x1; j < road.x2 + 1; j++) {
				DrawString(0 + 20 * j, 0 + 20 * i, "¡", GetColor(0, 0, 255));
			}
		}

		ScreenFlip();
		Sleep(30);
	}

	WaitKey();

	ReduceWays();

	ClearDrawScreen();

	for(int i = 0; i < Define::MAX_ROW; i++) {
		for (int j = 0; j < Define::MAX_COL; j++) {
			if(_map[i][j] == eMapType::wall) DrawString(0 + 20 * j, 0 + 20 * i, "¡", GetColor(255, 255, 255));
			else DrawString(0 + 20 * j, 0 + 20 * i, "¡", GetColor(0, 0, 255));
		}
	}

	ScreenFlip();
}