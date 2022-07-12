#include "NormalEnemy.h"
#include "Macro.h"
#include "Define.h"

using namespace std;

NormalEnemy::NormalEnemy(IShootListener* pt, int hp, int pattern, double x, double y, string img_path) : AbstractEnemy(pt, hp, pattern, x, y, img_path)
{
	_width = 13, _heigh = 12;
	_x_offset = 1, _y_offset = 1;
	_x_wrap_point_offset = x;
	_y_wrap_point_offset = y;

	Pattern(_pattern);
}

void NormalEnemy::init()
{
}

void NormalEnemy::draw() const
{
	DrawString(_x, _y, "Å°", GetColor(255, 255, 255));
}

vector<pair<Coor, Coor>> NormalEnemy::Edge()
{
	Coor a = { _x + _x_offset, _y + _y_offset },
		 b = { _x + _x_offset + _width, _y + _y_offset },
		 c = { _x + _x_offset, _y + _y_offset + _heigh },
		 d = { _x + _x_offset + _width, _y + _y_offset + _heigh };

	return { { a, b }, { b, c }, { c, d }, {d, a} };
}

void NormalEnemy::Pattern(int p)
{
	switch (p)
	{
	case 0:
		_x_ang = 0.0;
		_y_ang = Define::PI / 2.0;
		_sp = 1.0;
		break;
	case 1:
		_x_ang = Define::PI / 2.0;
		_y_ang = 0.0;
		_sp = 0.5;
		break;
	case 2:
		_x_ang = Define::PI / 3.0;
		_y_ang = Define::PI / 3.0;
		_sp = 2.0;
		break;
	case 3:
		_x = (double)Define::GAME_WIN_X1 - _width;
		_x_ang = 0.0;
		_y_ang = Define::PI / 2.0;
		_sp = 1.0;
		break;
	case 4:
		_x = (double)Define::GAME_WIN_X2 - _width;
		_x_ang = 0.0;
		_y_ang = Define::PI / 2.0;
		_sp = 1.0;
		break;
	case 5:
		_x = (double)Define::GAME_WIN_X2 - _width;
		_x_ang = Define::PI / 3.0;
		_y_ang = Define::PI / 3.0;
		_sp = 2.0;
		break;
	default:
		break;
	}
}

void NormalEnemy::Move(int p)
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
			_y += sin(_y_ang + Define::PI) * _sp;
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
			_x += cos(_x_ang + (Define::PI / 3.0) * 2.0) * _sp;
			_y += sin(_y_ang + (Define::PI / 3.0) * 2.0) * _sp;
		}
		break;
	case 3:
		if (Define::GAME_WIN_X2 / 2 + _x_wrap_point_offset >= _x) {
			_x += cos(_x_ang) * _sp;
			_y += sin(_y_ang) * _sp;
		}
		else
		{
			_x += cos(_x_ang + Define::PI) * _sp;
			_y += sin(_y_ang) * _sp;
		}
		break;
	case 4:
		if (Define::GAME_WIN_X2 / 2 + _x_wrap_point_offset <= _x) {
			_x += cos(_x_ang + Define::PI) * _sp;
			_y += sin(_y_ang) * _sp;
		}
		else {
			_x += cos(_x_ang + Define::PI / 2.0) * _sp;
			_y += sin(_y_ang) * _sp;
		}
		break;
	case 5:
		if (Define::GAME_WIN_X2 / 2 + _x_wrap_point_offset <= _x) {
			_x += cos(_x_ang + Define::PI) * _sp;
			_y += sin(_y_ang) * _sp;
		}
		else
		{
			_x += cos(_x_ang + Define::PI) * _sp;
			_y += sin(_y_ang + Define::PI) * _sp;
		}
		break;
	default:
		break;
	}
}