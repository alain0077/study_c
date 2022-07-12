#pragma once

#include "AbstractScene.h"
#include "IShootListener.h"

class TestScene : public AbstractScene
{
public:
	TestScene(IOnSceneChangedListener* impl, const Parameter& parameter);
	virtual ~TestScene() = default;
	void update() override;
	void draw() const override;

	const static char* ParameterTagCharaNum;//パラメータのタグ「キャラクター数」

private:
	int NowSelect;

	int	_flag,

		//ライフ
		_lives,

		//幅
		_width,
		//高さ
		_heigh,

		//カウンタ
		_shot_cnt,

		_x_offset,

		_y_offset;

	//画像ファイルのパス
	std::string _img;

	//座標
	double _x, _y;

	/*弾幕関連*/

		//弾の種類
	int _bltype,

		//色
		_color;

	std::vector < std::pair<Coor, Coor >> Edge();
};