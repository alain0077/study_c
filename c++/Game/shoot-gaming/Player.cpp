#include "Player.h"

using namespace std;

Player::Player(IShootListener* ptr, double x, double y, int life, std::string img_path) : AbstractPlayer(ptr, x, y, life, img_path)
{
	_heigh = 13, _width = 16;
}

void Player::init()
{
}

void Player::draw() const
{
	//DrawFormatString(20, 10, GetColor(255, 255, 255), "%d,%d", _x, _y);
	DrawString(_x, _y, "Å£", GetColor(255, 255, 255));
}

vector<pair<Coor, Coor>> Player::Edge()
{
	Coor a = { _x + _width / 2.0, _y },
		 b = { _x, _y + _heigh },
		 c = { _x + _width, _y + _heigh };

	return { { a, b }, { b, c }, { c, a } };
}