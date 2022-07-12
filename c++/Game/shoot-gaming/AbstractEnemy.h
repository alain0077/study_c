#pragma once

#include "Task.h"
#include "IShootListener.h"
#include "IStatusListener.h"
#include <string>

class IShootListener;

class AbstractEnemy : public Task, public IStatusListener
{
public:
	AbstractEnemy(IShootListener* ptr, int hp, int _pattern, double x, double y, std::string img_path);
	virtual ~AbstractEnemy() = default;
	virtual void init() = 0;
	bool update();
	virtual void draw() const = 0;
	
	Status Lis_Status() override { return { { _x, _y }, {_heigh, _width} }; }

	// Return line segments for collision detection
	virtual std::vector<std::pair<Coor, Coor>> Edge() = 0;

	// Whether or not it is on the outside
	bool IsOutside() const;

protected:

	unsigned int
		//カウント
		_cnt;

		//フラグ
	int	_flag,
		
		//移動パターン
		_pattern,

		//ヒットポイント
		_hp,

		//停滞時間
		_wait,

		//幅
		_width,

		//高さ
		_heigh,

		// x's soffset
		_x_offset,

		// y's offset
		_y_offset,

		//色
		_color;

		//画像ファイルのパス
	std::string _img;

		//座標
	double _x, _y,

		//スピード
		_sp,

		//角度
		_x_ang,
		_y_ang;

	/*弾幕関連*/

		//弾の種類
	int _bltype;

	IShootListener* _ptr;

private:
	//パターンに応じたパラメータを設定
	virtual void Pattern() = 0;

	//パターンに応じたx,yを返す
	virtual void Move() = 0;
};