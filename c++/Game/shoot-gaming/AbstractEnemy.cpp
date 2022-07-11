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
	_flag(live),
	_img(img_path)
{
	Pattern(_pattern);
}

bool AbstractEnemy::update()
{
	if(!(_cnt%60)) _ptr->Shoot(_x, _y, Define::PI / 2, 2.0, eBalletPattern::EnemyBlt, 1);

	_cnt++;
	Move(_pattern);

	_hp -= _ptr->CheckTaken(Edge(), 1);

	if (_hp <= 0) {
		return false;
	}

	return true;
}

void AbstractEnemy::Pattern(int p)
{
	switch(p)
	{
	case 0:
		_x_ang = 0.0;
		_y_ang = Define::PI / 2;
		_sp = 1.0;
		break;
	case 1:
		_x_ang = Define::PI / 2;
		_y_ang = 0.0;
		_sp = 1.0;
		break;
	case 2:
		_x_ang = Define::PI / 3;
		_y_ang = Define::PI / 3;
		_sp = 2.0;
		break;

	}
}

void AbstractEnemy::Move(int p)
{
	switch (p)
	{
	case 0:
		if (_cnt % 360 < 90) {
			_x += cos(_x_ang) * _sp;
			_y += sin(_y_ang) * _sp;
		}
		else if (_cnt % 360 < 180)
		{
			_x += cos(_x_ang + Define::PI) * _sp;
			_y += sin(_y_ang) * _sp;
		}
		else if (_cnt % 360 < 270) {
			_x += cos(_x_ang + Define::PI) * _sp;
			_y += sin(_y_ang + Define::PI) * _sp;
		}
		else {
			_x += cos(_x_ang) * _sp;
			_y += sin(_y_ang + Define::PI)* _sp;
		}
		break;

	case 1:
		_x += 2.0 * _sp;
		_x_ang += 0.1 * _sp;
		_y = cos(_x_ang) * 100.0 + 100.0;
		break;

	case 2:
		if (_cnt % 270 < 90) {
			_x += cos(_x_ang) * _sp;
			_y += sin(_y_ang) * _sp;
		}
		else if (_cnt % 270 < 180)
		{
			_x += cos(_x_ang) * _sp;
			_y += sin(_y_ang + Define::PI) * _sp;
		}
		else {
			_x += cos(_x_ang + Define::PI / 3 * 2) * _sp;
			_y += sin(_y_ang + Define::PI / 3 * 2) * _sp;
		}
		break;
	}
}