#pragma once

#include "Task.h"
#include "AbstractEnemy.h"

class BossEnemy : public AbstractEnemy
{

public:
	BossEnemy(IShootListener* pt, int hp, int _pattern, double x, double y, std::string img_path);
	~BossEnemy() = default;
	void init() override;
	void draw() const override;
	bool update() override;
	// Return line segments for collision detection
	std::vector<std::pair<Coor, Coor>> Edge() override;

private:
	void Pattern() override;
	void Move() override;
	void Skill();
};