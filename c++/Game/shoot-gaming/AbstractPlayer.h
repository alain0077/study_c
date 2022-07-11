#pragma once

#include "Task.h"
#include "IShootListener.h"
#include "IStatusListener.h"
#include <string>

class IShootListener;

class AbstractPlayer : public Task, public IStatusListener
{
	enum eP_Flag {
		live,
		death,
	};

public:
	AbstractPlayer(IShootListener *ptr, double x, double y, int life, std::string img_path);
	virtual ~AbstractPlayer() = default;
	virtual void init() = 0;
	bool update();
	virtual void draw() const = 0;
	Status Lis_Status() override { return { { _x, _y }, {_heigh, _width} }; }
	// Return line segments for collision detection
	virtual std::vector<std::pair<Coor, Coor>> Edge() = 0;

protected:
		//�t���O
	int	_flag,

		//���C�t
		_lives,

		//��
		_width,
		//����
		_heigh,

		//�J�E���^
		_shot_cnt;

	//�摜�t�@�C���̃p�X
	std::string _img;

	//���W
	double _x, _y;

	/*�e���֘A*/

		//�e�̎��
	int _bltype,

		//�F
		_color;

	IShootListener* _ptr;
};