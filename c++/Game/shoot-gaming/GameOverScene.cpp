#include "GameOverScene.h"
#include <DxLib.h>
#include "Define.h"
#include "Keyboard.h"
#include "Macro.h"

using namespace std;

GameOverScene::GameOverScene(IOnSceneChangedListener* impl, const Parameter& parameter) : AbstractScene(impl, parameter)
, _NowSelect(0), _score(parameter.get("ParameterTagResultScore")), _time(parameter.get("ParameterTagTime"))
{
}

void GameOverScene::update()
{
	if (Keyboard::getIns()->getPressingCount(KEY_INPUT_UP) == 1) {//上キーで選択を一つ上へ
		_NowSelect = (_NowSelect + (Define::eResultSelect::ResultNum - 1)) % Define::eResultSelect::ResultNum;
	}
	if (Keyboard::getIns()->getPressingCount(KEY_INPUT_DOWN) == 1) {//下キーで選択を一つ下へ
		_NowSelect = (_NowSelect + 1) % Define::eResultSelect::ResultNum;
	}

	if (Keyboard::getIns()->getPressingCount(KEY_INPUT_RETURN) == 1) {
		Parameter parameter;
		const bool stackClear = true;

		switch (_NowSelect) {
		case Define::eResultSelect::Restart:
			_implSceneChanged->onSceneChanged(eScene::Game, parameter, stackClear);
			break;
		case Define::eResultSelect::Title:
			_implSceneChanged->onSceneChanged(eScene::Title, parameter, stackClear);
			break;
		}
	}
}

void GameOverScene::draw() const
{
	DrawString(Define::WIN_W / 2 - Define::Result_Score_X + 160, Define::WIN_H / 2 - Define::Result_Score_Y - 120, "Game Over!", GetColor(255, 255, 255));
	DrawFormatString(Define::WIN_W / 2 - Define::Result_Score_X, Define::WIN_H / 2 - Define::Result_Score_Y, GetColor(255, 255, 255), "          time  : %d", _time);
	DrawFormatString(Define::WIN_W / 2 - Define::Result_Score_X, Define::WIN_H / 2 - Define::Result_Score_Y + 20, GetColor(255, 255, 255), "          score : %d", _score);

	DrawString(Define::WIN_W / 2 - Define::Result_Restart_X, Define::WIN_H / 2 + Define::Result_Restart_Y, "Restart", GetColor(255, 255, 255));
	DrawString(Define::WIN_W / 2 - Define::Result_Restart_X, Define::WIN_H / 2 + Define::Result_Title_Y + 60, "Back to Title", GetColor(255, 255, 255));

	switch (_NowSelect) {//現在の選択状態に従って処理を分岐
	case Define::eResultSelect::Restart:
		DrawString(Define::WIN_W / 2 - Define::Result_Restart_X, Define::WIN_H / 2 + Define::Result_Restart_Y, "_______", GetColor(255, 255, 255));
		break;
	case Define::eResultSelect::Title:
		DrawString(Define::WIN_W / 2 - Define::Result_Restart_X, Define::WIN_H / 2 + +Define::Result_Title_Y + 60, "_____________", GetColor(255, 255, 255));
		break;
	default:
		ERR("unexpected error!");
		break;
	}
}