#pragma once

#include "Task.h"
#include "AbstractEnemy.h"

class NormalEnemy : public AbstractEnemy
{

public:
	NormalEnemy(IShootListener *pt, int hp, int _pattern, double x, double y, std::string img_path);
	~NormalEnemy() = default;
	void init() override;
	void draw() const override;
	// Return line segments for collision detection
	std::vector<std::pair<Coor, Coor>> Edge() override;

private:
	double _x_wrap_point_offset;
	double _y_wrap_point_offset;

	void Pattern() override;
	void Move() override;
};