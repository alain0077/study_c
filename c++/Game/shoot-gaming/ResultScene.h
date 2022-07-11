#pragma once

#include "AbstractScene.h"
#include <fstream>

class ResultScene : public AbstractScene
{
public:
	ResultScene(IOnSceneChangedListener* impl, const Parameter& parameter);
	virtual ~ResultScene() = default;
	void update() override;
	void draw() const override;

private:
	int _NowSelect,
		_score,
		_time;
};