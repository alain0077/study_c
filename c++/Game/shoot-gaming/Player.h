#pragma once

#include "AbstractPlayer.h"

class IShootListener;

class Player : public AbstractPlayer
{
public:
	Player(IShootListener* pt, double x, double y, int life, std::string img_path);
	~Player() = default;
	void init() override;
	void draw() const override;
	std::vector<std::pair<Coor, Coor>> Edge() override;
};