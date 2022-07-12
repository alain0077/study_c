#include "TestScene.h"
#include <DxLib.h>
#include "Define.h"
#include "Keyboard.h"


#include <vector>

using namespace std;

const static double SPEED = 1.0;

bool IsCross(Coor a, Coor b, Coor c, Coor d)
{
	/*
	* For the x coordinate,
	* If they do not intersect obviously.
	*/
	if (a.x >= b.x) {
		if ((a.x < c.x && a.x < d.x) || (b.x > c.x && b.x > d.x)) {
			return false;
		}
	}
	else {
		if ((b.x < c.x && b.x < d.x) || (a.x > c.x && a.x > d.x)) {
			return false;
		}
	}

	/*
	* For the y coordinate,
	* If they do not intersect obviously.
	*/
	if (a.y >= b.y) {
		if ((a.y > c.y && a.y > d.y) || (b.y < c.y && b.y < d.y)) {
			return false;
		}
	}
	else {
		if ((b.x > c.x && b.x > d.x) || (a.x < c.x && a.x < d.x)) {
			return false;
		}
	}

	/*
	* When AB and CD are parallel
	*/
	/*
	if ((a.x - b.x) * (c.y - d.y) == (a.y - b.y) * (c.y - d.y))
	{
		if (((c.y * (a.x - b.x)) + (a.y * (b.x - c.x)) + (b.y * (c.x - a.x)) == 0) &&
			((d.y * (a.x - b.x)) + (d.y * (b.x - c.x)) + (d.y * (c.x - a.x)) != 0)) 
		{
			return true;
		}

		if (((c.y * (a.x - b.x)) + (a.y * (b.x - c.x)) + (b.y * (c.x - a.x)) != 0) &&
			((d.y * (a.x - b.x)) + (d.y * (b.x - c.x)) + (d.y * (c.x - a.x)) == 0))
		{
			return true;
		}
	}
	*/

	/*
	* Do line AB and line CD intersect?
	*/
	if (((a.x - b.x) * (c.y - a.y) - (a.y - b.y) * (c.x - a.x)) *
		((a.x - b.x) * (d.y - a.y) - (a.y - b.y) * (d.x - a.x)) > 0)
	{
		return false;
	}
	if (((c.x - d.x) * (a.y - c.y) - (c.y - d.y) * (a.x - c.x)) *
		((c.x - d.x) * (b.y - c.y) - (c.y - d.y) * (b.x - c.x)) > 0)
	{
		return false;
	}

	return true;
}

TestScene::TestScene(IOnSceneChangedListener* impl, const Parameter& parameter) : AbstractScene(impl, parameter)
, NowSelect(0)
{
	/*
	_heigh = 13, _width = 16;
	*/

	_x = 150.0, _y = 150.0, _lives = 1;

	_width = 13, _heigh = 12;
	_x_offset = 1, _y_offset = 1;

	_flag = true;
}

