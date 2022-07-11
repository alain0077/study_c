#pragma once
#include <string>
#include <vector>

struct Status {
	//Corrdinate
	std::pair<double, double> coor;
	//Height & Width
	std::pair<double, double> _h_w;
};

class IStatusListener
{
public:
	IStatusListener() = default;
	~IStatusListener() = default;
	virtual Status Lis_Status() = 0;
};