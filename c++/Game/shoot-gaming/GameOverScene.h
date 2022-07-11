#pragma once

#include "AbstractScene.h"
#include <fstream>

class GameOverScene : public AbstractScene
{
public:
	GameOverScene(IOnSceneChangedListener* impl, const Parameter& parameter);
	virtual ~GameOverScene() = default;
	void update() override;
	void draw() const override;

private:
	int _NowSelect,
		_score,
		_time;
};