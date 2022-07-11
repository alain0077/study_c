#include "Bullet.h"
#include "Define.h"
#include "eBalletPattern.h"
#include "Macro.h"

using namespace std;

Bullet::Bullet(double x, double y, double ang, double sp, int ptn) :
	_cnt(0),
	_x(x),
	_y(y),
	_x_offset(0.0),
	_y_offset(0.0),
	_ang(ang),
	_pattern(ptn),
	_speed(sp),
	_width(0.0),
	_heigh(0.0)
{
	switch (_pattern)
	{
	case eBalletPattern::EnemyBlt:
		_width = 8.0;
		_heigh = 8.0;
		_y_offset = 3.0;
		break;
	case eBalletPattern::PlayerBlt:
		_width = 0.0;
		_heigh = 15.0;
		_x_offset = 4.0;
		break;
	default:
		ERR("存在しない弾が選択されました！");
		break;
	}
}

void Bullet::init()
{
}

bool Bullet::update()
{
	_x += cos(_ang) * _speed;
	_y += sin(_ang) * _speed;

	if (_x < Define::GAME_WIN_X1 - _width || _x > Define::GAME_WIN_X2 + _width || _y < Define::GAME_WIN_Y1 - _heigh || _y > Define::GAME_WIN_Y2 + _heigh) return false;

	draw();

	return true;
}

bool Bullet::IsTakenCircle(double x, double y, double r)
{
	switch (_pattern)
	{
	case eBalletPattern::EnemyBlt:
		if (r + _width >= pow(x - (_x + _width / 2.0), 2.0) + pow(y - (_y + (3.0 + _heigh)), 2.0))
			return true;
		break;
	case eBalletPattern::PlayerBlt:

		break;
	default:
		ERR("存在しない弾が選択されました！");
		break;
	}

	return false;
}

void Bullet::draw() const
{
	switch (_pattern)
	{
	case eBalletPattern::EnemyBlt:
		DrawString(_x, _y, "+", GetColor(255, 255, 255));
		break;
	case eBalletPattern::PlayerBlt:
		DrawString(_x, _y, "|", GetColor(255, 255, 255));
		break;
	default:
		ERR("存在しない弾が選択されました！");
		break;
	}
}