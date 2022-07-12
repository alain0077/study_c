#include "TitleScene.h"
#include <DxLib.h>
#include "Define.h"
#include "Keyboard.h"

using namespace std;

TitleScene::TitleScene(IOnSceneChangedListener* impl, const Parameter& parameter) : AbstractScene(impl, parameter)
, NowSelect(0)
{
}

void TitleScene::update()
{
	if (Keyboard::getIns()->getPressingCount(KEY_INPUT_UP) == 1) {//上キーで選択を一つ上へ
		NowSelect = (NowSelect + (Define::eTitleSelect::TitleNum - 1)) % Define::eTitleSelect::TitleNum;
	}
	if (Keyboard::getIns()->getPressingCount(KEY_INPUT_DOWN) == 1) {//下キーで選択を一つ下へ
		NowSelect = (NowSelect + 1) % Define::eTitleSelect::TitleNum;
	}

	if (Keyboard::getIns()->getPressingCount(KEY_INPUT_RETURN) == 1) {
		Parameter parameter;
		const bool stackClear = false;

		switch (NowSelect) {
		case Define::eTitleSelect::Start:
			_implSceneChanged->onSceneChanged(eScene::Game, parameter, stackClear);
			break;
		case Define::eTitleSelect::End:

			break;
		}
		
	}


	/*
	if (Keyboard::getIns()->getPressingCount(KEY_INPUT_E) == 1) {
		Parameter parameter;
		parameter.set(GameScene::ParameterTagLevel, Define::eLevel::Easy);
		const bool stackClear = false;
		_implSceneChanged->onSceneChanged(eScene::Game, parameter, stackClear);
		return;
	}
	if (Keyboard::getIns()->getPressingCount(KEY_INPUT_N) == 1) {
		Parameter parameter;
		parameter.set(GameScene::ParameterTagLevel, Define::eLevel::Normal);
		const bool stackClear = false;
		_implSceneChanged->onSceneChanged(eScene::Game, parameter, stackClear);
		return;
	}
	*/
}

void TitleScene::draw() const
{
	DrawString(Define::START_X, Define::START_Y, "Start", GetColor(255, 255, 255));
	DrawString(Define::END_X, Define::END_Y, "Exit", GetColor(255, 255, 255));
	DrawString(Define::UNPOPULATED_X, Define::UNPOPULATED_Y, "coming soon...", GetColor(255, 255, 255));

	switch (NowSelect) {//現在の選択状態に従って処理を分岐
	case Define::eTitleSelect::Start://スタート選択中なら
		DrawString(Define::START_X, Define::START_Y, "_____", GetColor(255, 255, 255));
		break;
	case Define::eTitleSelect::End://終了選択中なら
		DrawString(Define::END_X, Define::END_Y, "____", GetColor(255, 255, 255));
		break;
	case Define::eTitleSelect::Umpopulated://未実装選択中なら
		DrawString(Define::UNPOPULATED_X, Define::UNPOPULATED_Y, "______________", GetColor(255, 255, 255));
		break;
	}
}
