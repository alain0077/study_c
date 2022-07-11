#pragma once
#include "eBalletPattern.h"
#include <iostream>
#include <vector>

struct Coor {
	double x, y;
};

class IShootListener
{
public:
	IShootListener() = default;
	virtual ~IShootListener() = default;
	// Palyer:0, Enemy:1
	virtual void Shoot(double x, double y, double ang, double speed, eBalletPattern pattern, int flag) = 0;
	// Palyer:0, Enemy:1
	virtual int CheckTaken(std::vector<std::pair<Coor, Coor>> edge, int flag) = 0;
};