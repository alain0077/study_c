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
	if (Keyboard::getIns()->getPressingCount(KEY_INPUT_UP) == 1) {//��L�[�őI��������
		NowSelect = (NowSelect + (Define::eTitleSelect::TitleNum - 1)) % Define::eTitleSelect::TitleNum;
	}
	if (Keyboard::getIns()->getPressingCount(KEY_INPUT_DOWN) == 1) {//���L�[�őI���������
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

	switch (NowSelect) {//���݂̑I����Ԃɏ]���ď����𕪊�
	case Define::eTitleSelect::Start://�X�^�[�g�I�𒆂Ȃ�
		DrawString(Define::START_X, Define::START_Y, "_____", GetColor(255, 255, 255));
		break;
	case Define::eTitleSelect::End://�I���I�𒆂Ȃ�
		DrawString(Define::END_X, Define::END_Y, "____", GetColor(255, 255, 255));
		break;
	case Define::eTitleSelect::Umpopulated://�������I�𒆂Ȃ�
		DrawString(Define::UNPOPULATED_X, Define::UNPOPULATED_Y, "______________", GetColor(255, 255, 255));
		break;
	}

	//DrawString(100, 100, "��", GetColor(255, 255, 255));
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
}
