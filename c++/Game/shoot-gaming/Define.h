#pragma once

#include <string>


class Define final {
public:
	const static int WIN_W;	//�E�B���h�E�T�C�Y��
	const static int WIN_H;	//�E�B���h�E�T�C�Y�c

	const static float PI;	//�~����

	
	//Title���
	const static int START_X;
	const static int START_Y;
	const static int END_X;
	const static int END_Y;
	const static int UNPOPULATED_X;
	const static int UNPOPULATED_Y;

	//Game���
	const static int GAME_WIN_X1;
	const static int GAME_WIN_Y1;
	const static int GAME_WIN_X2;
	const static int GAME_WIN_Y2;

	//Result���
	const static int Result_Score_X;
	const static int Result_Score_Y;
	const static int Result_Restart_X;
	const static int Result_Restart_Y;
	const static int Result_Title_X;
	const static int Result_Title_Y;

	enum eTitleSelect {
		Start,
		End,
		Umpopulated,

		TitleNum,
	};

	enum eResultSelect {
		Restart,
		Title,
		
		ResultNum,
	};

	//��Փx
	enum eLevel {
		Easy,
		Normal,
		LevelNum
	};

	//�t���[��
	const static int FRAME;
};