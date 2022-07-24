#pragma once

#include <vector>

enum eMapType {
	wall,
	room,
	way,
};

class AbstractMethod
{
public:
	AbstractMethod();
	~AbstractMethod() = default;
	virtual void init() = 0;
	virtual void draw() = 0;
	std::vector<std::vector<eMapType>> getMap() { return _map; }
	int GetRandom(int min, int max);
	void WriteMap(int x1, int y1, int x2, int y2, eMapType type);

protected:
	// For GetRandom()
	unsigned int _seed;
	
	std::vector<std::vector<eMapType>> _map;
};