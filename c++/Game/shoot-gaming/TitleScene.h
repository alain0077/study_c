#pragma once

#include "AbstractScene.h"
#include <fstream>

class TitleScene : public AbstractScene
{
public:
	TitleScene(IOnSceneChangedListener* impl, const Parameter& parameter);
	virtual ~TitleScene() = default;
	void update() override;
	void draw() const override;

	const static char* ParameterTagCharaNum;//パラメータのタグ「キャラクター数」

private:
	int NowSelect;
};