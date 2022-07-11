#pragma once

#include "Task.h"
#include "IShootListener.h"
#include "IStatusListener.h"
#include <string>

class IShootListener;

class AbstractPlayer : public Task, public IStatusListener
{
	enum eP_Flag {
		live,
		death,
	};

public:
	AbstractPlayer(IShootListener *ptr, double x, double y, int life, std::string img_path);
	virtual ~AbstractPlayer() = default;
	virtual void init() = 0;
	bool update();
	virtual void draw() const = 0;
	Status Lis_Status() override { return { { _x, _y }, {_heigh, _width} }; }
	// Return line segments for collision detection
	virtual std::vector<std::pair<Coor, Coor>> Edge() = 0;

protected:
		//フラグ
	int	_flag,

		//ライフ
		_lives,

		//幅
		_width,
		//高さ
		_heigh,

		//カウンタ
		_shot_cnt;

	//画像ファイルのパス
	std::string _img;

	//座標
	double _x, _y;

	/*弾幕関連*/

		//弾の種類
	int _bltype,

		//色
		_color;

	IShootListener* _ptr;
};