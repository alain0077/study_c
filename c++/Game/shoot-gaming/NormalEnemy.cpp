#include "NormalEnemy.h"
#include "Macro.h"

using namespace std;

NormalEnemy::NormalEnemy(IShootListener* pt, int hp, int pattern, double x, double y, string img_path) : AbstractEnemy(pt, hp, pattern, x, y, img_path)
{
	_width = 13, _heigh = 12;
	_x_offset = 1, _y_offset = 1;
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