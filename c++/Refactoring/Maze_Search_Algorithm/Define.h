#pragma once

#include <string>


class Define final {
public:
	const static int WIN_W;	//�E�B���h�E�T�C�Y��
	const static int WIN_H;	//�E�B���h�E�T�C�Y�c

	const static int MAP_SIZE; //�}�b�v�̃T�C�Y

	enum eMapType {
		wall,
		road,
		start,
		goal,

		eMapTypeNum
	};
};