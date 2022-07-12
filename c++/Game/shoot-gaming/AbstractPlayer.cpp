#include <DxLib.h>
#include "Define.h"
#include "AbstractPlayer.h"
#include "Keyboard.h"
#include "Macro.h"

using namespace std;

const static double SPEED = 4.0;

AbstractPlayer::AbstractPlayer(IShootListener* ptr, double x, double y, int life, string img_path) :
	_x(x),
	_y(y),
	_lives(life),
	_img(img_path),
	_bltype(0),
	_color(0),
	_flag(0),
	_heigh(0),
	_width(0),
	_shot_cnt(60),
	_ptr(ptr)
{
}

bool AbstractPlayer::update()
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
			_ptr->Shoot(_x  + _width / 2 - 3.0, _y, -Define::PI / 2, 3.0, eBalletPattern::PlayerBlt, 0);
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

	/*
	* Collision Detection
	*/
	if (_ptr->CheckTaken(Edge(), 0))
	{
		_lives--;
	}

	if (_lives <= 0) return false;

	return true;
}