#include "GameScene.h"
#include <DxLib.h>
#include "Define.h"
#include "Keyboard.h"

using namespace std;

GameScene::GameScene(IOnSceneChangedListener* impl, const Parameter& parameter) : AbstractScene(impl, parameter)
, NowSelect(0), _StageChangeFlag(false), _NowStage(1)
{
	_bulletMgr = new BulletMgr();
	_scoreMgr = new ScoreMgr();

	_pMgr = new PlayerMgr(_bulletMgr);
	_eMgr = new EnemyMgr(_bulletMgr, _scoreMgr, "data/Normal.csv");
}

void GameScene::update()
{
	if(!_StageChangeFlag)
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
			else
			{
				_bulletMgr->init();
				_StageChangeFlag = true;
				_NowStage++;
			}
		}
	}
	else
	{
		if (Keyboard::getIns()->getPressingCount(KEY_INPUT_RETURN) == 1) {
			_StageChangeFlag = false;
		}
	}

	_scoreMgr->update();
}

void GameScene::draw() const
{
	if (!_StageChangeFlag)
	{
		_bulletMgr->draw();
		_pMgr->draw();
		_eMgr->draw();
		_scoreMgr->draw();
	}

	_scoreMgr->draw();

	if(_StageChangeFlag)
	{
		DrawFormatString(100, 100, GetColor(255, 255, 255), "Next Stage is %d", _NowStage);
		DrawString(100, 160, "Please Hit EnterKey", GetColor(255, 255, 255));
	}


	DrawBox(Define::GAME_WIN_X1, Define::GAME_WIN_Y1, Define::GAME_WIN_X2, Define::GAME_WIN_Y2, GetColor(255, 255, 255), false);
	DrawBox(Define::GAME_WIN_X1 - 40, Define::GAME_WIN_Y1, Define::GAME_WIN_X1, Define::GAME_WIN_Y2, GetColor(0, 0, 0), true);
	DrawBox(Define::GAME_WIN_X1 - 40, Define::GAME_WIN_Y1 - 40, Define::GAME_WIN_X2 + 40, Define::GAME_WIN_Y1, GetColor(0, 0, 0), true);
	DrawBox(Define::GAME_WIN_X2, Define::GAME_WIN_Y1, Define::GAME_WIN_X2 + 40, Define::GAME_WIN_Y2, GetColor(0, 0, 0), true);
	DrawBox(Define::GAME_WIN_X1 - 40, Define::GAME_WIN_Y2, Define::GAME_WIN_X2 + 40, Define::GAME_WIN_Y2 + 40, GetColor(0, 0, 0), true);

	DrawFormatString(410, 100, GetColor(255, 255, 255), "Stage %d", _NowStage);
}