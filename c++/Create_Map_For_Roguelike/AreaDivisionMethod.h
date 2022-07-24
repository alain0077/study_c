#pragma once

#include "AbstractMethod.h"
#include <list>

struct Way {
	int x1, y1;
	int x2, y2;

	/*
	* Id of the room way is connecting to
	* First : Start room Id
	* Secnd : End room Id
	*/
	//std::pair<int, int> id;
};

struct Room {
	int id;
	int x1, y1;
	int x2, y2;
};

struct Bound {
	int x1, y1;
	int x2, y2;
};

struct Area {
	int x1, y1;
	int x2, y2;
	Room room;
	std::vector<Way> ways;
};

class AreaDivisionMethod : public AbstractMethod
{
public:
	AreaDivisionMethod();
	~AreaDivisionMethod() = default;
	void init() override;
	void draw() override;

	/*
	* Alternate vertical and horizontal divisions.
	*/
	void AreaDiv();
	
	/*
	* Divide the area in order of size.
	*/
	void AreaDivEx();

	/*
	* Assign an appropriately sized room to each area based on the division results.
	*/
	void CreateRoom();

	/*
	* Extend the passage to the boundary.
	*/
	void CreateRoad();

	/*
	* Reduce unnecessary Ways
	*/
	void ReduceWays();

	/*
	* Result
	*/
	std::list<Area> _areas;
	std::list<Room> _rooms;
	std::list<Bound> _bounds;
	std::list<Way> _ways;


	// For draw()
	std::vector<std::list<Area>> _areas_ex;
};