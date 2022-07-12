#include "BossEnemy.h"
#include "Macro.h"
#include "Define.h"

using namespace std;

BossEnemy::BossEnemy(IShootListener* pt, int hp, int pattern, double x, double y, string img_path) : AbstractEnemy(pt, hp, pattern, x, y, img_path)
{
	_width = 13, _heigh = 12;
	_x_offset = 1, _y_offset = 1;

	Pattern();
}

void BossEnemy::init()
{
}

bool BossEnemy::update()
{
	if (!(_cnt % 60)) _ptr->Shoot(_x + _x_offset + _width / 2, _y + _y_offset, Define::PI / 2, 2.0, eBalletPattern::EnemyBlt, 1);

	_cnt++;

	Move();

	Skill();

	_hp -= _ptr->CheckTaken(Edge(), 1);

	if (_hp <= 0) {
		return false;
	}

	return true;
} 

vector<pair<Coor, Coor>> BossEnemy::Edge()
{
	vector<Coor> v;

	switch (_pattern)
	{
	/*
	* Å°Å°Å°
	* Å@Å°
	*/
	case 0:
		v.push_back({ _x - _width, _y + _y_offset });
		v.push_back({ _x + (_width + _x_offset) * 2, _y + _y_offset });
		v.push_back({ _x - _width, _y + _heigh + _y_offset });
		v.push_back({ _x + (_width + _x_offset) * 2, _y + _heigh + _y_offset });
		v.push_back({ _x + _x_offset, _y + _heigh + _y_offset * 2 });
		v.push_back({ _x + _width + _x_offset, _y + _heigh + _y_offset * 2 });
		v.push_back({ _x + _x_offset, _y + (_heigh + _y_offset) * 2 });
		v.push_back({ _x + _width + _x_offset, _y + (_heigh + _y_offset) * 2 });
		break;
	case 1:
		break;
	default:
		break;
	}

	vector<pair<Coor, Coor>> res;

	for (int i = 0; i < v.size(); i++)
	{
		res.push_back({ v[i], v[(i + 1) % v.size()] });
	}

	return res;
}

void BossEnemy::Pattern()
{
	switch (_pattern)
	{
	case 0:
		_x_ang = 0.0;
		_y_ang = Define::PI / 2.0;
		_sp = 1.0;
		_color = GetColor(255, 255, 255);
		break;
	default:
		break;
	}
}

void BossEnemy::Move()
{
	switch (_pattern)
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
	default:
		break;
	}
}

void BossEnemy::Skill()
{
}

void BossEnemy::draw() const
{
	switch (_pattern)
	{
		/*
		* Å°Å°Å°
		* Å@Å°
		*/
	case 0:
		DrawString(_x, _y, "Å°", _color);
		DrawString(_x + _width + _x_offset, _y, "Å°", _color);
		DrawString(_x - _width - _x_offset, _y, "Å°", _color);
		DrawString(_x, _y + _heigh + _y_offset, "Å°", _color);
		break;
	default:
		break;
	}
}