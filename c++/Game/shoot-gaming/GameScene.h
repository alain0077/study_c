#pragma once

#include "AbstractScene.h"
#include "PlayerMgr.h"
#include "EnemyMgr.h"
#include "BulletMgr.h" 
#include "ScoreMgr.h"
#include <fstream>

class GameScene : public AbstractScene
{
	enum eGameScene {
		GameNum
	};
public:
	GameScene(IOnSceneChangedListener* impl, const Parameter& parameter);
	virtual ~GameScene() = default;
	void update() override;
	void draw() const override;

private:
	int NowSelect;
	int _NowStage;
	bool _StageChangeFlag;

	BulletMgr* _bulletMgr;
	EnemyMgr* _eMgr;
	PlayerMgr* _pMgr;
	ScoreMgr* _scoreMgr;
};