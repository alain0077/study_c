#include "GameScene.h"
#include <DxLib.h>
#include "Define.h"
#include "Keyboard.h"

using namespace std;

GameScene::GameScene(IOnSceneChangedListener* impl, const Parameter& parameter) : AbstractScene(impl, parameter)
, NowSelect(0)
{
	_bulletMgr = new BulletMgr();
	_scoreMgr = new ScoreMgr();

	_pMgr = new PlayerMgr(_bulletMgr);
	_eMgr = new EnemyMgr(_bulletMgr, _scoreMgr, "data/Normal.csv");
}

void GameScene::update()
{
	_bulletMgr->update();

	if (!_pMgr->update())
	{
		Parameter parameter;
		const bool stackClear = true;

		parameter.set("ParameterTagResultScore", _scoreMgr->getFilalScore());
		parameter.set("ParameterTagTime", _scoreMgr->getTime());

		_implSceneChanged->onSceneChanged(eScene::GameOver, parameter, stackClear);

		return;
	}
	
	if (!_eMgr->update())
	{
		if (!_eMgr->NextStage())
		{
			Parameter parameter;
			const bool stackClear = true;

			parameter.set("ParameterTagResultScore", _scoreMgr->getFilalScore());
			parameter.set("ParameterTagTime", _scoreMgr->getTime());

			_implSceneChanged->onSceneChanged(eScene::Result, parameter, stackClear);

			return;
		}
	}

	_scoreMgr->update();
}

void GameScene::draw() const
{
	_bulletMgr->draw();
	_pMgr->draw();
	_eMgr->draw();
	_scoreMgr->draw();

	DrawBox(Define::GAME_WIN_X1, Define::GAME_WIN_Y1, Define::GAME_WIN_X2, Define::GAME_WIN_Y2, GetColor(255, 255, 255), false);
	
	//DrawString(100, 100, "Å°", GetColor(255, 255, 255));
	//DrawBox(108, 99, 108, 114, GetColor(0, 0, 255), false);
	//DrawPixel(101, 101, GetColor(255, 0, 255));
	//DrawPixel(114, 101, GetColor(255, 0, 255));
	//DrawPixel(101, 113, GetColor(255, 0, 255));
	//DrawPixel(114, 113, GetColor(255, 0, 255));

	//DrawString(200, 200, "|", GetColor(255, 255, 255));
	//DrawPixel(204, 200, GetColor(255, 0, 255));
	//DrawPixel(204, 215, GetColor(255, 0, 255));
	//DrawPixel(204, 211, GetColor(255, 0, 255));
	//DrawPixel(208, 207, GetColor(255, 0, 255));
	//DrawString(Define::START_X, Define::START_Y, "Ç±Ç±ÇÕGameSceneÇ≈Ç∑ÅI", GetColor(255, 255, 255));
}