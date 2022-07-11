#pragma once
#include "Task.h"
#include "IShootListener.h"
#include "IStatusListener.h"
#include "Bullet.h"
#include <vector>

class BulletMgr final: public Task, public IShootListener
{
public:
	BulletMgr();
	~BulletMgr() = default;
	void init();
	bool update();
	void draw() const;
	// Palyer:0, Enemy:1
	int CheckTaken(std::vector<std::pair<Coor, Coor>> edge, int flag) override;
	// Palyer:0, Enemy:1
	void Shoot(double x, double y, double ang, double speed, eBalletPattern pattern, int flag) override;

private:
	std::vector<Bullet*> _bullets;
	std::vector<Bullet*> _ebullets;

	/*
	* Do line AB and line CD intersect?
	* if they intersect, return True.
	* Do not intersect, return False.
	*/
	bool IsCross(Coor A, Coor B, Coor C, Coor D);
};