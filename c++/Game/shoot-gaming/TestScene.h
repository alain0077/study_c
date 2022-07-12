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

	const static char* ParameterTagCharaNum;//�p�����[�^�̃^�O�u�L�����N�^�[���v

private:
	int NowSelect;

	int	_flag,

		//���C�t
		_lives,

		//��
		_width,
		//����
		_heigh,

		//�J�E���^
		_shot_cnt,

		_x_offset,

		_y_offset;

	//�摜�t�@�C���̃p�X
	std::string _img;

	//���W
	double _x, _y;

	/*�e���֘A*/

		//�e�̎��
	int _bltype,

		//�F
		_color;

	std::vector < std::pair<Coor, Coor >> Edge();
};