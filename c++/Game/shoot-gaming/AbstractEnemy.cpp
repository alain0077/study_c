#include "AbstractEnemy.h"
#include "Define.h"
#include "Macro.h"

using namespace std;

AbstractEnemy::AbstractEnemy(IShootListener *ptr, int hp, int pattern, double x, double y, string img_path) :
	_ptr(ptr),
	_hp(hp),
	_pattern(pattern),
	_x(x),
	_y(y),
	_cnt(0),
	_flag(0),
	_img(img_path)
{
}

bool AbstractEnemy::update()
{
	if (!(_cnt % 60)) _ptr->Shoot(_x + _x_offset + _width / 2 - 2.0, _y + _y_offset + 3.0, Define::PI / 2, 2.0, eBalletPattern::EnemyBlt, 1);

	_cnt++;
	
	Move();

	_hp -= _ptr->CheckTaken(Edge(), 1);

	if (_hp <= 0) {
		return false;
	}

	return true;
}

bool AbstractEnemy::IsOutside() const
{
	if (Define::GAME_WIN_X1 > _x + _x_offset + _width)
	{
		return true;
	}
	else if (Define::GAME_WIN_X2 < _x + _x_offset)
	{
		return true;
	}
	else if (Define::GAME_WIN_Y1 > _y + _y_offset + _heigh)
	{
		return true;
	}
	else if (Define::GAME_WIN_Y2 < _y + _y_offset)
	{
		return true;
	}

	return false;
}