void TestScene::update()
{
	_shot_cnt++;

	// Move by keyboard operation
	double X = 0, Y = 0;
	if (Keyboard::getIns()->getPressingCount(KEY_INPUT_RIGHT))
	{
		X += SPEED;
	}
	if (Keyboard::getIns()->getPressingCount(KEY_INPUT_LEFT))
	{
		X -= SPEED;
	}
	if (Keyboard::getIns()->getPressingCount(KEY_INPUT_UP))
	{
		Y -= SPEED;
	}
	if (Keyboard::getIns()->getPressingCount(KEY_INPUT_DOWN))
	{
		Y += SPEED;
	}

	// Diagonal Move
	if (X && Y) {
		X /= (double)sqrt(2.0);
		Y /= (double)sqrt(2.0);
	}

	// Ç‰Ç¡Ç≠ÇËìÆÇ≠ìÆçÏ
	if (Keyboard::getIns()->getPressingCount(KEY_INPUT_LCONTROL))
	{
		X /= 3.0;
		Y /= 3.0;
	}

	if (_shot_cnt > 40) {
		if (Keyboard::getIns()->getPressingCount(KEY_INPUT_SPACE))
		{
			//_ptr->Shoot(_x + _width / 2, _y, -Define::PI / 2, 3.0, eBalletPattern::PlayerBlt, 0);
			_shot_cnt = 0;
		}
	}

	//î’ñ ÇÇÕÇ›èoÇ»Ç¢ÇÊÇ§Ç…Ç∑ÇÈÇΩÇﬂÇÃêßå‰
	if (_x + X < Define::GAME_WIN_X1) _x = Define::GAME_WIN_X1;
	else if (_x + X > Define::GAME_WIN_X2 - _width) _x = Define::GAME_WIN_X2 - _width;
	else _x += X;

	if (_y + Y < Define::GAME_WIN_Y1) _y = Define::GAME_WIN_Y1;
	else if (_y + Y > Define::GAME_WIN_Y2 - _heigh) _y = Define::GAME_WIN_Y2 - _heigh;
	else _y += Y;

	double off = 4.0;
	_flag = false;

	Coor
	v1 = { 100 + off, 100 },
	v2 = { 100 + off, 100 + 15.0 };
	/*
	v1 = { 100, 100 + off + 8.0 / 2.0 },
	v2 = { 100 + 8.0, 100 + off + 8.0 / 2.0 },
	v3 = { 100 + 8.0 / 2.0, 100 + off },
	v4 = { 100 + 8.0 / 2.0, 100 + off + 8.0 };
	*/
	vector<pair<Coor, Coor>> edge = Edge();

	for (auto e : edge)
	{
		if (IsCross(e.first, e.second, v1, v2) ||
			//IsCross(e.first, e.second, v3, v4) ||
			IsCross(v1, v2, e.first, e.second) //||
			//IsCross(v3, v4, e.first, e.second)
			)
		{
			_flag = true;
			break;
		}
	}



}

vector<pair<Coor, Coor>> TestScene::Edge()
{
	/*
	Coor a = { _x + _width / 2.0, _y },
		b = { _x, _y + _heigh },
		c = { _x + _width, _y + _heigh };

	return { { a, b }, { b, c }, { c, a } };
	*/

	Coor a = { _x + _x_offset, _y + _y_offset },
		b = { _x + _x_offset + _width, _y + _y_offset },
		c = { _x + _x_offset, _y + _y_offset + _heigh },
		d = { _x + _x_offset + _width, _y + _y_offset + _heigh };

	return { { a, b }, { b, c }, { c, d }, {d, a} };
}

void TestScene::draw() const
{
	DrawString(_x, _y, "Å°", GetColor(255, 255, 255));

	DrawString(100, 100, "|", GetColor(255, 0, 255));

	if (_flag)
	{
		DrawString(200, 100, "TRUE", GetColor(255, 255, 255));
	}
	else
	{
		DrawString(200, 100, "FALSE", GetColor(255, 255, 255));
	}
	 
	if (IsCross({ 100, 100 + 3.0 + 8.0 / 2.0 }, { 100 + 8.0, 100 + 3.0 + 8.0 / 2.0 }, { _x + _x_offset + _width, _y + _y_offset + _heigh }, { _x + _x_offset, _y + _y_offset }))
	{
		DrawString(200, 140, "TRUE", GetColor(255, 255, 255));
	}
	else
	{
		DrawString(200, 140, "FALSE", GetColor(255, 255, 255));
	}
	
	if (IsCross({ 100 + 8.0 / 2.0, 100 + 3.0 }, { 100 + 8.0 / 2.0, 100 + 3.0 + 8.0 }, { _x + _x_offset + _width, _y + _y_offset + _heigh }, { _x + _x_offset, _y + _y_offset }))
	{
		DrawString(200, 160, "TRUE", GetColor(255, 255, 255));
	}
	else
	{
		DrawString(200, 160, "FALSE", GetColor(255, 255, 255));
	}

	/*
	int _x = 100, _y = 100;
	int _heigh = 13, _width = 16;
	int _x_offset = 1, _y_offset = 3;
	int _color = GetColor(255, 255, 255);

	DrawString(_x, _y, "Å£", _color);

	_color = GetColor(255, 0, 255);

	DrawPixel(_x + _width / 2.0, _y, _color);
	DrawPixel(_x, _y + _heigh, _color);
	DrawPixel(_x + _width, _y + _heigh, _color);
	*/
}