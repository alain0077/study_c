#pragma once

#include "Task.h"
#include "IShootListener.h"
#include "IStatusListener.h"
#include <string>

class IShootListener;

class AbstractEnemy : public Task, public IStatusListener
{
	enum eE_Flag {
		live,
		death,
	};

public:
	AbstractEnemy(IShootListener* ptr, int hp, int _pattern, double x, double y, std::string img_path);
	virtual ~AbstractEnemy() = default;
	virtual void init() = 0;
	bool update();
	virtual void draw() const = 0;
	Status Lis_Status() override { return { { _x, _y }, {_heigh, _width} }; }
	// Return line segments for collision detection
	virtual std::vector<std::pair<Coor, Coor>> Edge() = 0;

protected:

	unsigned int
		//�J�E���g
		_cnt;

		//�t���O
	int	_flag,
		
		//�ړ��p�^�[��
		_pattern,

		//�q�b�g�|�C���g
		_hp,

		//��؎���
		_wait,

		//��
		_width,

		// x's soffset
		_x_offset,

		// y's offset
		_y_offset,

		//����
		_heigh;

		//�摜�t�@�C���̃p�X
	std::string _img;

		//���W
	double _x, _y,

		//�X�s�[�h
		_sp,

		//�p�x
		_x_ang,
		_y_ang;

	/*�e���֘A*/

		//�e�̎��
	int _bltype,

		//�F
		_color;

	IShootListener* _ptr;

private:
	//�p�^�[���ɉ������p�����[�^��ݒ�
	void Pattern(int p);

	//�p�^�[���ɉ�����x,y��Ԃ�
	void Move(int p);
};