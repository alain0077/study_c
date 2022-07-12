#pragma once
#include <string>
#include "Task.h"

struct B_Status {
	//bullet type
	int b_type;
	//Corrdinate
	std::pair<int, int> coor;
	//offset
	std::pair<int, int> offset;
	//Height & Width
	std::pair<int, int> _h_w;
};

class Bullet : public Task
{
public:
	Bullet(double x, double y, double ang, double speed, int pattern);
	~Bullet() = default;
	void init();
	bool update();
	void draw() const;

	bool IsTakenCircle(double x, double y, double r);

	B_Status getStatus() { return { _pattern, {_x, _y}, {_x_offset, _y_offset}, {_heigh, _width} };}

private:
	int _cnt,
		_pattern;

	double
		_x,
		_y,
		_x_offset,
		_y_offset,
		_width,
		_heigh,
		_ang,
		_ang_x,
		_ang_y,
		_speed;
};